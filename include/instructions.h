#pragma once

#include <cstdint>
#include <string_view>


enum class InstructionType {
    NONE,
    NOP,
    JP,
    XOR,
    LD_16,
    LD,
    DEC,
    INC,
    JR,
    DI,
    EI,
    LDH,
    HALT,
    CP,
    RST,
    ADD,
    ADC,
    POP,
    SUB,
    SBC,
    AND,
    OR,
    INC16,
    DEC16,
    ADD16,
    PUSH,
    RRCA,
    RLCA,
    RRA,
    RLA,
    DAA,
    CPL,
    SCF,
    CCF,
};


enum class ArgumentType {
    NONE,
    IMM_16,
    B,
    C,
    D,
    E,
    H,
    L,
    MEM_AT_HL,
    A,
    BC,
    DE,
    HL,
    SP,
    IMM_8,
    MEM_AT_BC,
    MEM_AT_DE,
    MEM_AT_HLD,
    MEM_AT_HLI,
    MEM_AT_A8, // E0, F0
    MEM_AT_C, // E2, F2
    MEM_AT_A16,
    AF,
};


enum class ConditionType {
    NONE,
    NC,
    NZ,
    Z,
    C,
};


struct Instruction {
    uint8_t opcode = 0x00;
    std::string_view mnemonic{"NONE"};
    InstructionType type = InstructionType::NONE;
    ArgumentType destination = ArgumentType::NONE;
    ArgumentType source = ArgumentType::NONE;
    ConditionType condition = ConditionType::NONE;
};


struct InstructionContext {
    uint16_t pc;
    Instruction instruction;
    bool is16Bit = false;
    uint16_t source = 0;
};


static Instruction kInstructions[] = {
    // 0x
    {    0x00,    "NOP",             InstructionType::NOP, },
    {    0x01,    "LD BC,d16",       InstructionType::LD_16,          ArgumentType::BC,               ArgumentType::IMM_16,           ConditionType::NONE },
    {    0x02,    "LD (BC),A",       InstructionType::LD,             ArgumentType::MEM_AT_BC,        ArgumentType::A,                ConditionType::NONE },
    {    0x03,    "INC BC",          InstructionType::INC16,          ArgumentType::NONE,             ArgumentType::BC,               ConditionType::NONE },
    {    0x04,    "INC B",           InstructionType::INC,            ArgumentType::NONE,             ArgumentType::B,                ConditionType::NONE },
    {    0x05,    "DEC B",           InstructionType::DEC,            ArgumentType::NONE,             ArgumentType::B,                ConditionType::NONE },
    {    0x06,    "LD B,d8",         InstructionType::LD,             ArgumentType::B,                ArgumentType::IMM_8,            ConditionType::NONE },
    {    0x07,    "RLCA",            InstructionType::RLCA,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },
    {    0x08,    "NONE",            InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },
    {    0x09,    "ADD HL,BC",       InstructionType::ADD16,          ArgumentType::HL,               ArgumentType::BC,               ConditionType::NONE },
    {    0x0A,    "LD A,(BC)",       InstructionType::LD,             ArgumentType::A,                ArgumentType::MEM_AT_BC,        ConditionType::NONE },
    {    0x03,    "DEC BC",          InstructionType::DEC16,          ArgumentType::NONE,             ArgumentType::BC,               ConditionType::NONE },
    {    0x0C,    "INC C",           InstructionType::INC,            ArgumentType::NONE,             ArgumentType::C,                ConditionType::NONE },
    {    0x0D,    "DEC C",           InstructionType::DEC,            ArgumentType::NONE,             ArgumentType::C,                ConditionType::NONE },
    {    0x0E,    "LD C,d8",         InstructionType::LD,             ArgumentType::C,                ArgumentType::IMM_8,            ConditionType::NONE },
    {    0x0F,    "RRCA",            InstructionType::RRCA,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },

    // 1x
    {    0x10,    "NONE",            InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },
    {    0x11,    "LD DE,d16",       InstructionType::LD_16,          ArgumentType::DE,               ArgumentType::IMM_16,           ConditionType::NONE },
    {    0x12,    "LD (DE),A",       InstructionType::LD,             ArgumentType::MEM_AT_DE,        ArgumentType::A,                ConditionType::NONE },
    {    0x13,    "INC DE",          InstructionType::INC16,          ArgumentType::NONE,             ArgumentType::DE,               ConditionType::NONE },
    {    0x14,    "INC D",           InstructionType::INC,            ArgumentType::NONE,             ArgumentType::D,                ConditionType::NONE },
    {    0x15,    "DEC D",           InstructionType::DEC,            ArgumentType::NONE,             ArgumentType::D,                ConditionType::NONE },
    {    0x16,    "LD D,d8",         InstructionType::LD,             ArgumentType::D,                ArgumentType::IMM_8,            ConditionType::NONE },
    {    0x17,    "RLA",             InstructionType::RLA,            ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },
    {    0x18,    "JR r8",           InstructionType::JR,             ArgumentType::NONE,             ArgumentType::IMM_8,            ConditionType::NONE },
    {    0x19,    "ADD HL,DE",       InstructionType::ADD16,          ArgumentType::HL,               ArgumentType::DE,               ConditionType::NONE },
    {    0x1A,    "LD A,(DE)",       InstructionType::LD,             ArgumentType::A,                ArgumentType::MEM_AT_DE,        ConditionType::NONE },
    {    0x1B,    "DEC DE",          InstructionType::DEC16,          ArgumentType::NONE,             ArgumentType::DE,               ConditionType::NONE },
    {    0x1C,    "INC E",           InstructionType::INC,            ArgumentType::NONE,             ArgumentType::E,                ConditionType::NONE },
    {    0x1D,    "DEC E",           InstructionType::DEC,            ArgumentType::NONE,             ArgumentType::E,                ConditionType::NONE },
    {    0x1E,    "LD E,d8",         InstructionType::LD,             ArgumentType::E,                ArgumentType::IMM_8,            ConditionType::NONE },
    {    0x1F,    "RRA",             InstructionType::RRA,            ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },

    // 2x
    {    0x20,    "JR NZ,r8",        InstructionType::JR,             ArgumentType::NONE,             ArgumentType::IMM_8,            ConditionType::NZ   },
    {    0x21,    "LD HL,d16",       InstructionType::LD_16,          ArgumentType::HL,               ArgumentType::IMM_16,           ConditionType::NONE },
    {    0x22,    "LD (HL+),A",      InstructionType::LD,             ArgumentType::MEM_AT_HLI,       ArgumentType::A,                ConditionType::NONE },
    {    0x13,    "INC HL",          InstructionType::INC16,          ArgumentType::NONE,             ArgumentType::HL,               ConditionType::NONE },
    {    0x24,    "INC H",           InstructionType::INC,            ArgumentType::NONE,             ArgumentType::H,                ConditionType::NONE },
    {    0x25,    "DEC H",           InstructionType::DEC,            ArgumentType::NONE,             ArgumentType::H,                ConditionType::NONE },
    {    0x26,    "LD H,d8",         InstructionType::LD,             ArgumentType::H,                ArgumentType::IMM_8,            ConditionType::NONE },
    {    0x27,    "DAA",             InstructionType::DAA,            ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },
    {    0x28,    "JR Z,r8",         InstructionType::JR,             ArgumentType::NONE,             ArgumentType::IMM_8,            ConditionType::Z    },
    {    0x29,    "ADD HL,HL",       InstructionType::ADD16,          ArgumentType::HL,               ArgumentType::HL,               ConditionType::NONE },
    {    0x2A,    "LD A,(HL+)",      InstructionType::LD,             ArgumentType::A,                ArgumentType::MEM_AT_HLI,       ConditionType::NONE },
    {    0x2B,    "DEC HL",          InstructionType::DEC16,          ArgumentType::NONE,             ArgumentType::HL,               ConditionType::NONE },
    {    0x2C,    "INC L",           InstructionType::INC,            ArgumentType::NONE,             ArgumentType::L,                ConditionType::NONE },
    {    0x2D,    "DEC L",           InstructionType::DEC,            ArgumentType::NONE,             ArgumentType::L,                ConditionType::NONE },
    {    0x2E,    "LD L,d8",         InstructionType::LD,             ArgumentType::L,                ArgumentType::IMM_8,            ConditionType::NONE },
    {    0x2F,    "CPL",             InstructionType::CPL,            ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },

    // 3x
    {    0x30,    "JR NC,r8",        InstructionType::JR,             ArgumentType::NONE,             ArgumentType::IMM_8,            ConditionType::NC   },
    {    0x31,    "LD SP,d16",       InstructionType::LD_16,          ArgumentType::SP,               ArgumentType::IMM_16,           ConditionType::NONE },
    {    0x32,    "LD (HL-),A",      InstructionType::LD,             ArgumentType::MEM_AT_HLD,       ArgumentType::A,                ConditionType::NONE },
    {    0x13,    "INC SP",          InstructionType::INC16,          ArgumentType::NONE,             ArgumentType::SP,               ConditionType::NONE },
    {    0x34,    "INC (HL)",        InstructionType::INC,            ArgumentType::NONE,             ArgumentType::MEM_AT_HL,        ConditionType::NONE },
    {    0x35,    "DEC (HL)",        InstructionType::DEC,            ArgumentType::NONE,             ArgumentType::MEM_AT_HL,        ConditionType::NONE },
    {    0x36,    "LD (HL),d8",      InstructionType::LD,             ArgumentType::MEM_AT_HL,        ArgumentType::IMM_8,            ConditionType::NONE },
    {    0x37,    "SCF",             InstructionType::SCF,            ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },
    {    0x38,    "JR C,r8",         InstructionType::JR,             ArgumentType::NONE,             ArgumentType::IMM_8,            ConditionType::C    },
    {    0x39,    "ADD HL,SP",       InstructionType::ADD16,          ArgumentType::HL,               ArgumentType::SP,               ConditionType::NONE },
    {    0x3A,    "LD A,(HL-)",      InstructionType::LD,             ArgumentType::A,                ArgumentType::MEM_AT_HLD,       ConditionType::NONE },
    {    0x3B,    "DEC SP",          InstructionType::DEC16,          ArgumentType::NONE,             ArgumentType::SP,               ConditionType::NONE },
    {    0x3C,    "INC A",           InstructionType::INC,            ArgumentType::NONE,             ArgumentType::A,                ConditionType::NONE },
    {    0x3D,    "DEC A",           InstructionType::DEC,            ArgumentType::NONE,             ArgumentType::A,                ConditionType::NONE },
    {    0x3E,    "LD A,d8",         InstructionType::LD,             ArgumentType::A,                ArgumentType::IMM_8,            ConditionType::NONE },
    {    0x3F,    "CCF",             InstructionType::CCF,            ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },

    // 4x
    {    0x40,    "LD B,B",          InstructionType::LD,             ArgumentType::B,                ArgumentType::B,                ConditionType::NONE },
    {    0x41,    "LD B,C",          InstructionType::LD,             ArgumentType::B,                ArgumentType::C,                ConditionType::NONE },
    {    0x42,    "LD B,D",          InstructionType::LD,             ArgumentType::B,                ArgumentType::D,                ConditionType::NONE },
    {    0x43,    "LD B,E",          InstructionType::LD,             ArgumentType::B,                ArgumentType::E,                ConditionType::NONE },
    {    0x44,    "LD B,H",          InstructionType::LD,             ArgumentType::B,                ArgumentType::H,                ConditionType::NONE },
    {    0x45,    "LD B,L",          InstructionType::LD,             ArgumentType::B,                ArgumentType::L,                ConditionType::NONE },
    {    0x46,    "LD B,(HL)",       InstructionType::LD,             ArgumentType::B,                ArgumentType::MEM_AT_HL,        ConditionType::NONE },
    {    0x47,    "LD B,A",          InstructionType::LD,             ArgumentType::B,                ArgumentType::A,                ConditionType::NONE },
    {    0x48,    "LD C,B",          InstructionType::LD,             ArgumentType::C,                ArgumentType::B,                ConditionType::NONE },
    {    0x49,    "LD C,C",          InstructionType::LD,             ArgumentType::C,                ArgumentType::C,                ConditionType::NONE },
    {    0x4A,    "LD C,D",          InstructionType::LD,             ArgumentType::C,                ArgumentType::D,                ConditionType::NONE },
    {    0x4B,    "LD C,E",          InstructionType::LD,             ArgumentType::C,                ArgumentType::E,                ConditionType::NONE },
    {    0x4C,    "LD C,H",          InstructionType::LD,             ArgumentType::C,                ArgumentType::H,                ConditionType::NONE },
    {    0x4D,    "LD C,L",          InstructionType::LD,             ArgumentType::C,                ArgumentType::L,                ConditionType::NONE },
    {    0x4E,    "LD C,(HL)",       InstructionType::LD,             ArgumentType::C,                ArgumentType::MEM_AT_HL,        ConditionType::NONE },
    {    0x4F,    "LD C,A",          InstructionType::LD,             ArgumentType::C,                ArgumentType::A,                ConditionType::NONE },

    // 5x
    {    0x50,    "LD D,B",          InstructionType::LD,             ArgumentType::D,                ArgumentType::B,                ConditionType::NONE },
    {    0x51,    "LD D,C",          InstructionType::LD,             ArgumentType::D,                ArgumentType::C,                ConditionType::NONE },
    {    0x52,    "LD D,D",          InstructionType::LD,             ArgumentType::D,                ArgumentType::D,                ConditionType::NONE },
    {    0x53,    "LD D,E",          InstructionType::LD,             ArgumentType::D,                ArgumentType::E,                ConditionType::NONE },
    {    0x54,    "LD D,H",          InstructionType::LD,             ArgumentType::D,                ArgumentType::H,                ConditionType::NONE },
    {    0x55,    "LD D,L",          InstructionType::LD,             ArgumentType::D,                ArgumentType::L,                ConditionType::NONE },
    {    0x56,    "LD D,(HL)",       InstructionType::LD,             ArgumentType::D,                ArgumentType::MEM_AT_HL,        ConditionType::NONE },
    {    0x57,    "LD D,A",          InstructionType::LD,             ArgumentType::D,                ArgumentType::A,                ConditionType::NONE },
    {    0x58,    "LD E,B",          InstructionType::LD,             ArgumentType::E,                ArgumentType::B,                ConditionType::NONE },
    {    0x59,    "LD E,C",          InstructionType::LD,             ArgumentType::E,                ArgumentType::C,                ConditionType::NONE },
    {    0x5A,    "LD E,D",          InstructionType::LD,             ArgumentType::E,                ArgumentType::D,                ConditionType::NONE },
    {    0x5B,    "LD E,E",          InstructionType::LD,             ArgumentType::E,                ArgumentType::E,                ConditionType::NONE },
    {    0x5C,    "LD E,H",          InstructionType::LD,             ArgumentType::E,                ArgumentType::H,                ConditionType::NONE },
    {    0x5D,    "LD E,L",          InstructionType::LD,             ArgumentType::E,                ArgumentType::L,                ConditionType::NONE },
    {    0x5E,    "LD E,(HL)",       InstructionType::LD,             ArgumentType::E,                ArgumentType::MEM_AT_HL,        ConditionType::NONE },
    {    0x5F,    "LD E,A",          InstructionType::LD,             ArgumentType::E,                ArgumentType::A,                ConditionType::NONE },

    // 6x
    {    0x60,    "LD H,B",          InstructionType::LD,             ArgumentType::H,                ArgumentType::B,                ConditionType::NONE },
    {    0x61,    "LD H,C",          InstructionType::LD,             ArgumentType::H,                ArgumentType::C,                ConditionType::NONE },
    {    0x62,    "LD H,D",          InstructionType::LD,             ArgumentType::H,                ArgumentType::D,                ConditionType::NONE },
    {    0x63,    "LD H,E",          InstructionType::LD,             ArgumentType::H,                ArgumentType::E,                ConditionType::NONE },
    {    0x64,    "LD H,H",          InstructionType::LD,             ArgumentType::H,                ArgumentType::H,                ConditionType::NONE },
    {    0x65,    "LD H,L",          InstructionType::LD,             ArgumentType::H,                ArgumentType::L,                ConditionType::NONE },
    {    0x66,    "LD H,(HL)",       InstructionType::LD,             ArgumentType::H,                ArgumentType::MEM_AT_HL,        ConditionType::NONE },
    {    0x67,    "LD H,A",          InstructionType::LD,             ArgumentType::H,                ArgumentType::A,                ConditionType::NONE },
    {    0x68,    "LD L,B",          InstructionType::LD,             ArgumentType::L,                ArgumentType::B,                ConditionType::NONE },
    {    0x69,    "LD L,C",          InstructionType::LD,             ArgumentType::L,                ArgumentType::C,                ConditionType::NONE },
    {    0x6A,    "LD L,D",          InstructionType::LD,             ArgumentType::L,                ArgumentType::D,                ConditionType::NONE },
    {    0x6B,    "LD L,E",          InstructionType::LD,             ArgumentType::L,                ArgumentType::E,                ConditionType::NONE },
    {    0x6C,    "LD L,H",          InstructionType::LD,             ArgumentType::L,                ArgumentType::H,                ConditionType::NONE },
    {    0x6D,    "LD L,L",          InstructionType::LD,             ArgumentType::L,                ArgumentType::L,                ConditionType::NONE },
    {    0x6E,    "LD L,(HL)",       InstructionType::LD,             ArgumentType::L,                ArgumentType::MEM_AT_HL,        ConditionType::NONE },
    {    0x6F,    "LD L,A",          InstructionType::LD,             ArgumentType::L,                ArgumentType::A,                ConditionType::NONE },

    // 7x
    {    0x70,    "LD (HL),B",       InstructionType::LD,             ArgumentType::MEM_AT_HL,        ArgumentType::B,                ConditionType::NONE },
    {    0x71,    "LD (HL),C",       InstructionType::LD,             ArgumentType::MEM_AT_HL,        ArgumentType::C,                ConditionType::NONE },
    {    0x72,    "LD (HL),D",       InstructionType::LD,             ArgumentType::MEM_AT_HL,        ArgumentType::D,                ConditionType::NONE },
    {    0x73,    "LD (HL),E",       InstructionType::LD,             ArgumentType::MEM_AT_HL,        ArgumentType::E,                ConditionType::NONE },
    {    0x74,    "LD (HL),H",       InstructionType::LD,             ArgumentType::MEM_AT_HL,        ArgumentType::H,                ConditionType::NONE },
    {    0x75,    "LD (HL),L",       InstructionType::LD,             ArgumentType::MEM_AT_HL,        ArgumentType::L,                ConditionType::NONE },
    {    0x76,    "HALT",            InstructionType::HALT,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },
    {    0x77,    "LD (HL),A",       InstructionType::LD,             ArgumentType::MEM_AT_HL,        ArgumentType::A,                ConditionType::NONE },
    {    0x78,    "LD A,B",          InstructionType::LD,             ArgumentType::A,                ArgumentType::B,                ConditionType::NONE },
    {    0x79,    "LD A,C",          InstructionType::LD,             ArgumentType::A,                ArgumentType::C,                ConditionType::NONE },
    {    0x7A,    "LD A,D",          InstructionType::LD,             ArgumentType::A,                ArgumentType::D,                ConditionType::NONE },
    {    0x7B,    "LD A,E",          InstructionType::LD,             ArgumentType::A,                ArgumentType::E,                ConditionType::NONE },
    {    0x7C,    "LD A,H",          InstructionType::LD,             ArgumentType::A,                ArgumentType::H,                ConditionType::NONE },
    {    0x7D,    "LD A,L",          InstructionType::LD,             ArgumentType::A,                ArgumentType::L,                ConditionType::NONE },
    {    0x7E,    "LD A,(HL)",       InstructionType::LD,             ArgumentType::A,                ArgumentType::MEM_AT_HL,        ConditionType::NONE },
    {    0x7F,    "LD A,A",          InstructionType::LD,             ArgumentType::A,                ArgumentType::A,                ConditionType::NONE },

    // 8x
    {    0x80,    "ADD A,B",         InstructionType::ADD,            ArgumentType::NONE,             ArgumentType::B,                ConditionType::NONE },
    {    0x81,    "ADD A,C",         InstructionType::ADD,            ArgumentType::NONE,             ArgumentType::C,                ConditionType::NONE },
    {    0x82,    "ADD A,D",         InstructionType::ADD,            ArgumentType::NONE,             ArgumentType::D,                ConditionType::NONE },
    {    0x83,    "ADD A,E",         InstructionType::ADD,            ArgumentType::NONE,             ArgumentType::E,                ConditionType::NONE },
    {    0x84,    "ADD A,H",         InstructionType::ADD,            ArgumentType::NONE,             ArgumentType::H,                ConditionType::NONE },
    {    0x85,    "ADD A,L",         InstructionType::ADD,            ArgumentType::NONE,             ArgumentType::L,                ConditionType::NONE },
    {    0x86,    "ADD A,(HL)",      InstructionType::ADD,            ArgumentType::NONE,             ArgumentType::MEM_AT_HL,        ConditionType::NONE },
    {    0x87,    "ADD A,A",         InstructionType::ADD,            ArgumentType::NONE,             ArgumentType::A,                ConditionType::NONE },
    {    0x88,    "ADC A,B",         InstructionType::ADC,            ArgumentType::NONE,             ArgumentType::B,                ConditionType::NONE },
    {    0x89,    "ADC A,C",         InstructionType::ADC,            ArgumentType::NONE,             ArgumentType::C,                ConditionType::NONE },
    {    0x8A,    "ADC A,D",         InstructionType::ADC,            ArgumentType::NONE,             ArgumentType::D,                ConditionType::NONE },
    {    0x8B,    "ADC A,E",         InstructionType::ADC,            ArgumentType::NONE,             ArgumentType::E,                ConditionType::NONE },
    {    0x8C,    "ADC A,H",         InstructionType::ADC,            ArgumentType::NONE,             ArgumentType::H,                ConditionType::NONE },
    {    0x8D,    "ADC A,L",         InstructionType::ADC,            ArgumentType::NONE,             ArgumentType::L,                ConditionType::NONE },
    {    0x8E,    "ADC A,(HL)",      InstructionType::ADC,            ArgumentType::NONE,             ArgumentType::MEM_AT_HL,        ConditionType::NONE },
    {    0x8F,    "ADC A,A",         InstructionType::ADC,            ArgumentType::NONE,             ArgumentType::A,                ConditionType::NONE },

    // 9x
    {    0x90,    "SUB A,B",         InstructionType::SUB,            ArgumentType::NONE,             ArgumentType::B,                ConditionType::NONE },
    {    0x91,    "SUB A,C",         InstructionType::SUB,            ArgumentType::NONE,             ArgumentType::C,                ConditionType::NONE },
    {    0x92,    "SUB A,D",         InstructionType::SUB,            ArgumentType::NONE,             ArgumentType::D,                ConditionType::NONE },
    {    0x93,    "SUB A,E",         InstructionType::SUB,            ArgumentType::NONE,             ArgumentType::E,                ConditionType::NONE },
    {    0x94,    "SUB A,H",         InstructionType::SUB,            ArgumentType::NONE,             ArgumentType::H,                ConditionType::NONE },
    {    0x95,    "SUB A,L",         InstructionType::SUB,            ArgumentType::NONE,             ArgumentType::L,                ConditionType::NONE },
    {    0x96,    "SUB A,(HL)",      InstructionType::SUB,            ArgumentType::NONE,             ArgumentType::MEM_AT_HL,        ConditionType::NONE },
    {    0x97,    "SUB A,A",         InstructionType::SUB,            ArgumentType::NONE,             ArgumentType::A,                ConditionType::NONE },
    {    0x98,    "SBC A,B",         InstructionType::SBC,            ArgumentType::NONE,             ArgumentType::B,                ConditionType::NONE },
    {    0x99,    "SBC A,C",         InstructionType::SBC,            ArgumentType::NONE,             ArgumentType::C,                ConditionType::NONE },
    {    0x9A,    "SBC A,D",         InstructionType::SBC,            ArgumentType::NONE,             ArgumentType::D,                ConditionType::NONE },
    {    0x9B,    "SBC A,E",         InstructionType::SBC,            ArgumentType::NONE,             ArgumentType::E,                ConditionType::NONE },
    {    0x9C,    "SBC A,H",         InstructionType::SBC,            ArgumentType::NONE,             ArgumentType::H,                ConditionType::NONE },
    {    0x9D,    "SBC A,L",         InstructionType::SBC,            ArgumentType::NONE,             ArgumentType::L,                ConditionType::NONE },
    {    0x9E,    "SBC A,(HL)",      InstructionType::SBC,            ArgumentType::NONE,             ArgumentType::MEM_AT_HL,        ConditionType::NONE },
    {    0x9F,    "SBC A,A",         InstructionType::SBC,            ArgumentType::NONE,             ArgumentType::A,                ConditionType::NONE },

    // Ax
    {    0xA0,    "AND A,B",         InstructionType::AND,            ArgumentType::NONE,             ArgumentType::B,                ConditionType::NONE },
    {    0xA1,    "AND A,C",         InstructionType::AND,            ArgumentType::NONE,             ArgumentType::C,                ConditionType::NONE },
    {    0xA2,    "AND A,D",         InstructionType::AND,            ArgumentType::NONE,             ArgumentType::D,                ConditionType::NONE },
    {    0xA3,    "AND A,E",         InstructionType::AND,            ArgumentType::NONE,             ArgumentType::E,                ConditionType::NONE },
    {    0xA4,    "AND A,H",         InstructionType::AND,            ArgumentType::NONE,             ArgumentType::H,                ConditionType::NONE },
    {    0xA5,    "AND A,L",         InstructionType::AND,            ArgumentType::NONE,             ArgumentType::L,                ConditionType::NONE },
    {    0xA6,    "AND A,(HL)",      InstructionType::AND,            ArgumentType::NONE,             ArgumentType::MEM_AT_HL,        ConditionType::NONE },
    {    0xA7,    "AND A,A",         InstructionType::AND,            ArgumentType::NONE,             ArgumentType::A,                ConditionType::NONE },
    {    0xA8,    "XOR B",           InstructionType::XOR,            ArgumentType::NONE,             ArgumentType::B,                ConditionType::NONE },
    {    0xA9,    "XOR C",           InstructionType::XOR,            ArgumentType::NONE,             ArgumentType::C,                ConditionType::NONE },
    {    0xAA,    "XOR D",           InstructionType::XOR,            ArgumentType::NONE,             ArgumentType::D,                ConditionType::NONE },
    {    0xAB,    "XOR E",           InstructionType::XOR,            ArgumentType::NONE,             ArgumentType::E,                ConditionType::NONE },
    {    0xAC,    "XOR H",           InstructionType::XOR,            ArgumentType::NONE,             ArgumentType::H,                ConditionType::NONE },
    {    0xAD,    "XOR L",           InstructionType::XOR,            ArgumentType::NONE,             ArgumentType::L,                ConditionType::NONE },
    {    0xAE,    "XOR (HL)",        InstructionType::XOR,            ArgumentType::NONE,             ArgumentType::MEM_AT_HL,        ConditionType::NONE },
    {    0xAF,    "XOR A",           InstructionType::XOR,            ArgumentType::NONE,             ArgumentType::A,                ConditionType::NONE },

    // Bx
    {    0xB0,    "OR A,B",          InstructionType::OR,             ArgumentType::NONE,             ArgumentType::B,                ConditionType::NONE },
    {    0xB1,    "OR A,C",          InstructionType::OR,             ArgumentType::NONE,             ArgumentType::C,                ConditionType::NONE },
    {    0xB2,    "OR A,D",          InstructionType::OR,             ArgumentType::NONE,             ArgumentType::D,                ConditionType::NONE },
    {    0xB3,    "OR A,E",          InstructionType::OR,             ArgumentType::NONE,             ArgumentType::E,                ConditionType::NONE },
    {    0xB4,    "OR A,H",          InstructionType::OR,             ArgumentType::NONE,             ArgumentType::H,                ConditionType::NONE },
    {    0xB5,    "OR A,L",          InstructionType::OR,             ArgumentType::NONE,             ArgumentType::L,                ConditionType::NONE },
    {    0xB6,    "OR A,(HL)",       InstructionType::OR,             ArgumentType::NONE,             ArgumentType::MEM_AT_HL,        ConditionType::NONE },
    {    0xB7,    "OR A,A",          InstructionType::OR,             ArgumentType::NONE,             ArgumentType::A,                ConditionType::NONE },
    {    0xB8,    "CP B",            InstructionType::CP,             ArgumentType::NONE,             ArgumentType::B,                ConditionType::NONE },
    {    0xB9,    "CP C",            InstructionType::CP,             ArgumentType::NONE,             ArgumentType::C,                ConditionType::NONE },
    {    0xBA,    "CP D",            InstructionType::CP,             ArgumentType::NONE,             ArgumentType::D,                ConditionType::NONE },
    {    0xBB,    "CP E",            InstructionType::CP,             ArgumentType::NONE,             ArgumentType::E,                ConditionType::NONE },
    {    0xBC,    "CP H",            InstructionType::CP,             ArgumentType::NONE,             ArgumentType::H,                ConditionType::NONE },
    {    0xBD,    "CP L",            InstructionType::CP,             ArgumentType::NONE,             ArgumentType::L,                ConditionType::NONE },
    {    0xBE,    "CP (HL)",         InstructionType::CP,             ArgumentType::NONE,             ArgumentType::MEM_AT_HL,        ConditionType::NONE },
    {    0xBF,    "CP A",            InstructionType::CP,             ArgumentType::NONE,             ArgumentType::A,                ConditionType::NONE },

    // Cx
    {    0xC0,    "NONE",            InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },
    {    0xC1,    "POP BC",          InstructionType::POP,            ArgumentType::BC,               ArgumentType::NONE,             ConditionType::NONE },
    {    0xC2,    "JP NZ,a16",       InstructionType::JP,             ArgumentType::NONE,             ArgumentType::IMM_16,           ConditionType::NZ   },
    {    0xC3,    "JP a16",          InstructionType::JP,             ArgumentType::NONE,             ArgumentType::IMM_16,           ConditionType::NONE },
    {    0xC4,    "NONE",            InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },
    {    0xC5,    "PUSH BC",         InstructionType::PUSH,           ArgumentType::NONE,             ArgumentType::BC,               ConditionType::NONE },
    {    0xC6,    "ADD A,u8",        InstructionType::ADD,            ArgumentType::NONE,             ArgumentType::IMM_8,            ConditionType::NONE },
    {    0xC7,    "RST 00h",         InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },
    {    0xC8,    "NONE",            InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },
    {    0xC9,    "NONE",            InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },
    {    0xCA,    "JP Z,a16",        InstructionType::JP,             ArgumentType::NONE,             ArgumentType::IMM_16,           ConditionType::Z    },
    {    0xCB,    "NONE",            InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },
    {    0xCC,    "NONE",            InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },
    {    0xCD,    "NONE",            InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },
    {    0xCE,    "ADC A,u8",        InstructionType::ADC,            ArgumentType::NONE,             ArgumentType::IMM_8,            ConditionType::NONE },
    {    0xCF,    "RST 08h",         InstructionType::RST,            ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },

    // Dx
    {    0xD0,    "NONE",            InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },
    {    0xD1,    "POP DE",          InstructionType::POP,            ArgumentType::DE,               ArgumentType::NONE,             ConditionType::NONE },
    {    0xD2,    "JP NC,a16",       InstructionType::JP,             ArgumentType::NONE,             ArgumentType::IMM_16,           ConditionType::NC   },
    {    0xD3,    "NONE",            InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },  // no instruction
    {    0xD4,    "NONE",            InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },
    {    0xD5,    "PUSH DE",         InstructionType::PUSH,           ArgumentType::NONE,             ArgumentType::DE,               ConditionType::NONE },
    {    0xD6,    "SUB A,d8",        InstructionType::SUB,            ArgumentType::NONE,             ArgumentType::IMM_8,            ConditionType::NONE },
    {    0xD7,    "RST 10h",         InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },
    {    0xD8,    "NONE",            InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },
    {    0xD9,    "NONE",            InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },
    {    0xDA,    "JP C,a16",        InstructionType::JP,             ArgumentType::NONE,             ArgumentType::IMM_16,           ConditionType::C    },
    {    0xDB,    "NONE",            InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },  // no instruction
    {    0xDC,    "NONE",            InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },
    {    0xDD,    "NONE",            InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },  // no instruction
    {    0xDE,    "SBC A,d8",        InstructionType::SBC,            ArgumentType::NONE,             ArgumentType::IMM_8,            ConditionType::NONE },
    {    0xDF,    "RST 18h",         InstructionType::RST,            ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },

    // Ex
    {    0xE0,    "LDH (a8),A",      InstructionType::LDH,            ArgumentType::MEM_AT_A8,        ArgumentType::A,                ConditionType::NONE },
    {    0xE1,    "POP HL",          InstructionType::POP,            ArgumentType::HL,               ArgumentType::NONE,             ConditionType::NONE },
    {    0xE2,    "LDH (C),A",       InstructionType::LDH,            ArgumentType::MEM_AT_C,         ArgumentType::A,                ConditionType::NONE },
    {    0xE3,    "NONE",            InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },  // no instruction
    {    0xE4,    "NONE",            InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },  // no instruction
    {    0xE5,    "PUSH HL",         InstructionType::PUSH,           ArgumentType::NONE,             ArgumentType::HL,               ConditionType::NONE },
    {    0xE6,    "AND A,u8",        InstructionType::AND,            ArgumentType::NONE,             ArgumentType::IMM_8,            ConditionType::NONE },
    {    0xE7,    "RST 20h",         InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },
    {    0xE8,    "NONE",            InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },
    {    0xE9,    "JP HL",           InstructionType::JP,             ArgumentType::NONE,             ArgumentType::HL,               ConditionType::NONE },
    {    0xEA,    "LD (a16),A",      InstructionType::LD,             ArgumentType::MEM_AT_A16,       ArgumentType::A,                ConditionType::NONE },
    {    0xEB,    "NONE",            InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },  // no instruction
    {    0xEC,    "NONE",            InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },  // no instruction
    {    0xED,    "NONE",            InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },  // no instruction
    {    0xEE,    "XOR d8",          InstructionType::XOR,            ArgumentType::NONE,             ArgumentType::IMM_8,            ConditionType::NONE },
    {    0xEF,    "RST 28h",         InstructionType::RST,            ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },

    // Fx
    {    0xF0,    "LDH A,(a8)",      InstructionType::LDH,            ArgumentType::A,                ArgumentType::MEM_AT_A8,        ConditionType::NONE },
    {    0xF1,    "POP AF",          InstructionType::POP,            ArgumentType::AF,               ArgumentType::NONE,             ConditionType::NONE },
    {    0xF2,    "LDH A,(C)",       InstructionType::LDH,            ArgumentType::A,                ArgumentType::MEM_AT_C,         ConditionType::NONE },
    {    0xF3,    "DI",              InstructionType::DI,             ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },
    {    0xF4,    "NONE",            InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },  // no instruction
    {    0xF5,    "PUSH SP",         InstructionType::PUSH,           ArgumentType::NONE,             ArgumentType::SP,               ConditionType::NONE },
    {    0xF6,    "OR A,u8",         InstructionType::OR,             ArgumentType::NONE,             ArgumentType::IMM_8,            ConditionType::NONE },
    {    0xF7,    "RST 30h",         InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },
    {    0xF8,    "NONE",            InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },
    {    0xF9,    "NONE",            InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },
    {    0xFA,    "LD A,(a16)",      InstructionType::LD,             ArgumentType::A,                ArgumentType::MEM_AT_A16,       ConditionType::NONE },
    {    0xFB,    "NONE",            InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },
    {    0xFC,    "NONE",            InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },  // no instruction
    {    0xFD,    "NONE",            InstructionType::NONE,           ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },  // no instruction
    {    0xFE,    "CP d8",           InstructionType::CP,             ArgumentType::NONE,             ArgumentType::IMM_8,            ConditionType::NONE },
    {    0xFF,    "RST 38h",         InstructionType::RST,            ArgumentType::NONE,             ArgumentType::NONE,             ConditionType::NONE },
};
