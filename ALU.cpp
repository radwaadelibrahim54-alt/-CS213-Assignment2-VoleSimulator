#include "ALU.h"
#include <cmath>

double voleToDouble(uint8_t v) {
    int sign = (v >> 7) & 1;
    int exp = ((v >> 4) & 7) - 4;
    double mantissa = 0;
    for (int i = 0; i < 4; ++i) {
        if ((v >> (3 - i)) & 1) mantissa += std::pow(2, -(i + 1));
    }
    double val = mantissa * std::pow(2, exp);
    return sign ? -val : val;
}

uint8_t doubleToVole(double val) {
    if (val == 0.0) return 0;
    int sign = (val < 0) ? 1 : 0;
    val = std::abs(val);
    int exp = 0;
    
    while (val < 0.5 && exp > -4) { val *= 2; exp--; }
    while (val >= 1.0 && exp < 3) { val /= 2; exp++; }
    
    int mantissa = 0;
    for (int i = 0; i < 4; ++i) {
        val *= 2;
        if (val >= 1.0) {
            mantissa |= (1 << (3 - i));
            val -= 1.0;
        }
    }
    int stored_exp = exp + 4;
    return (sign << 7) | ((stored_exp & 7) << 4) | (mantissa & 15);
}

uint8_t ALU::addInteger(uint8_t a, uint8_t b) {
    return a + b;
}

uint8_t ALU::bitwiseOr(uint8_t a, uint8_t b) {
    return a | b;
}

uint8_t ALU::bitwiseAnd(uint8_t a, uint8_t b) {
    return a & b;
}

uint8_t ALU::bitwiseXor(uint8_t a, uint8_t b) {
    return a ^ b;
}

uint8_t ALU::rotateRight(uint8_t v, int n) {
    n = n % 8; 
    if (n == 0) return v;
    return (v >> n) | (v << (8 - n));
}

uint8_t ALU::addFloat(uint8_t a, uint8_t b) {
    double val1 = voleToDouble(a);
    double val2 = voleToDouble(b);
    return doubleToVole(val1 + val2);
}
