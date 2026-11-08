#include "ExecutionContext.h"

ExecutionContext::ExecutionContext(CPU& c, Memory& m, RegisterFile& r, Screen& s, ALU& a) : cpu(c), memory(m), registers(r), screen(s), alu(a)
{
}
