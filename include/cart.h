#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "interface/addressable.h"


const uint16_t kEntryStart = 0x100;
const uint16_t kEntrySize = 0x04;
const uint16_t kLogoStart = 0x104;
const uint16_t kLogoSize = 0x30;
const uint16_t kTitleStart = 0x134;
const uint16_t kTitleSize = 16;
const uint16_t kNewLicenseeStart = 0x144;
const uint16_t kSbgFlag = 0x146;
const uint16_t kCartType = 0x147;
const uint16_t kRomSize = 0x148;
const uint16_t kRamSize = 0x149;
const uint16_t kDestinationCode = 0x14A;
const uint16_t kOldLicenseeCode = 0x14B;
const uint16_t kRomVersion = 0x14C;
const uint16_t kHeaderChecksum = 0x14D;
const uint16_t kGlobalChecksum = 0x14E;


class Cart : public Addressable {
    public:
        Cart(std::vector<uint8_t>& buffer);
        virtual ~Cart();

        const std::string Describe();
        const uint8_t Read(uint16_t addr);
        void Write(uint16_t addr, uint8_t value);

        const std::vector<uint8_t> buffer_;
        const uint32_t size_;

        // header fields
        const std::vector<uint8_t> entry_;
        const std::vector<uint8_t> logo_;
        const std::string title_;
        const uint16_t newLicenseeCode_;
        const uint8_t sgbFlag_;
        const uint8_t cartType_;
        const uint8_t romSize_;
        const uint8_t ramSize_;
        const uint8_t destinationCode_;
        const uint8_t oldLicenseeCode_;
        const uint8_t romVersion_;
        const uint8_t headerChecksum_;
        const uint16_t globalChecksum_;

        bool checksumPassed_ = false;
};
