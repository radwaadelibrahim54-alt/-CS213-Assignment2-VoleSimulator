#pragma once
#include <cstdint>
#include "DecodedInstruction.h"

	class InstructionDecoder
	{
	public:
		DecodedInstruction decode(uint16_t raw);
	};


