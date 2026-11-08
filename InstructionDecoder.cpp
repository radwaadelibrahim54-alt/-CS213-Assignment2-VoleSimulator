#include "InstructionDecoder.h"

DecodedInstruction InstructionDecoder::decode(uint16_t raw)
{
    DecodedInstruction result;

    result.opcode = (raw >> 12) & 0xF;
    result.r = (raw >> 8) & 0xF;
    result.s = (raw >> 4) & 0xF;
    result.t = raw & 0xF;
    result.xy = raw & 0xFF;

    result.isValid = (result.opcode >= 1 && result.opcode <= 12);

    if (result.opcode == 4 && result.r != 0) {
        result.isValid = false;
    }

    if (result.opcode == 10 && result.s != 0) {
        result.isValid = false;
    }
    if (result.opcode == 12 &&
        (result.r != 0 || result.s != 0 || result.t != 0)) {
        result.isValid = false;
    }
    return result;
}