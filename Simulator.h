#pragma once
#include <string>
#include <cstdint>
#include "CPU.h"
#include "Memory.h"
#include "RegisterFile.h"
#include "Screen.h"
#include "ALU.h"
#include "InstructionDecoder.h"
#include "CommandFactory.h"
#include "ExecutionContext.h"
class Simulator {
private:
    CPU   cpu;
    Memory  memory;
    RegisterFile registers;
    Screen  screen;
    ALU   alu;
    InstructionDecoder decoder;
    CommandFactory  factory;
public:
    bool loadProgramFromFile(const std::string& fileName, uint8_t startAddress);
        void setRegister(uint8_t index, uint8_t value);
    void setMemoryCell(uint8_t address, uint8_t value);
    void step();
    void run();
    void displayStatus() const;
        void showMenu();
};