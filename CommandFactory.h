#pragma once
#include"Instruction.h"
#include "DecodedInstruction.h"
class CommandFactory
{
public:
	Instruction* create(DecodedInstruction dec);
};

