#pragma once

#include <cstdint>

#include "interface/addressable.h"


class Timer : public Addressable {
public:
    Timer();
    virtual ~Timer();

    const uint8_t Read(const uint16_t addr);
    void Write(const uint16_t addr, const uint8_t value);

    void Tick();

    uint16_t div_ = 0xAC00; // 0xFF04, sort of
    uint8_t tima_; // 0xFF05
    uint8_t tma_; // 0xFF06
    uint8_t tac_; // 0xFF07
};
