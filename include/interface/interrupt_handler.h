#pragma once

#include <cstdint>


const uint8_t kInterruptVBlank = 0x01 << 0;
const uint8_t kInterruptLCD = 0x01 << 1;
const uint8_t kInterruptTimer = 0x01 << 2;
const uint8_t kInterruptSerial = 0x01 << 3;
const uint8_t kInterruptJoypad = 0x01 << 4;


class InterruptHandler {
public:
    InterruptHandler() {};
    virtual ~InterruptHandler() {};

    virtual void Request(const uint8_t interruptType) = 0;
};
