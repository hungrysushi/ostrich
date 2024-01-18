#pragma once

#include <cstdint>
#include <vector>

#include "cart/cart.h"

const uint16_t kMbc3RomBank00Start = 0x0000;
const uint16_t kMbc3RomBank00End = 0x3FFF;

const uint16_t kMbc3RomBankSwitchableStart = 0x4000;
const uint16_t kMbc3RomBankSwitchableEnd = 0x7FFF;

const uint16_t kMbc3RamBankSwitchableStart = 0xA000;
const uint16_t kMbc3RamBankSwitchableEnd = 0xBFFF;

const uint16_t kMbc3RamAndTimerEnableStart = 0x0000;
const uint16_t kMbc3RamAndTimerEnableEnd = 0x1FFF;

const uint16_t kMbc3RomBankNumberStart = 0x2000;
const uint16_t kMbc3RomBankNumberEnd = 0x3FFF;

const uint16_t kMbc3RamBankNumberStart = 0x4000;
const uint16_t kMbc3RamBankNumberEnd = 0x5FFF;

const uint16_t kMbc3LatchClockDataStart = 0x6000;
const uint16_t kMbc3LatchClockDataEnd = 0x7FFF;

class MBC3Cart : public Cart {
 public:
  MBC3Cart(std::vector<uint8_t>& buffer);
  virtual ~MBC3Cart();

  virtual const uint8_t Read(uint16_t addr) override;
  virtual void Write(uint16_t addr, uint8_t value) override;

  const uint8_t ReadRomBank(const uint16_t addr);
  const uint8_t ReadRamBankOrTimer(const uint16_t addr);
  void WriteRamBankOrTimer(const uint16_t addr, const uint8_t value);
  void LatchRTC();

  bool Halted();

  // registers
  bool ramAndTimerEnable_ = false;
  uint8_t romBankNumber_ = 0x00;
  uint8_t ramBankNumber_ = 0x00;
  bool bankingModeSelect_ = false;
  uint8_t latchClockData_ = 0x00;
  // 0x08-0x0C
  uint8_t rtcS_ = 0x00;
  uint8_t rtcM_ = 0x00;
  uint8_t rtcH_ = 0x00;
  uint8_t rtcDL_ = 0x00;
  uint8_t rtcDH_ = 0x00;

  uint64_t lastMeasuredMs_;
  uint64_t elapsedMs_;
};
