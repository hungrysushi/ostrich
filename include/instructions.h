#pragma once

#include <cstdint>
#include <string_view>


enum class InstructionType {
    NONE,
    NOP,
    STOP,
    HALT,
    DI,
    EI,
    CB_PREFIX,
};


enum class ArgumentType {
    NONE,

};


enum class ConditionType {
    NONE,
};


struct Instruction {
    uint8_t opcode = 0x00;
    std::string_view mnemonic{"NONE"};
    InstructionType type = InstructionType::NONE;
    ArgumentType argType1 = ArgumentType::NONE;
    ArgumentType argType2 = ArgumentType::NONE;
    ConditionType condition = ConditionType::NONE;
};


struct InstructionContext {
    uint16_t pc;
    Instruction instruction;
};


static Instruction kInstructions[] = {
    // 0x
    {    0x00,    "NOP",         InstructionType::NOP, },
    {    0x01,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x02,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x03,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x04,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x05,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x06,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x07,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x08,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x09,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x0A,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x0B,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x0C,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x0D,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x0E,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x0F,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },

    // 1x
    {    0x10,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x11,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x12,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x13,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x14,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x15,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x16,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x17,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x18,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x19,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x1A,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x1B,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x1C,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x1D,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x1E,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x1F,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },

    // 2x
    {    0x20,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x21,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x22,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x23,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x24,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x25,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x26,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x27,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x28,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x29,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x2A,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x2B,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x2C,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x2D,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x2E,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x2F,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },

    // 3x
    {    0x30,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x31,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x32,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x33,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x34,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x35,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x36,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x37,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x38,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x39,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x3A,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x3B,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x3C,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x3D,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x3E,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x3F,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },

    // 4x
    {    0x40,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x41,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x42,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x43,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x44,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x45,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x46,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x47,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x48,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x49,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x4A,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x4B,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x4C,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x4D,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x4E,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x4F,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },

    // 5x
    {    0x50,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x51,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x52,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x53,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x54,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x55,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x56,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x57,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x58,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x59,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x5A,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x5B,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x5C,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x5D,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x5E,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x5F,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },

    // 6x
    {    0x60,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x61,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x62,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x63,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x64,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x65,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x66,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x67,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x68,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x69,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x6A,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x6B,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x6C,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x6D,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x6E,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x6F,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },

    // 7x
    {    0x70,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x71,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x72,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x73,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x74,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x75,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x76,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x77,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x78,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x79,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x7A,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x7B,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x7C,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x7D,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x7E,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x7F,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },

    // 8x
    {    0x80,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x81,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x82,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x83,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x84,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x85,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x86,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x87,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x88,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x89,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x8A,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x8B,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x8C,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x8D,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x8E,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x8F,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },

    // 9x
    {    0x90,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x91,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x92,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x93,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x94,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x95,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x96,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x97,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x98,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x99,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x9A,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x9B,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x9C,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x9D,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x9E,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0x9F,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },

    // Ax
    {    0xA0,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xA1,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xA2,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xA3,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xA4,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xA5,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xA6,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xA7,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xA8,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xA9,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xAA,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xAB,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xAC,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xAD,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xAE,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xAF,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },

    // Bx
    {    0xB0,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xB1,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xB2,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xB3,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xB4,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xB5,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xB6,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xB7,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xB8,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xB9,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xBA,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xBB,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xBC,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xBD,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xBE,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xBF,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },

    // Cx
    {    0xC0,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xC1,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xC2,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xC3,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xC4,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xC5,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xC6,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xC7,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xC8,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xC9,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xCA,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xCB,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xCC,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xCD,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xCE,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xCF,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },

    // Dx
    {    0xD0,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xD1,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xD2,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xD3,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xD4,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xD5,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xD6,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xD7,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xD8,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xD9,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xDA,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xDB,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xDC,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xDD,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xDE,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xDF,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },

    // Ex
    {    0xE0,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xE1,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xE2,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xE3,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xE4,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xE5,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xE6,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xE7,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xE8,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xE9,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xEA,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xEB,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xEC,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xED,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xEE,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xEF,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },

    // Fx
    {    0xF0,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xF1,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xF2,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xF3,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xF4,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xF5,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xF6,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xF7,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xF8,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xF9,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xFA,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xFB,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xFC,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xFD,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xFE,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
    {    0xFF,    "NONE",        InstructionType::NONE,       ArgumentType::NONE,     ArgumentType::NONE,     ConditionType::NONE },
};
