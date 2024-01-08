#pragma once

#include <cstdint>
#include <memory>

#include "interface/addressable.h"


class IO : public Addressable {
public:
    IO();
    virtual ~IO();

    const uint8_t Read(const uint16_t addr);
    void Write(const uint16_t addr, const uint8_t value);

    std::shared_ptr<Addressable> timer_ = nullptr;
    std::shared_ptr<Addressable> cpu_ = nullptr;
    std::shared_ptr<Addressable> ppu_ = nullptr;

    uint8_t serialData_; // 0xFF01
    uint8_t serialControl_; // 0xFF02
};
