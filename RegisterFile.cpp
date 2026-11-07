#include "RegisterFile.h"

RegisterFile::RegisterFile() {
    for (int i = 0; i < 16; ++i) {
        registers[i] = 0;
    }
}

uint8_t RegisterFile::read(uint8_t index) {
    if (index < 16) {
        return registers[index];
    }
    return 0; 
}

void RegisterFile::write(uint8_t index, uint8_t value) {
    if (index < 16) {
        registers[index] = value;
    }
}
