#include "cpu.h"

#include "spdlog/spdlog.h"


CPU::CPU() {

        Boot();
    }

CPU::~CPU() {

}

void CPU::Boot() {
    registers_.ProgramCounter() = 0x100;
    registers_.StackPointer() = 0xFFFE;

    registers_.A() = (uint8_t) 0x01;
    registers_.Flags() = (uint8_t) 0xB0;
    registers_.B() = (uint8_t) 0x00;
    registers_.C() = (uint8_t) 0x13;
    registers_.D() = (uint8_t) 0x00;
    registers_.E() = (uint8_t) 0xD8;
    registers_.H() = (uint8_t) 0x01;
    registers_.L() = (uint8_t) 0x4D;

    ie_ = 0;
    if_ = 0;
    ime_ = false;
    setImeNextCycle_ = false;
}

int CPU::Step() {
    if (halted_) {
        cycles_++;

        // resume if an interrupt has been requested
        if (if_) {
            halted_ = false;
        }
    } else {
        InstructionContext context;

        // fetch next instruction
        Fetch(context);

        if (context.instruction.type == InstructionType::NONE) {
            spdlog::warn("Unknown instruction: {:02X} {}", context.instruction.opcode, context.instruction.mnemonic);
            return -1;
        }

        Decode(context);

        Execute(context);
    }

    if (ime_) {
        // TODO handle interrupts
    }

    // set ime after 1 cycle delay
    if (setImeNextCycle_) {
        ime_ = true;
        setImeNextCycle_ = false;
    }

    return 1;
}

void CPU::Fetch(InstructionContext& context) {
    uint8_t opcode = memory_->Read(registers_.ProgramCounter()++);
    context.instruction = kInstructions[opcode];

    spdlog::trace("{:08X} PC[{:04X}] {:<8} - [ {:02X} {:02X} {:02X} {:02X} ] AF: {:02X}{:02X} BC:{:02X}{:02X} DE:{:02X}{:02X} HL:{:02X}{:02X}",
            cycles_,
            registers_.ProgramCounter(),
            context.instruction.mnemonic,
            opcode,
            memory_->Read(registers_.ProgramCounter()),
            memory_->Read(registers_.ProgramCounter() + 1),
            memory_->Read(registers_.ProgramCounter() + 2),
            registers_.A(),
            registers_.Flags(),
            registers_.B(),
            registers_.C(),
            registers_.D(),
            registers_.E(),
            registers_.H(),
            registers_.L());

    cycles_++;
}

void CPU::Decode(InstructionContext& context) {
}

void CPU::Execute(InstructionContext& context) {
    switch(context.instruction.type) {
        case InstructionType::NOP: _nop(context); break;
        case InstructionType::NONE:
        default:
            spdlog::warn("Opcode execute handler not found: {:02x} {}", context.instruction.opcode, context.instruction.mnemonic);
    }
}


void CPU::_nop(InstructionContext& context) { }
