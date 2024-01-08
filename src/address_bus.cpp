#include "address_bus.h"

#include <iostream>


AddressBus::AddressBus() {}

AddressBus::~AddressBus() {}

const uint8_t AddressBus::Read(const uint16_t addr) {
    if (addr >= kRomBankStart && addr <= kRomBankEnd) {
        return cart_->Read(addr);
    } else if (addr >= kVramStart && addr <= kVramEnd) {
        return ppu_->Read(addr);
    } else if (addr >= kWramStart && addr <= kWramEnd) {
        return wram_[addr - kWramStart];
    } else if (addr >= kOamStart && addr <= kOamEnd) {
        return ppu_->Read(addr);
    } else if (addr >= kIoStart && addr <= kIoEnd) {
        return io_->Read(addr);
    } else if (addr >= kHramStart && addr <= kHramEnd) {
        return hram_[addr - kHramStart];
    } else if (addr == kInterruptFlags) {
        return io_->Read(addr);
    } else if (addr == kInterruptEnable) {
        return io_->Read(addr);
    }

    std::cout << "Unimplemented memory read: " << std::hex << addr << "\n";
    return 0xFF;
}

void AddressBus::Write(const uint16_t addr, const uint8_t value) {
    if (addr >= kRomBankStart && addr <= kRomBankEnd) {
        cart_->Write(addr, value);
    } else if (addr >= kVramStart && addr <= kVramEnd) {
        ppu_->Write(addr, value);
    } else if (addr >= kWramStart && addr <= kWramEnd) {
        wram_[addr - kWramStart] = value;
    } else if (addr >= kOamStart && addr <= kOamEnd) {
        ppu_->Write(addr, value);
    } else if (addr >= kIoStart && addr <= kIoEnd) {
        io_->Write(addr, value);
    } else if (addr >= kHramStart && addr <= kHramEnd) {
        hram_[addr - kHramStart] = value;
    } else if (addr == kInterruptFlags) {
        io_->Write(addr, value);
    } else if (addr == kInterruptEnable) {
        io_->Write(addr, value);
    } else {
        std::cout << "Unimplemented memory write: " << std::hex << addr << "\n";
    }
}
