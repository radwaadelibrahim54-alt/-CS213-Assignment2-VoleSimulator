#include "Instruction.h"
#include "ExecutionContext.h"
#include"RegisterFile.h"


Instruction::Instruction(DecodedInstruction d) : dec(d)
{
}


void AddIntInstruction::execute(ExecutionContext& ctx)
{
    uint8_t val1 = ctx.registers.read(dec.s);
    uint8_t val2 = ctx.registers.read(dec.t);

    uint8_t result = ctx.alu.addInteger(val1, val2);

    ctx.registers.write(dec.r, result);
}


void AddFloatInstruction::execute(ExecutionContext& ctx)
{
    uint8_t val1 = ctx.registers.read(dec.s);
    uint8_t val2 = ctx.registers.read(dec.t);

    uint8_t result = ctx.alu.addFloat(val1, val2);

    ctx.registers.write(dec.r, result);
}


void OrInstruction::execute(ExecutionContext& ctx)
{
    uint8_t val1 = ctx.registers.read(dec.s);
    uint8_t val2 = ctx.registers.read(dec.t);

    uint8_t result = ctx.alu.bitwiseOr(val1, val2);

    ctx.registers.write(dec.r, result);
}


void AndInstruction::execute(ExecutionContext& ctx)
{
    uint8_t val1 = ctx.registers.read(dec.s);
    uint8_t val2 = ctx.registers.read(dec.t);

    uint8_t result = ctx.alu.bitwiseAnd(val1, val2);

    ctx.registers.write(dec.r, result);
}


void XorInstruction::execute(ExecutionContext& ctx)
{
    uint8_t val1 = ctx.registers.read(dec.s);
    uint8_t val2 = ctx.registers.read(dec.t);

    uint8_t result = ctx.alu.bitwiseXor(val1, val2);

    ctx.registers.write(dec.r, result);
}


void RotateInstruction::execute(ExecutionContext& ctx)
{
    uint8_t value = ctx.registers.read(dec.r);

    
    uint8_t steps = dec.t;

    uint8_t result = ctx.alu.rotateRight(value, steps);

    ctx.registers.write(dec.r, result);
}


void JumpInstruction::execute(ExecutionContext& ctx)
{
    uint8_t registerValue = ctx.registers.read(dec.r);
    uint8_t registerZero = ctx.registers.read(0);

    if (registerValue == registerZero)
    {
        ctx.cpu.setPC(dec.xy);
    }
}


void HaltInstruction::execute(ExecutionContext& ctx)
{
    ctx.cpu.halt();
}


void LoadMemoryInstruction::execute(ExecutionContext& ctx)
{
    uint8_t value = ctx.memory.read(dec.xy);

    ctx.registers.write(dec.r, value);
}


void LoadValueInstruction::execute(ExecutionContext& ctx)
{
    ctx.registers.write(dec.r, dec.xy);
}


void StoreInstruction::execute(ExecutionContext& ctx)
{
    uint8_t value = ctx.registers.read(dec.r);

    if (dec.xy == 0xFF)
    {
        ctx.screen.writeByte(value);
    }
    else
    {
        ctx.memory.write(dec.xy, value);
    }
}


void MoveInstruction::execute(ExecutionContext& ctx)
{
    
    uint8_t value = ctx.registers.read(dec.s);

    ctx.registers.write(dec.t, value);
}
