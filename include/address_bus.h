#pragma once

#include "interface/addressable.h"

#include <cstdint>
#include <memory>
#include <vector>


const uint16_t kRomBank00Start = 0x0000;
const uint16_t kRomBank00End = 0x3FFF;

const uint16_t kWramStart = 0xC000;
const uint16_t kWramEnd = 0xDFFF; // TODO adjust this for CGB switchable bank

const uint16_t kHramStart = 0xFF80;
const uint16_t kHramEnd = 0xFFFE;

class AddressBus : public Addressable {
public:
        AddressBus();
        virtual ~AddressBus();

        const uint8_t Read(const uint16_t i);
        void Write(const uint16_t i, const uint8_t byte);

        std::shared_ptr<Addressable> cart_;
        std::vector<uint8_t> wram_ = std::vector<uint8_t>(0x2000);
        std::vector<uint8_t> hram_ = std::vector<uint8_t>(0x80);
};
