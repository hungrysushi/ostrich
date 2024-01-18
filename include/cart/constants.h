#pragma once

#include <cstdint>

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

// rom types
const uint8_t kRomOnly = 0x00;
const uint8_t kMbc1 = 0x01;
const uint8_t kMbc1Ram = 0x02;
const uint8_t kMbc1RamBattery = 0x03;
const uint8_t kMbc2 = 0x05;
const uint8_t kMbc2Battery = 0x06;
const uint8_t kRomRam = 0x08;
const uint8_t kRomRamBattery = 0x09;
const uint8_t kMmm01 = 0x0B;
const uint8_t kMmm01Ram = 0x0C;
const uint8_t kMmm01RamBattery = 0x0D;
const uint8_t kMbc3TimerBattery = 0x0F;
const uint8_t kMbc3TimerRamBattery = 0x10;
const uint8_t kMbc3 = 0x11;
const uint8_t kMbc3Ram = 0x12;
const uint8_t kMbc3RamBattery = 0x13;
const uint8_t kMbc5 = 0x19;
const uint8_t kMbc5Ram = 0x1A;
const uint8_t kMbc5RamBattery = 0x1B;
const uint8_t kMbc5Rumble = 0x1C;
const uint8_t kMbc5RumbleRam = 0x1D;
const uint8_t kMbc5RumbleRamBattery = 0x1E;
const uint8_t kMbc6 = 0x20;
const uint8_t kMbc7SensorRumbleRamBattery = 0x22;
const uint8_t kPocketCamera = 0xFC;
const uint8_t kBandaiTama5 = 0xFD;
const uint8_t kHuC3 = 0xFE;
const uint8_t kHuC1RamBattery = 0xFF;

const uint16_t kCartRamSize = 0x1FFF;