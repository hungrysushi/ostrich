#pragma once

#include <cstdint>
#include <vector>

#include "cart/cart.h"

const uint16_t kMbc1RomBankX0Start = 0x0000;
const uint16_t kMbc1RomBankX0End = 0x3FFF;

const uint16_t kMbc1RomBankSwitchableStart = 0x4000;
const uint16_t kMbc1RomBankSwitchableEnd = 0x7FFF;

const uint16_t kMbc1RamBankSwitchableStart = 0xA000;
const uint16_t kMbc1RamBankSwitchableEnd = 0xBFFF;

const uint16_t kMbc1RamEnableStart = 0x0000;
const uint16_t kMbc1RamEnableEnd = 0x1FFF;

const uint16_t kMbc1RomBankNumberStart = 0x2000;
const uint16_t kMbc1RomBankNumberEnd = 0x3FFF;

const uint16_t kMbc1RamBankNumberStart = 0x4000;
const uint16_t kMbc1RamBankNumberEnd = 0x5FFF;

const uint16_t kMbc1BankingModeSelectStart = 0x6000;
const uint16_t kMbc1BankingModeSelectEnd = 0x7FFF;

class MBC1Cart : public Cart {
 public:
  MBC1Cart(std::vector<uint8_t>& buffer);
  virtual ~MBC1Cart();

  virtual const uint8_t Read(uint16_t addr) override;
  virtual void Write(uint16_t addr, uint8_t value) override;

  const uint8_t ReadRomBank(const uint16_t addr);
  const uint8_t ReadRamBank(const uint16_t addr);
  const uint8_t WriteRamBank(const uint16_t addr, const uint8_t value);

  bool ramEnable_ = false;
  uint8_t romBankNumber_ = 0x00;
  uint8_t ramBankNumber_ = 0x00;
  bool bankingModeSelect_ = false;
};
