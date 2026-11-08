#pragma once
#include <cstdint>
#include "CPU.h"
#include "ALU.h"
#include "Memory.h"
#include "Screen.h"

class CPU;
class Memory;
class RegisterFile;
class Screen;
class ALU;

class ExecutionContext
{
public:
	CPU& cpu;
	Memory& memory;
	RegisterFile& registers;
	Screen& screen;
	ALU& alu;

	ExecutionContext(CPU& c, Memory& m, RegisterFile& r, Screen& s, ALU& a);
	

};

