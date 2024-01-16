#include "io.h"

#include <iostream>

#include "spdlog/spdlog.h"

IO::IO() {}

IO::~IO() {}

const uint8_t IO::Read(const uint16_t addr) {
  switch (addr) {
    case 0xFF00:
      return GetJoypad();
    case 0xFF01:
      return serialData_;
    case 0xFF02:
      return serialControl_;
    case 0xFF04:
    case 0xFF05:
    case 0xFF06:
    case 0xFF07:
      return timer_->Read(addr);
    case 0xFF0F:
      return cpu_->Read(addr);
    case 0xFF40:
    case 0xFF41:
    case 0xFF42:
    case 0xFF43:
    case 0xFF44:
    case 0xFF45:
    case 0xFF46:
    case 0xFF47:
    case 0xFF48:
    case 0xFF49:
    case 0xFF4A:
    case 0xFF4B:
      return ppu_->Read(addr);
    case 0xFFFF:
      return cpu_->Read(addr);
    default:
      spdlog::warn("Unimplemented IO memory read: {:4X}", addr);
      break;
  }

  return 0;
}

void IO::Write(const uint16_t addr, const uint8_t value) {
  switch (addr) {
    case 0xFF00:
      joypad_ = value;
    case 0xFF01:
      serialData_ = value;
      break;
    case 0xFF02:
      serialControl_ = value;
      break;
    case 0xFF04:
    case 0xFF05:
    case 0xFF06:
    case 0xFF07:
      timer_->Write(addr, value);
      break;
    case 0xFF0F:
      cpu_->Write(addr, value);
      break;
    case 0xFF40:
    case 0xFF41:
    case 0xFF42:
    case 0xFF43:
    case 0xFF44:
    case 0xFF45:
    case 0xFF46:
    case 0xFF47:
    case 0xFF48:
    case 0xFF49:
    case 0xFF4A:
    case 0xFF4B:
      return ppu_->Write(addr, value);
    case 0xFFFF:
      cpu_->Write(addr, value);
      break;
    default:
      spdlog::warn("Unimplemented IO memory write: {:4X}", addr);
  }
}

void IO::UpdateJoypad(uint8_t button, bool set) {
  /* joypad_ &= 0x0F; */
  if (set) {
    joypad_ &= ~button;
  } else {
    joypad_ |= button;
  }
}

bool IO::ButtonSelect() { return !(joypad_ & kIOSelectButtons); }

bool IO::DPadSelect() { return !(joypad_ & kIOSelectDPad); }

uint8_t IO::GetJoypad() {
  uint8_t joypad = 0xCF;

  if (ButtonSelect()) {
    if (start_) {
      joypad &= ~kIOStartDown;
    }
    if (select_) {
      joypad &= ~kIOSelectUp;
    }
    if (b_) {
      joypad &= ~kIOBLeft;
    }
    if (a_) {
      joypad &= ~kIOARight;
    }
  }

  if (DPadSelect()) {
    if (down_) {
      joypad &= ~kIOStartDown;
    }
    if (up_) {
      joypad &= ~kIOSelectUp;
    }
    if (left_) {
      joypad &= ~kIOBLeft;
    }
    if (right_) {
      joypad &= ~kIOARight;
    }
  }

  return joypad;
}
