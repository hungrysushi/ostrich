#include "address_bus.h"

#include <iostream>


AddressBus::AddressBus() {}

AddressBus::~AddressBus() {}

const uint8_t AddressBus::Read(const uint16_t addr) {
    if (addr >= kRomBank00Start && addr <= kRomBank00End) {
        return cart_->Read(addr);
    } else if (addr >= kWramStart && addr <= kWramEnd) {
        return wram_[addr - kWramStart];
    } else if (addr >= kHramStart && addr <= kHramEnd) {
        return hram_[addr - kHramStart];
    }

    std::cout << "Unimplemented memory read: " << std::hex << addr << "\n";
    return 0xFF;
}

void AddressBus::Write(const uint16_t addr, const uint8_t value) {
    if (addr >= kRomBank00Start && addr <= kRomBank00End) {
        cart_->Write(addr, value);
    } else if (addr >= kWramStart && addr <= kWramEnd) {
        wram_[addr - kWramStart] = value;
    } else if (addr >= kHramStart && addr <= kHramEnd) {
        hram_[addr - kHramStart] = value;
    } else {
        std::cout << "Unimplemented memory write: " << std::hex << addr << "\n";
    }
}
