#pragma once
#include"DecodedInstruction.h"
#include"ExecutionContext.h"

class Instruction
{
protected:
    DecodedInstruction dec;
public:
    Instruction(DecodedInstruction d);
    virtual void execute(ExecutionContext& ctx) = 0;
    virtual ~Instruction() = default;
};
class AddIntInstruction : public Instruction {
public:
    AddIntInstruction(DecodedInstruction d) : Instruction(d) {}
    void execute(ExecutionContext& ctx) override;
    
};
    class AddFloatInstruction : public Instruction {
    public:
        AddFloatInstruction(DecodedInstruction d) : Instruction(d) {}
        void execute(ExecutionContext& ctx) override;
        
    };

    class OrInstruction : public Instruction {
    public:
        OrInstruction(DecodedInstruction d) : Instruction(d) {}
        void execute(ExecutionContext& ctx) override;
        
    };

    class AndInstruction : public Instruction {
    public:
        AndInstruction(DecodedInstruction d) : Instruction(d) {}
        void execute(ExecutionContext& ctx) override;
            
        
    };

    class XorInstruction : public Instruction {
    public:
        XorInstruction(DecodedInstruction d) : Instruction(d) {}
        void execute(ExecutionContext& ctx) override;
            
        
    };

    class RotateInstruction : public Instruction {
    public:
        RotateInstruction(DecodedInstruction d) : Instruction(d) {}
        void execute(ExecutionContext& ctx) override;
            
        
    };

    class JumpInstruction : public Instruction {
    public:
        JumpInstruction(DecodedInstruction d) : Instruction(d) {}
        void execute(ExecutionContext& ctx) override;
            
        
    };

    class HaltInstruction : public Instruction {
    public:
        HaltInstruction(DecodedInstruction d) : Instruction(d) {}
        void execute(ExecutionContext& ctx) override;
            
        
    };

    class LoadMemoryInstruction : public Instruction {
    public:
        LoadMemoryInstruction(DecodedInstruction d) : Instruction(d) {}
        void execute(ExecutionContext& ctx) override;
            
        
    };

    class LoadValueInstruction : public Instruction {
    public:
        LoadValueInstruction(DecodedInstruction d) : Instruction(d) {}
        void execute(ExecutionContext& ctx) override;
            
        
    };

    class StoreInstruction : public Instruction {
    public:
        StoreInstruction(DecodedInstruction d) : Instruction(d) {}
        void execute(ExecutionContext& ctx) override;
            
        
    };

    class MoveInstruction : public Instruction {
    public:
        MoveInstruction(DecodedInstruction z) : Instruction(z) {}
        void execute(ExecutionContext& ctx) override;
            
        
    };


