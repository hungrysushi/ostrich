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
    uint8_t opcode = memory_->Read(registers_.ProgramCounter());
    context.instruction = kInstructions[opcode];

    spdlog::trace("{:08X} PC[{:04X}] {:<12} - [ {:02X} {:02X} {:02X} {:02X} ]  Flags: {}{}{}{}  A: {:02X}  BC: {:02X}{:02X}  DE: {:02X}{:02X}  HL: {:02X}{:02X}",
            cycles_,
            registers_.ProgramCounter(),
            context.instruction.mnemonic,
            opcode,
            memory_->Read(registers_.ProgramCounter() + 1),
            memory_->Read(registers_.ProgramCounter() + 2),
            memory_->Read(registers_.ProgramCounter() + 3),
            registers_.GetZeroFlag() ? "Z" : "-",
            registers_.GetSubFlag() ? "N" : "-",
            registers_.GetHalfCarryFlag() ? "H" : "-",
            registers_.GetCarryFlag() ? "C" : "-",
            registers_.af_[1],
            registers_.bc_[1],
            registers_.bc_[0],
            registers_.de_[1],
            registers_.de_[0],
            registers_.hl_[1],
            registers_.hl_[0]);

    registers_.ProgramCounter()++;
    cycles_++;
}

void CPU::Decode(InstructionContext& context) {
    // fetch any data required
    context.source = _readData(context.instruction.source);
    /* context.arg2 = _readData(context.instruction.argType2); */
}

void CPU::Execute(InstructionContext& context) {
    switch(context.instruction.type) {
        case InstructionType::NOP: _nop(context); break;
        case InstructionType::JP: _jp(context); break;
        case InstructionType::XOR: _xor(context); break;
        case InstructionType::LD_16: _ld16(context); break;
        case InstructionType::LD: _ld(context); break;
        case InstructionType::DEC: _dec(context); break;
        case InstructionType::INC: _inc(context); break;
        case InstructionType::JR: _jr(context); break;
        case InstructionType::DI: _di(context); break;
        case InstructionType::EI: _ei(context); break;
        case InstructionType::LDH: _ldh(context); break;
        case InstructionType::HALT: _halt(context); break;
        case InstructionType::CP: _cp(context); break;
        case InstructionType::RST: _rst(context); break;
        case InstructionType::ADD: _add(context); break;
        case InstructionType::ADC: _adc(context); break;
        case InstructionType::POP: _pop(context); break;
        case InstructionType::SUB: _sub(context); break;
        case InstructionType::SBC: _sbc(context); break;
        case InstructionType::AND: _and(context); break;
        case InstructionType::OR: _or(context); break;
        case InstructionType::INC16: _inc16(context); break;
        case InstructionType::DEC16: _dec16(context); break;
        case InstructionType::ADD16: _add16(context); break;
        case InstructionType::PUSH: _push(context); break;
        case InstructionType::RLCA: _rlca(context); break;
        case InstructionType::RRCA: _rrca(context); break;
        case InstructionType::RLA: _rla(context); break;
        case InstructionType::RRA: _rra(context); break;
        case InstructionType::DAA: _daa(context); break;
        case InstructionType::CPL: _cpl(context); break;
        case InstructionType::SCF: _scf(context); break;
        case InstructionType::CCF: _ccf(context); break;
        case InstructionType::NONE:
        default:
            spdlog::critical("Opcode execute handler not found: {:02x} {}", context.instruction.opcode, context.instruction.mnemonic);
            exit(-1);

    }
}

const uint8_t CPU::Read(const uint16_t addr) {
    switch(addr) {
        case 0xFF0F:
            return if_;
        case 0xFFFF:
            return ie_;
        default:
            spdlog::warn("Unimplemented CPU register read: {:4X}", addr);
    }

    return 0;
}

void CPU::Write(const uint16_t addr, const uint8_t value) {
    switch(addr) {
        case 0xFF0F:
            if_ = value;
        case 0xFFFF:
            ie_ = value;
        default:
            spdlog::warn("Unimplemented CPU register write: {:4X}", addr);
    }
}

//--------
// handlers
void CPU::_nop(InstructionContext& context) { }

void CPU::_jp(InstructionContext& context) {
    if (_checkCondition(context.instruction.condition)) {
        registers_.ProgramCounter() = context.source;
        cycles_++;
    }
}

void CPU::_xor(InstructionContext& context) {
    registers_.A() ^= (context.source & 0xFF);

    registers_.SetZeroFlag(registers_.A() == 0);
    registers_.SetSubFlag(false);
    registers_.SetHalfCarryFlag(false);
    registers_.SetCarryFlag(false);
}

void CPU::_ld16(InstructionContext& context) {
    _writeData(context.instruction.destination, context.source);
}

void CPU::_ld(InstructionContext& context) {
    _writeData(context.instruction.destination, context.source);
}

void CPU::_dec(InstructionContext& context) {
    uint8_t value = (context.source & 0xFF) - 1;

    _writeData(context.instruction.source, value);

    registers_.SetZeroFlag(value == 0);
    registers_.SetSubFlag(true);
    registers_.SetHalfCarryFlag((value & 0x0F) == 0x0F);
}

void CPU::_inc(InstructionContext& context) {
    uint8_t value = (context.source & 0xFF) + 1;

    _writeData(context.instruction.source, value);

    registers_.SetZeroFlag(value == 0);
    registers_.SetSubFlag(false);
    registers_.SetHalfCarryFlag((value & 0x0F) == 0x00);
}

void CPU::_jr(InstructionContext& context) {
    if (_checkCondition(context.instruction.condition)) {
        int8_t offset = (int8_t) (context.source & 0xFF);

        registers_.ProgramCounter() += offset;
        cycles_++;
    }
}

void CPU::_di(InstructionContext& context) {
    ime_ = false;
}

void CPU::_ei(InstructionContext& context) {
    setImeNextCycle_ = true;
}

void CPU::_ldh(InstructionContext& context) {
    _writeData(context.instruction.destination, context.source);
}

void CPU::_halt(InstructionContext& context) {
    halted_ = true;
}

void CPU::_cp(InstructionContext& context) {
    int value = (int) registers_.A() - (int) context.source;

    registers_.SetZeroFlag(value == 0);
    registers_.SetSubFlag(true);
    registers_.SetHalfCarryFlag(((int) registers_.A() & 0x0F) - ((int) context.source & 0x0F) < 0);
    registers_.SetCarryFlag(value < 0);
}

void CPU::_rst(InstructionContext& context) {
    cycles_++; // not sure exactly where this cycle is spent

    uint8_t address = 0x00;
    switch(context.instruction.opcode) {
        case 0xC7: address = 0x00; break;
        case 0xCF: address = 0x08; break;
        case 0xD7: address = 0x10; break;
        case 0xDF: address = 0x18; break;
        case 0xE7: address = 0x20; break;
        case 0xEF: address = 0x28; break;
        case 0xF7: address = 0x30; break;
        case 0xFF: address = 0x38; break;
    }

    _savePCToStack();
    registers_.ProgramCounter() = address;
}

void CPU::_add(InstructionContext& context) {
    uint8_t value = registers_.A() + context.source;

    registers_.SetZeroFlag(value == 0);
    registers_.SetSubFlag(false);
    registers_.SetHalfCarryFlag((registers_.A() & 0xF) + (context.source & 0xF) >= 0x10);
    registers_.SetCarryFlag(((int32_t) registers_.A() & 0xFF) + ((int32_t) context.source & 0xFF) >= 0x100); // why does this have to be int?

    registers_.A() = value;
}

void CPU::_adc(InstructionContext& context) {
    uint8_t value = registers_.A() + context.source + (int) registers_.GetCarryFlag();

    registers_.SetZeroFlag((value & 0xFF) == 0);
    registers_.SetSubFlag(false);
    registers_.SetHalfCarryFlag((registers_.A() & 0x0F) + (context.source & 0x0F) + registers_.GetCarryFlag() > 0xF);
    registers_.SetCarryFlag(registers_.A() + context.source + registers_.GetCarryFlag() > 0xFF);

    registers_.A() = value;
}

void CPU::_pop(InstructionContext& context) {
    uint16_t data = _stackPopWord(); // consider doing this in the data fetch stage
    _writeData(context.instruction.destination, data);
}

void CPU::_sub(InstructionContext& context) {
    uint8_t value = registers_.A() - context.source;

    registers_.SetZeroFlag(value == 0);
    registers_.SetSubFlag(true);
    registers_.SetHalfCarryFlag(((int16_t) registers_.A() & 0x0F) - ((int16_t) context.source & 0x0F) < 0);
    registers_.SetCarryFlag(((int16_t) registers_.A()) - ((int16_t) context.source) < 0);

    registers_.A() = value;
}

void CPU::_sbc(InstructionContext& context) {
    // TODO double check this implementation
    uint8_t value = registers_.A() - context.source - (int) registers_.GetCarryFlag();

    registers_.SetZeroFlag(value == 0);
    registers_.SetSubFlag(true);
    registers_.SetHalfCarryFlag(((int16_t) registers_.A() & 0x0F) - ((int16_t) context.source & 0x0F) - (int) registers_.GetCarryFlag() < 0);
    registers_.SetCarryFlag(((int16_t) registers_.A()) - ((int16_t) context.source) - (int) registers_.GetCarryFlag() < 0);

    registers_.A() = value;
}

void CPU::_and(InstructionContext& context) {
    registers_.A() &= context.source & 0xFF;

    registers_.SetZeroFlag(registers_.A() == 0);
    registers_.SetSubFlag(false);
    registers_.SetHalfCarryFlag(true);
    registers_.SetCarryFlag(false);
}

void CPU::_or(InstructionContext& context) {
    registers_.A() |= context.source & 0xFF;

    registers_.SetZeroFlag(registers_.A() == 0);
    registers_.SetSubFlag(false);
    registers_.SetHalfCarryFlag(false);
    registers_.SetCarryFlag(false);
}

void CPU::_inc16(InstructionContext& context) {
    uint16_t value = context.source + 1;

    cycles_++;
    _writeData(context.instruction.source, value);
}

void CPU::_dec16(InstructionContext& context) {
    uint16_t value = context.source - 1;

    cycles_++;
    _writeData(context.instruction.source, value);
}

void CPU::_add16(InstructionContext& context) {
    uint16_t value = registers_.HL() + context.source;

    registers_.SetSubFlag(false);
    registers_.SetHalfCarryFlag((registers_.HL() & 0xFFF) + (context.source & 0xFFF) >= 0x1000);
    registers_.SetCarryFlag(((uint32_t) registers_.HL()) + ((uint32_t) context.source) >= 0x10000);

    cycles_++;
    registers_.HL() = value;
}

void CPU::_push(InstructionContext& context) {
    _stackPushWord(context.source);
    cycles_++;
}

void CPU::_rlca(InstructionContext& context) {
    bool carry = (registers_.A() >> 7) & 0x01; // check if leftmost bit is set

    registers_.A() = (registers_.A() << 1) | ((uint8_t) carry);
    registers_.SetZeroFlag(false);
    registers_.SetSubFlag(false);
    registers_.SetHalfCarryFlag(false);
    registers_.SetCarryFlag(carry);
}

void CPU::_rrca(InstructionContext& context) {
    bool carry = registers_.A() & 0x01; // check if rightmost bit is set

    registers_.A() = (registers_.A() >> 1) | ((uint8_t) carry << 7);
    registers_.SetZeroFlag(false);
    registers_.SetSubFlag(false);
    registers_.SetHalfCarryFlag(false);
    registers_.SetCarryFlag(carry);
}

void CPU::_rla(InstructionContext& context) {
    bool carry = (registers_.A() >> 7) & 0x01; // check if leftmost bit is set

    registers_.A() = (registers_.A() << 1) | ((uint8_t) registers_.GetCarryFlag());
    registers_.SetZeroFlag(false);
    registers_.SetSubFlag(false);
    registers_.SetHalfCarryFlag(false);
    registers_.SetCarryFlag(carry);
}

void CPU::_rra(InstructionContext& context) {
    bool carry = registers_.A() & 0x01;

    registers_.A() = (registers_.A() >> 1) | ((uint8_t) registers_.GetCarryFlag() << 7);
    registers_.SetZeroFlag(false);
    registers_.SetSubFlag(false);
    registers_.SetHalfCarryFlag(false);
    registers_.SetCarryFlag(carry);
}

void CPU::_daa(InstructionContext& context) {
    bool carryFlag = false;
    uint8_t value = 0;

    if (registers_.GetHalfCarryFlag() || (!registers_.GetSubFlag() && ((registers_.A() & 0x0F) > 9))) {
        value = 6;
    }

    if (registers_.GetCarryFlag() || (!registers_.GetSubFlag() && (registers_.A() > 0x99))) {
        value |= 0x60;  // ??
        carryFlag = true;
    }

    registers_.A() += registers_.GetSubFlag() ? -value : value;

    registers_.SetZeroFlag(registers_.A() == 0);
    registers_.SetHalfCarryFlag(false);
    registers_.SetCarryFlag(carryFlag);
}

void CPU::_cpl(InstructionContext& context) {
    registers_.A() = ~registers_.A();
    registers_.SetSubFlag(true);
    registers_.SetHalfCarryFlag(true);
}

void CPU::_scf(InstructionContext& context) {
    registers_.SetSubFlag(false);
    registers_.SetHalfCarryFlag(false);
    registers_.SetCarryFlag(true);
}

void CPU::_ccf(InstructionContext& context) {
    registers_.SetSubFlag(false);
    registers_.SetHalfCarryFlag(false);
    registers_.SetCarryFlag(registers_.GetCarryFlag() ^ 0x1);
}

//--------
// helpers
uint16_t CPU::_readData(ArgumentType argumentType) {
    uint16_t data;

    switch(argumentType) {
        case ArgumentType::IMM_16:
            data = _readImm16();
            break;
        case ArgumentType::B:
            data = registers_.B();
            break;
        case ArgumentType::C:
            data = registers_.C();
            break;
        case ArgumentType::D:
            data = registers_.D();
            break;
        case ArgumentType::E:
            data = registers_.E();
            break;
        case ArgumentType::H:
            data = registers_.H();
            break;
        case ArgumentType::L:
            data = registers_.L();
            break;
        case ArgumentType::MEM_AT_HL:
            data = _readMem(registers_.HL());
            break;
        case ArgumentType::A:
            data = registers_.A();
            break;
        case ArgumentType::BC:
            data = registers_.BC();
            break;
        case ArgumentType::DE:
            data = registers_.DE();
            break;
        case ArgumentType::HL:
            data = registers_.HL();
            break;
        case ArgumentType::SP:
            data = registers_.StackPointer();
            break;
        case ArgumentType::IMM_8:
            data = _readImm8();
            break;
        case ArgumentType::MEM_AT_BC:
            data = _readMem(registers_.BC());
            break;
        case ArgumentType::MEM_AT_DE:
            data = _readMem(registers_.DE());
            break;
        case ArgumentType::MEM_AT_HLI:
            data = _readMem(registers_.HL()++);
            break;
        case ArgumentType::MEM_AT_HLD:
            data = _readMem(registers_.HL()--);
            break;
        case ArgumentType::MEM_AT_A8:
            data = _readMem(0xFF00 | _readImm8());
            break;
        case ArgumentType::MEM_AT_C:
            data = _readMem(0xFF00 | registers_.C());
            break;
        case ArgumentType::MEM_AT_A16:
            data = _readMem(_readImm16());
            break;
        case ArgumentType::AF:
            data = registers_.AF();
            break;
        case ArgumentType::NONE: break;
        default:
            spdlog::warn("Unknown _readData ArgumentType");
    }

    return data;
}

uint16_t CPU::_readImm16() {
    uint8_t low = _readMem(registers_.ProgramCounter()++);
    uint8_t high = _readMem(registers_.ProgramCounter()++);

    return (high << 8) | low;
}

uint8_t CPU::_readImm8() {
    return _readMem(registers_.ProgramCounter()++);
}


uint8_t CPU::_readMem(uint16_t addr) {
    cycles_++;
    return memory_->Read(addr);
}

bool CPU::_checkCondition(ConditionType conditionType) {
    switch (conditionType) {
        case ConditionType::NZ: return !registers_.GetZeroFlag();
        case ConditionType::Z: return registers_.GetZeroFlag();
        case ConditionType::NC: return !registers_.GetCarryFlag();
        case ConditionType::C: return registers_.GetCarryFlag();
        case ConditionType::NONE:
        default:
            return true;
    }
}

void CPU::_writeData(ArgumentType argumentType, uint16_t data) {
    switch(argumentType) {
        /* case ArgumentType::IMM_16: */
        /*     spdlog::warn("Invalid _writeData argument type"); */
        /*     break; */
        case ArgumentType::B:
            registers_.B() = data & 0x00FF;
            break;
        case ArgumentType::C:
            registers_.C() = data & 0x00FF;
            break;
        case ArgumentType::D:
            registers_.D() = data & 0x00FF;
            break;
        case ArgumentType::E:
            registers_.E() = data & 0x00FF;
            break;
        case ArgumentType::H:
            registers_.H() = data & 0x00FF;
            break;
        case ArgumentType::L:
            registers_.L() = data & 0x00FF;
            break;
        case ArgumentType::MEM_AT_HL:
            _writeMem(registers_.HL(), data & 0x00FF);
            break;
        case ArgumentType::A:
            registers_.A() = data & 0x00FF;
            break;
        case ArgumentType::BC:
            registers_.BC() = data;
            break;
        case ArgumentType::DE:
            registers_.DE() = data;
            break;
        case ArgumentType::HL:
            registers_.HL() = data;
            break;
        case ArgumentType::SP:
            registers_.StackPointer() = data;
            break;
        /* case ArgumentType::IMM_8: */
        /*     spdlog::warn("Invalid _writeData argument type"); */
        /*     break; */
        case ArgumentType::MEM_AT_BC:
            _writeMem(registers_.BC(), data & 0x00FF);
            break;
        case ArgumentType::MEM_AT_DE:
            _writeMem(registers_.DE(), data & 0x00FF);
            break;
        case ArgumentType::MEM_AT_HLI:
            _writeMem(registers_.HL()++, data & 0x00FF);
            break;
        case ArgumentType::MEM_AT_HLD:
            _writeMem(registers_.HL()--, data & 0x00FF);
            break;
        case ArgumentType::MEM_AT_A8:
            _writeMem((0xFF00 | _readImm8()), data & 0x00FF);
            break;
        case ArgumentType::MEM_AT_C:
            _writeMem((0xFF00 | registers_.C()), data & 0x00FF);
            break;
        case ArgumentType::MEM_AT_A16:
            _writeMem(_readImm16(), data & 0x00FF);
            break;
        case ArgumentType::AF:
            registers_.AF() = data & 0xFFF0; // skip last nibble when writing to AF
            break;
        case ArgumentType::NONE: break;
        default:
            spdlog::warn("Unknown ArgumentType for _writeData");
    }
}

void CPU::_writeMem(uint16_t addr, uint8_t data) {
    cycles_++;
    memory_->Write(addr, data);
}

void CPU::_stackPush(const uint8_t data) {
    registers_.StackPointer()--;
    memory_->Write(registers_.StackPointer(), data);
    cycles_++;
}

void CPU::_stackPushWord(const uint16_t data) {
    _stackPush((uint8_t) ((data >> 8) & 0xFF));
    _stackPush((uint8_t) (data & 0xFF));
}

uint8_t CPU::_stackPop() {
    uint8_t data = memory_->Read(registers_.StackPointer()++);
    cycles_++;
    return data;
}

uint16_t CPU::_stackPopWord() {
    uint8_t low = _stackPop();
    uint8_t high = _stackPop();
    return (high << 8) | low;
}

void CPU::_savePCToStack() {
    _stackPushWord(registers_.ProgramCounter());
}
