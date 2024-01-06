#pragma once

#include "interface/addressable.h"

#include <cstdint>
#include <memory>


const uint16_t kRomBank00Start = 0x0000;
const uint16_t kRomBank00End = 0x3FFF;


class AddressBus : public Addressable {
public:
        AddressBus();
        virtual ~AddressBus();

        const uint8_t Read(const uint16_t i);
        void Write(const uint16_t i, const uint8_t byte);

        std::shared_ptr<Addressable> cart_;
};
