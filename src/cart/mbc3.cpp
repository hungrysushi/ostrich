#include "cart/mbc3.h"

#include <chrono>

#include "cart/constants.h"
#include "spdlog/spdlog.h"

MBC3Cart::MBC3Cart(std::vector<uint8_t>& cartridge) : Cart(cartridge) {
  elapsedMs_ = 0;  // should try to keep this with save data
  auto now = std::chrono::high_resolution_clock::now();
  lastMeasuredMs_ = std::chrono::time_point_cast<std::chrono::milliseconds>(now)
                        .time_since_epoch()
                        .count();
}

MBC3Cart::~MBC3Cart() {}

const uint8_t MBC3Cart::Read(uint16_t addr) {
  switch (addr) {
    case kMbc3RomBank00Start ... kMbc3RomBank00End:
      return buffer_[addr];
    case kMbc3RomBankSwitchableStart ... kMbc3RomBankSwitchableEnd:
      return ReadRomBank(addr);
    case kMbc3RamBankSwitchableStart ... kMbc3RamBankSwitchableEnd:
      return ReadRamBankOrTimer(addr);
  }

  return 0xFF;
}

void MBC3Cart::Write(uint16_t addr, uint8_t value) {
  switch (addr) {
    case kMbc3RamAndTimerEnableStart ... kMbc3RamAndTimerEnableEnd:
      // Any value with A as the lower nibble enables RAM, all other values
      // written here disable it
      ramAndTimerEnable_ = ((value & 0x0A) == 0x0A);
      break;
    case kMbc3RomBankNumberStart ... kMbc3RomBankNumberEnd:
      romBankNumber_ = value;
      break;
    case kMbc3RamBankNumberStart ... kMbc3RamBankNumberEnd:
      ramBankNumber_ = value;
      break;
    case kMbc3LatchClockDataStart ... kMbc3LatchClockDataEnd:
      if (latchClockData_ == 0x00 && value == 0x01) {
        LatchRTC();
      }
      latchClockData_ = value;
      break;
    case kMbc3RamBankSwitchableStart ... kMbc3RamBankSwitchableEnd:
      WriteRamBankOrTimer(addr, value);
      break;
    default:
      spdlog::warn("Unsupported MBC3 cart write to {:X}: {:X}", addr, value);
  }
}

const uint8_t MBC3Cart::ReadRomBank(const uint16_t addr) {
  if (romBankNumber_ <= 0x01) {  // 0x00 or 0x01 selects rom bank 1
    return buffer_[addr];
  }

  return buffer_[addr + (romBankNumber_ - 1) * kMbc3RomBankSwitchableStart];
}

const uint8_t MBC3Cart::ReadRamBankOrTimer(const uint16_t addr) {
  // TODO fix latching
  if (ramAndTimerEnable_) {
    switch (ramBankNumber_) {
      case 0x00:
      case 0x01:
      case 0x02:
      case 0x03:
        return ram_[ramBankNumber_ * kCartRamSize +
                    (addr - kMbc3RamBankSwitchableStart)];
      case 0x08:
        return rtcS_;
      case 0x09:
        return rtcM_;
      case 0x0A:
        return rtcH_;
      case 0x0B:
        return rtcDL_;
      case 0x0C:
        return rtcDL_;
    }
  }

  return 0xFF;
}

void MBC3Cart::WriteRamBankOrTimer(const uint16_t addr, const uint8_t value) {
  if (ramAndTimerEnable_) {
    switch (ramBankNumber_) {
      case 0x00:
      case 0x01:
      case 0x02:
      case 0x03:
        ram_[ramBankNumber_ * kCartRamSize +
             (addr - kMbc3RamBankSwitchableStart)] = value;
        break;
      case 0x08:
        rtcS_ = Halted() ? value : rtcS_;
        break;
      case 0x09:
        rtcM_ = Halted() ? value : rtcM_;
        break;
      case 0x0A:
        rtcH_ = Halted() ? value : rtcH_;
        break;
      case 0x0B:
        rtcDL_ = Halted() ? value : rtcDL_;
        break;
      case 0x0C:
        rtcDL_ = Halted() ? value : rtcDH_;
        break;
    }
  }
}

void MBC3Cart::LatchRTC() {
  auto now = std::chrono::high_resolution_clock::now();
  uint64_t nowMs = std::chrono::time_point_cast<std::chrono::milliseconds>(now)
                       .time_since_epoch()
                       .count();

  elapsedMs_ += nowMs - lastMeasuredMs_;
  lastMeasuredMs_ = nowMs;

  rtcS_ = elapsedMs_ / 1000;
  rtcM_ = elapsedMs_ / (60 * 1000);
  rtcH_ = elapsedMs_ / (60 * 60 * 1000);
  uint32_t days = elapsedMs_ / (24 * 60 * 60 * 1000);
  rtcDL_ = days & 0xFF;
  rtcDH_ &= ~(0x01);
  rtcDH_ |= (days >> 8 & 0x01);
  // TODO carry
}

bool MBC3Cart::Halted() { return rtcDH_ & (0x01 << 6); }