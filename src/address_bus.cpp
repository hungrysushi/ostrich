#include "address_bus.h"

#include <iostream>


AddressBus::AddressBus() {}

AddressBus::~AddressBus() {}

const uint8_t AddressBus::Read(const uint16_t addr) {
    if (addr >= kRomBank00Start && addr <= kRomBank00End) {
        return cart_->Read(addr);
    }

    std::cout << "Unimplemented memory read: " << std::hex << addr << "\n";
    return 0xFF;
}

void AddressBus::Write(const uint16_t addr, const uint8_t value) {
    if (addr >= kRomBank00Start && addr <= kRomBank00End) {
        return cart_->Write(addr, value);
    }

    std::cout << "Unimplemented memory write: " << std::hex << addr << "\n";
}
