#pragma once

#include <cstdint>
#include <memory>

#include "interface/addressable.h"


const uint8_t kIOSelectButtons = 0x01 << 5;
const uint8_t kIOSelectDPad = 0x01 << 4;
const uint8_t kIOStartDown = 0x01 << 3;
const uint8_t kIOSelectUp = 0x01 << 2;
const uint8_t kIOBLeft = 0x01 << 1;
const uint8_t kIOARight = 0x01 << 0;


class IO : public Addressable {
public:
    IO();
    virtual ~IO();

    const uint8_t Read(const uint16_t addr);
    void Write(const uint16_t addr, const uint8_t value);

    void UpdateJoypad(uint8_t button, bool set);
    uint8_t GetJoypad();
    bool ButtonSelect();
    bool DPadSelect();

    std::shared_ptr<Addressable> timer_ = nullptr;
    std::shared_ptr<Addressable> cpu_ = nullptr;
    std::shared_ptr<Addressable> ppu_ = nullptr;

    uint8_t joypad_; // 0xFF00
    uint8_t serialData_; // 0xFF01
    uint8_t serialControl_; // 0xFF02

    bool a_ = false;
    bool b_ = false;
    bool up_ = false;
    bool down_ = false;
    bool left_ = false;
    bool right_ = false;
    bool start_ = false;
    bool select_ = false;
};
