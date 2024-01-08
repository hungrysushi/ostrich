#pragma once

#include "interface/addressable.h"

#include <cstdint>
#include <memory>
#include <vector>


const uint16_t kRomBankStart = 0x0000;
const uint16_t kRomBankEnd = 0x7FFF;

const uint16_t kVramStart = 0x8000;
const uint16_t kVramEnd = 0x9FFF;

const uint16_t kWramStart = 0xC000;
const uint16_t kWramEnd = 0xDFFF; // TODO adjust this for CGB switchable bank

const uint16_t kOamStart = 0xFE00;
const uint16_t kOamEnd = 0xFE9F;

const uint16_t kIoStart = 0xFF00;
const uint16_t kIoEnd = 0xFF7F;

const uint16_t kHramStart = 0xFF80;
const uint16_t kHramEnd = 0xFFFE;

const uint16_t kInterruptFlags = 0xFF0F;
const uint16_t kInterruptEnable = 0xFFFF;


class AddressBus : public Addressable {
public:
        AddressBus();
        virtual ~AddressBus();

        const uint8_t Read(const uint16_t addr);
        void Write(const uint16_t addr, const uint8_t value);

        std::shared_ptr<Addressable> cart_;
        std::shared_ptr<Addressable> io_;
        std::shared_ptr<Addressable> ppu_;
        std::vector<uint8_t> wram_ = std::vector<uint8_t>(0x2000);
        std::vector<uint8_t> hram_ = std::vector<uint8_t>(0x80);
};
