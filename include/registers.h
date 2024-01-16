#pragma once

#include <cstdint>

const int kZeroFlagBit = 7;
const int kAddSubFlagBit = 6;
const int kHalfCarryFlagBit = 5;
const int kCarryFlagBit = 4;

enum class RegisterType {
  NONE,
  AF,
  BC,
  DE,
  HL,
  SP,
  PC,
  A,
  F,
  B,
  C,
  D,
  E,
  H,
  L,
};

class Registers {
 public:
  Registers() {}

  virtual ~Registers(){};

  uint16_t Read(RegisterType registerType) {
    switch (registerType) {
      case RegisterType::A:
        return A();
      case RegisterType::F:
        return Flags();
      case RegisterType::B:
        return B();
      case RegisterType::C:
        return C();
      case RegisterType::D:
        return D();
      case RegisterType::E:
        return E();
      case RegisterType::H:
        return H();
      case RegisterType::L:
        return L();
      case RegisterType::AF:
        return AF();
      case RegisterType::BC:
        return BC();
      case RegisterType::DE:
        return DE();
      case RegisterType::HL:
        return HL();
      case RegisterType::SP:
        return StackPointer();
      case RegisterType::PC:
        return ProgramCounter();
      default:
        return 0xFF;
    }
  }

  void Write(RegisterType registerType, uint16_t value) {
    switch (registerType) {
      case RegisterType::A:
        A() = (uint8_t)value & 0x00FF;
        break;
      case RegisterType::F:
        Flags() = (uint8_t)value & 0x00FF;
        break;
      case RegisterType::B:
        B() = (uint8_t)value & 0x00FF;
        break;
      case RegisterType::C:
        C() = (uint8_t)value & 0x00FF;
        break;
      case RegisterType::D:
        D() = (uint8_t)value & 0x00FF;
        break;
      case RegisterType::E:
        E() = (uint8_t)value & 0x00FF;
        break;
      case RegisterType::H:
        H() = (uint8_t)value & 0x00FF;
        break;
      case RegisterType::L:
        L() = (uint8_t)value & 0x00FF;
        break;
      case RegisterType::AF:
        AF() = value;  // do these need to be flipped?
        break;
      case RegisterType::BC:
        BC() = value;
        break;
      case RegisterType::DE:
        DE() = value;
        break;
      case RegisterType::HL:
        HL() = value;
        break;
      case RegisterType::SP:
        StackPointer() = value;
        break;
      case RegisterType::PC:
        ProgramCounter() = value;
        break;
      default:
        break;
    }
  }

  // 2 byte register accessors
  uint16_t& AF() { return *((uint16_t*)af_); }

  uint16_t& BC() { return *((uint16_t*)bc_); }

  uint16_t& DE() { return *((uint16_t*)de_); }

  uint16_t& HL() { return *((uint16_t*)hl_); }

  uint16_t& StackPointer() { return sp_; }

  uint16_t& ProgramCounter() { return pc_; }

  // accesss single byte registers
  uint8_t& A() { return af_[1]; }

  uint8_t& Flags() { return af_[0]; }

  uint8_t& B() { return bc_[1]; }

  uint8_t& C() { return bc_[0]; }

  uint8_t& D() { return de_[1]; }

  uint8_t& E() { return de_[0]; }

  uint8_t& H() { return hl_[1]; }

  uint8_t& L() { return hl_[0]; }

  // check flags
  bool GetZeroFlag() { return (Flags() >> kZeroFlagBit) & 0x1; }

  bool GetSubFlag() { return (Flags() >> kAddSubFlagBit) & 0x1; }

  bool GetHalfCarryFlag() { return (Flags() >> kHalfCarryFlagBit) & 0x1; }

  bool GetCarryFlag() { return (Flags() >> kCarryFlagBit) & 0x1; }

  // set/clear flags individually
  void SetZeroFlag() { Flags() |= (0x1 << kZeroFlagBit); }

  void ClearZeroFlag() { Flags() &= ~(0x1 << kZeroFlagBit); }

  void SetSubFlag() { Flags() |= (0x1 << kAddSubFlagBit); }

  void ClearSubFlag() { Flags() &= ~(0x1 << kAddSubFlagBit); }

  void SetHalfCarryFlag() { Flags() |= (0x1 << kHalfCarryFlagBit); }

  void ClearHalfCarryFlag() { Flags() &= ~(0x1 << kHalfCarryFlagBit); }

  void SetCarryFlag() { Flags() |= (0x1 << kCarryFlagBit); }

  void ClearCarryFlag() { Flags() &= ~(0x1 << kCarryFlagBit); }

  // set/clear by bool
  void SetZeroFlag(const bool b) { b ? SetZeroFlag() : ClearZeroFlag(); }

  void SetSubFlag(const bool b) { b ? SetSubFlag() : ClearSubFlag(); }

  void SetHalfCarryFlag(const bool b) {
    b ? SetHalfCarryFlag() : ClearHalfCarryFlag();
  }

  void SetCarryFlag(const bool b) { b ? SetCarryFlag() : ClearCarryFlag(); }

  uint8_t af_[2] = {0x00};  // accumulator and flags
  uint8_t bc_[2] = {0x00};
  uint8_t de_[2] = {0x00};
  uint8_t hl_[2] = {0x00};

  uint16_t sp_ = 0x0000;  // stack pointer
  uint16_t pc_ = 0x0000;  // program counter
};

constexpr const bool RegisterTypeIs16Bit(RegisterType type) {
  return (type >= RegisterType::AF && type <= RegisterType::PC);
}

constexpr const bool RegisterTypeIs8Bit(RegisterType type) {
  return (type >= RegisterType::A && type <= RegisterType::L);
}

constexpr const char* RegisterTypeToString(RegisterType type) {
  switch (type) {
    case RegisterType::NONE:
      return "NONE";
    case RegisterType::AF:
      return "AF";
    case RegisterType::BC:
      return "BC";
    case RegisterType::DE:
      return "DE";
    case RegisterType::HL:
      return "HL";
    case RegisterType::SP:
      return "SP";
    case RegisterType::PC:
      return "PC";
    case RegisterType::A:
      return "A";
    case RegisterType::F:
      return "F";
    case RegisterType::B:
      return "B";
    case RegisterType::C:
      return "C";
    case RegisterType::D:
      return "D";
    case RegisterType::E:
      return "E";
    case RegisterType::H:
      return "H";
    case RegisterType::L:
      return "L";
  }
};
