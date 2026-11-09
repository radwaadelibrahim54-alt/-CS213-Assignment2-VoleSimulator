#include "CPU.h"
void CPU::halt() {
	halted = true;
}
void CPU::fetch(const Memory& memory) {
	int next = pc + 1;
	if (next > 255) {
		halt();
		return;
	}
	uint8_t high = memory.read(pc);
	uint8_t low = memory.read(next);
	ir = (high << 8) | low;
	pc += 2;

}