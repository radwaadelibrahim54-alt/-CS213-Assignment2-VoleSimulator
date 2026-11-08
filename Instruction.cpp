
#include "Instruction.h"
#include "ExecutionContext.h"
#include"RegisterFile.h"

// Constructor
Instruction::Instruction(DecodedInstruction d) : dec(d)
{
}

// 1. Add Integer
void AddIntInstruction::execute(ExecutionContext& ctx)
{
    uint8_t val1 = ctx.registers.read(dec.s);
    uint8_t val2 = ctx.registers.read(dec.t);

    uint8_t result = ctx.alu.addInteger(val1, val2);

    ctx.registers.write(dec.r, result);
}

// 2. Add Floating Point
void AddFloatInstruction::execute(ExecutionContext& ctx)
{
    uint8_t val1 = ctx.registers.read(dec.s);
    uint8_t val2 = ctx.registers.read(dec.t);

    uint8_t result = ctx.alu.addFloat(val1, val2);

    ctx.registers.write(dec.r, result);
}

// 3. OR
void OrInstruction::execute(ExecutionContext& ctx)
{
    uint8_t val1 = ctx.registers.read(dec.s);
    uint8_t val2 = ctx.registers.read(dec.t);

    uint8_t result = ctx.alu.bitwiseOr(val1, val2);

    ctx.registers.write(dec.r, result);
}

// 4. AND
void AndInstruction::execute(ExecutionContext& ctx)
{
    uint8_t val1 = ctx.registers.read(dec.s);
    uint8_t val2 = ctx.registers.read(dec.t);

    uint8_t result = ctx.alu.bitwiseAnd(val1, val2);

    ctx.registers.write(dec.r, result);
}

// 5. XOR
void XorInstruction::execute(ExecutionContext& ctx)
{
    uint8_t val1 = ctx.registers.read(dec.s);
    uint8_t val2 = ctx.registers.read(dec.t);

    uint8_t result = ctx.alu.bitwiseXor(val1, val2);

    ctx.registers.write(dec.r, result);
}

// 6. Rotate Right
void RotateInstruction::execute(ExecutionContext& ctx)
{
    uint8_t value = ctx.registers.read(dec.r);

    // In AR0X, X is the last nibble (t)
    uint8_t steps = dec.t;

    uint8_t result = ctx.alu.rotateRight(value, steps);

    ctx.registers.write(dec.r, result);
}

// 7. Jump
void JumpInstruction::execute(ExecutionContext& ctx)
{
    uint8_t registerValue = ctx.registers.read(dec.r);
    uint8_t registerZero = ctx.registers.read(0);

    if (registerValue == registerZero)
    {
        ctx.cpu.setPC(dec.xy);
    }
}

// 8. Halt
void HaltInstruction::execute(ExecutionContext& ctx)
{
    ctx.cpu.halt();
}

// 9. Load from Memory
void LoadMemoryInstruction::execute(ExecutionContext& ctx)
{
    uint8_t value = ctx.memory.read(dec.xy);

    ctx.registers.write(dec.r, value);
}

// 10. Load Immediate Value
void LoadValueInstruction::execute(ExecutionContext& ctx)
{
    ctx.registers.write(dec.r, dec.xy);
}

// 11. Store
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

// 12. Move
void MoveInstruction::execute(ExecutionContext& ctx)
{
    // In 40RS: R is in s, and S is in t
    uint8_t value = ctx.registers.read(dec.s);

    ctx.registers.write(dec.t, value);
}