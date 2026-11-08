#pragma once
#include <cstdint>
class DecodedInstruction
{
public:
	uint8_t opcode;
	uint8_t r;
	uint8_t s;
	uint8_t t;
	uint8_t xy;
	bool isValid;

};

