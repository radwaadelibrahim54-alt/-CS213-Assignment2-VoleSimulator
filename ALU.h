#ifndef ALU_H
#define ALU_H

#include <cstdint>

class ALU {
public:
    uint8_t addInteger(uint8_t a, uint8_t b);
    uint8_t addFloat(uint8_t a, uint8_t b);
    uint8_t bitwiseOr(uint8_t a, uint8_t b);
    uint8_t bitwiseAnd(uint8_t a, uint8_t b);
    uint8_t bitwiseXor(uint8_t a, uint8_t b);
    uint8_t rotateRight(uint8_t v, int n);
};

#endif
