#include "Simulator.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <sstream>
#include <vector>
#include <limits>
// function to load program from file
bool Simulator::loadProgramFromFile(
    const std::string& fileName,
    uint8_t startAddress)
{
    std::ifstream file(fileName);

    if (!file.is_open())
        return false;

    if (startAddress % 2 != 0 || startAddress >= 255)
        return false;

    std::string line;
    std::vector<std::string> words;

    while (std::getline(file, line))
    {
        size_t pos = line.find_first_not_of(" \t");

        if (pos == std::string::npos)
            continue;

        line = line.substr(pos);

        if (line[0] == ';')
            continue;

        std::string word = line.substr(0, 4);

        if (word.length() < 4)
            return false;

        for (char c : word)
        {
            if (!std::isxdigit(static_cast<unsigned char>(c)))
                return false;
        }

        words.push_back(word);
    }

    file.close();

    if (startAddress + words.size() * 2 > 256)
        return false;

    // Validate all instructions before loading them into memory
    for (const std::string& word : words)
    {
        unsigned int value = std::stoul(word, nullptr, 16);

        DecodedInstruction decoded = decoder.decode(
            static_cast<uint16_t>(value)
        );

        if (!decoded.isValid)
        {
            std::cout << "Invalid instruction found: "
                << word << '\n';

            return false;
        }
    }

    cpu = CPU();
    screen = Screen();

    int address = startAddress;

    for (const std::string& word : words)
    {
        unsigned int value = std::stoul(word, nullptr, 16);

        memory.write(address, (value >> 8) & 0xFF);

        memory.write(address + 1, value & 0xFF);

        address += 2;
    }

    cpu.setPC(startAddress);

    return true;
}
//function to set register value
void Simulator::setRegister(uint8_t index, uint8_t value)
{
    if (index >= 16)
    {
        std::cout << "Invalid Register Index!\n";
        return;
    }

    registers.write(index, value);

    std::cout << "Register updated successfully!\n";
}
//function to set memory cell value
void Simulator::setMemoryCell(uint8_t address, uint8_t value)
{
    memory.write(address, value);

    std::cout << "Memory cell updated successfully!\n";
}
//function to execute one instruction
void Simulator::displayStatus() const
{
    std::cout << "\n========== CPU STATUS ==========\n";

    std::cout << "PC: "
        << std::hex << std::uppercase
        << std::setw(2) << std::setfill('0')
        << (int)cpu.getPC() << '\n';

    std::cout << "IR: "
        << std::setw(4) << std::setfill('0')
        << cpu.getIR() << '\n';

    std::cout << "\n========== REGISTERS ==========\n";

    for (int i = 0; i < 16; i++)
    {
        std::cout << "R" << std::hex << i << ": "
            << std::setw(2) << std::setfill('0')
            << (int)registers.read(i) << '\n';
    }

    std::cout << "\n========== MEMORY ==========\n";

    std::cout << "    ";

    for (int col = 0; col < 16; col++)
    {
        std::cout << std::setw(2) << col << " ";
    }

    std::cout << '\n';

    for (int row = 0; row < 16; row++)
    {
        std::cout << std::setw(2) << row << "  ";

        for (int col = 0; col < 16; col++)
        {
            int address = row * 16 + col;

            std::cout << std::setw(2)
                << (int)memory.read(address)
                << " ";
        }

        std::cout << '\n';
    }

    std::cout << "\n========== SCREEN ==========\n";

    std::cout << screen.getOutput() << '\n';

    std::cout << "============================\n";

    std::cout << std::dec << std::setfill(' ');
}
void Simulator::step()
{
    if (cpu.isHalted())
        return;

    cpu.fetch(memory);

    if (cpu.isHalted())
        return;

    DecodedInstruction decoded =
        decoder.decode(cpu.getIR());

    if (!decoded.isValid)
    {
        std::cout << "Invalid Instruction!\n";
        cpu.halt();
        return;
    }

    Instruction* instruction = factory.create(decoded);

    if (instruction == nullptr)
    {
        std::cout << "Invalid Instruction!\n";
        cpu.halt();
        return;
    }

    ExecutionContext context{
        cpu, memory, registers, screen, alu
    };

    instruction->execute(context);

    delete instruction;
}
//function to run the program until halt
void Simulator::run()
{
    while (!cpu.isHalted())
    {
        step();
    }

    displayStatus();
}

//function to show menu
void Simulator::showMenu()
{
    int choice = -1;

    do
    {
        std::cout << "\n========== VOLE MACHINE SIMULATOR ==========\n";
        std::cout << "1. Load Program\n";
        std::cout << "2. Set Register\n";
        std::cout << "3. Set Memory Cell\n";
        std::cout << "4. Run Program\n";
        std::cout << "5. Execute Step by Step\n";
        std::cout << "6. Display Status\n";
        std::cout << "0. Exit\n";

        std::cout << "Enter your choice: ";
        std::cin >> std::dec >> choice;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n'
            );

            choice = -1;
            std::cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n'
        );

        switch (choice)
        {
        case 1:
        {
            std::string fileName;
            int startAddress;

            std::cout << "Enter file name: ";
            std::getline(std::cin, fileName);

            std::cout << "Enter start address (Hex 00-FF): ";
            std::cin >> std::hex >> startAddress;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n'
                );
                std::cout << "Invalid address!\n";
                break;
            }

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n'
            );
            std::cin >> std::dec;

            if (startAddress < 0 ||
                startAddress > 254 ||
                startAddress % 2 != 0)
            {
                std::cout << "Invalid start address!\n";
                break;
            }

            if (loadProgramFromFile(fileName, startAddress))
                std::cout << "Program loaded successfully!\n";
            else
                std::cout << "Failed to load program!\n";

            break;
        }

        case 2:
        {
            int index, value;

            std::cout << "Enter register index (0-F): ";
            std::cin >> std::hex >> index;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n'
                );
                std::cout << "Invalid register index!\n";
                break;
            }

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n'
            );

            std::cout << "Enter value (00-FF): ";
            std::cin >> std::hex >> value;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n'
                );
                std::cout << "Invalid value!\n";
                break;
            }

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n'
            );
            std::cin >> std::dec;

            if (index >= 0 && index < 16 &&
                value >= 0 && value <= 255)
            {
                setRegister(index, value);
            }
            else
            {
                std::cout << "Invalid register index or value!\n";
            }

            break;
        }

        case 3:
        {
            int address, value;

            std::cout << "Enter memory address (00-FF): ";
            std::cin >> std::hex >> address;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n'
                );
                std::cout << "Invalid address!\n";
                break;
            }

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n'
            );

            std::cout << "Enter value (00-FF): ";
            std::cin >> std::hex >> value;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n'
                );
                std::cout << "Invalid value!\n";
                break;
            }

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n'
            );
            std::cin >> std::dec;

            if (address >= 0 && address <= 255 &&
                value >= 0 && value <= 255)
            {
                setMemoryCell(address, value);
            }
            else
            {
                std::cout << "Invalid memory address or value!\n";
            }

            break;
        }

        case 4:
        {
            run();
            break;
        }

        case 5:
        {
            if (cpu.isHalted())
            {
                std::cout << "No program is currently running!\n";
                break;
            }

            while (!cpu.isHalted())
            {
                step();
                displayStatus();

                if (!cpu.isHalted())
                {
                    std::cout << "\nPress Enter to execute next step...";
                    std::string line;
                    std::getline(std::cin, line);
                }
            }

            std::cout << "\nProgram execution finished!\n";
            break;
        }

        case 6:
        {
            displayStatus();
            break;
        }

        case 0:
        {
            std::cout << "Exiting Simulator...\n";
            break;
        }

        default:
        {
            std::cout << "Invalid choice! Try again.\n";
        }
        }

    } while (choice != 0);
}