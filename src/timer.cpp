#include "timer.h"

#include "spdlog/spdlog.h"

Timer::Timer() {}

Timer::~Timer() {}

void Timer::Tick() {
  uint16_t oldDiv =
      div_;  // detect time for divider by comparing different bits for change

  div_++;

  uint8_t clockSelect = tac_ & 0b0011;
  bool updateTima = false;
  switch (clockSelect) {
    case 0:  // every 1024 ticks
      updateTima = (oldDiv & (1 << 9)) && (!(div_ & (1 << 9)));
      break;
    case 1:  // every 16 ticks
      updateTima = (oldDiv & (1 << 3)) && (!(div_ & (1 << 3)));
      break;
    case 2:  // every 64
      updateTima = (oldDiv & (1 << 5)) && (!(div_ & (1 << 5)));
      break;
    case 3:  // every 256
      updateTima = (oldDiv & (1 << 7)) && (!(div_ & (1 << 7)));
      break;
  }

  if (updateTima && (tac_ & 0b0100)) {
    tima_++;

    if (tima_ == 0xFF) {
      tima_ = tma_;

      interruptHandler_->Request(kInterruptTimer);
    }
  }
}

const uint8_t Timer::Read(const uint16_t addr) {
  switch (addr) {
    case 0xFF04:
      return div_ >> 8;
    case 0xFF05:
      return tima_;
    case 0xFF06:
      return tma_;
    case 0xFF07:
      return tac_;
    default:
      spdlog::warn("Unimplemented Timer memory read: {:4X}", addr);
  }

  return 0;
}

void Timer::Write(const uint16_t addr, const uint8_t value) {
  switch (addr) {
    case 0xFF04:
      div_ = 0;
      break;
    case 0xFF05:
      tima_ = value;
      break;
    case 0xFF06:
      tma_ = value;
      break;
    case 0xFF07:
      tac_ = value;
      break;
    default:
      spdlog::warn("Unimplemented Timer memory write: {:4X}", addr);
  }
}
