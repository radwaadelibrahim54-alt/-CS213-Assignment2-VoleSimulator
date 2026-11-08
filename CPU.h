#ifndef CPU_H
#define CPU_H
#include <cstdint>
#include "Memory.h"

class CPU {
private:
	uint8_t pc;
	uint16_t ir;
	bool halted;
public:
	CPU() {
		pc = 0;
		ir = 0;
		halted = false;
	}
	void fetch(const Memory& memory);
	void halt();

	bool isHalted() const {
		return halted;
	}
	void setPC(uint8_t address) {
		pc = address;
	}
	uint8_t getPC() const {
		return pc;
	}
	uint16_t getIR() const {
		return ir;
	}
};
#endif



