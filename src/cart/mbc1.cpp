#include "cart/mbc1.h"

#include "cart/constants.h"
#include "spdlog/spdlog.h"

MBC1Cart::MBC1Cart(std::vector<uint8_t>& cartridge) : Cart(cartridge) {
  if (romSize_ >= 1024) {
    spdlog::warn("1MiB MBC1 ROM not supported");
  }
}

MBC1Cart::~MBC1Cart() {}

const uint8_t MBC1Cart::Read(uint16_t addr) {
  switch (addr) {
    case kMbc1RomBankX0Start ... kMbc1RomBankX0End:
      return buffer_[addr];
    case kMbc1RomBankSwitchableStart ... kMbc1RomBankSwitchableEnd:
      return ReadRomBank(addr);
    case kMbc1RamBankSwitchableStart ... kMbc1RamBankSwitchableEnd:
      return ReadRamBank(addr);
  }

  return 0xFF;
}

void MBC1Cart::Write(uint16_t addr, uint8_t value) {
  switch (addr) {
    case kMbc1RamEnableStart ... kMbc1RamEnableEnd:
      // Any value with A as the lower nibble enables RAM, all other values
      // written here disable it
      ramEnable_ = ((value & 0x0A) == 0x0A);
      break;
    case kMbc1RomBankNumberStart ... kMbc1RomBankNumberEnd:
      romBankNumber_ = 0b00011111 & value;  // discard top 3 bits
      break;
    case kMbc1RamBankNumberStart ... kMbc1RamBankNumberEnd:
      ramBankNumber_ = 0b0011 & value;
      break;
    case kMbc1BankingModeSelectStart ... kMbc1BankingModeSelectEnd:
      bankingModeSelect_ = 0b01 & value;
      break;
    case kMbc1RamBankSwitchableStart ... kMbc1RamBankSwitchableEnd:
      WriteRamBank(addr, value);
      break;
    default:
      spdlog::warn("Unsupported MBC1 cart write to {:X}: {:X}", addr, value);
  }
}

const uint8_t MBC1Cart::ReadRomBank(const uint16_t addr) {
  if (romBankNumber_ <= 0x01) {  // 0x00 or 0x01 selects rom bank 1
    return buffer_[addr];
  }

  return buffer_[addr + (romBankNumber_ - 1) * kMbc1RomBankSwitchableStart];
}

const uint8_t MBC1Cart::ReadRamBank(const uint16_t addr) {
  if (ramEnable_) {
    uint16_t ramIndex =
        (ramBankNumber_ * kCartRamSize + (addr - kMbc1RamBankSwitchableStart));
    return ram_[ramIndex];
  }
  return 0xFF;
}

const uint8_t MBC1Cart::WriteRamBank(const uint16_t addr, const uint8_t value) {
  if (ramEnable_) {
    uint16_t ramIndex =
        (ramBankNumber_ * kCartRamSize + (addr - kMbc1RamBankSwitchableStart));
    ram_[ramIndex] = value;
  }
  return 0xFF;
}