#pragma once

#include <cstdint>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#include "cart/constants.h"

static std::string RomTypeToString(const uint8_t romType) {
  switch (romType) {
    case kRomOnly:
      return "ROM ONLY";
    case kMbc1:
      return "MBC1";
    case kMbc1Ram:
      return "MBC1+RAM";
    case kMbc1RamBattery:
      return "MBC1+RAM+BATTERY";
    case kMbc2:
      return "MBC2";
    case kMbc2Battery:
      return "MBC2+BATTERY";
    case kRomRam:
      return "ROM+RAM 1";
    case kRomRamBattery:
      return "ROM+RAM+BATTERY 1";
    case kMmm01:
      return "MMM01";
    case kMmm01Ram:
      return "MMM01+RAM";
    case kMmm01RamBattery:
      return "MMM01+RAM+BATTERY";
    case kMbc3TimerBattery:
      return "MBC3+TIMER+BATTERY";
    case kMbc3TimerRamBattery:
      return "MBC3+TIMER+RAM+BATTERY 2";
    case kMbc3:
      return "MBC3";
    case kMbc3Ram:
      return "MBC3+RAM 2";
    case kMbc3RamBattery:
      return "MBC3+RAM+BATTERY 2";
    case kMbc5:
      return "MBC5";
    case kMbc5Ram:
      return "MBC5+RAM";
    case kMbc5RamBattery:
      return "MBC5+RAM+BATTERY";
    case kMbc5Rumble:
      return "MBC5+RUMBLE";
    case kMbc5RumbleRam:
      return "MBC5+RUMBLE+RAM";
    case kMbc5RumbleRamBattery:
      return "MBC5+RUMBLE+RAM+BATTERY";
    case kMbc6:
      return "MBC6";
    case kMbc7SensorRumbleRamBattery:
      return "MBC7+SENSOR+RUMBLE+RAM+BATTERY";
    case kPocketCamera:
      return "POCKET CAMERA";
    case kBandaiTama5:
      return "BANDAI TAMA5";
    case kHuC3:
      return "HuC3";
    case kHuC1RamBattery:
      return "HuC1+RAM+BATTERY";
    default:
      return "Unknown ROM type";
  }
}

static std::vector<uint8_t> LoadRom(const std::string& filename) {
  std::ifstream fs;
  fs.unsetf(std::ios::skipws);
  fs.exceptions(std::ios::badbit);

  fs.open(filename, std::ios::binary);

  // file length
  fs.seekg(0, std::ios::end);
  std::streampos length = fs.tellg();
  fs.seekg(0, std::ios::beg);

  // read whole file into a buffer
  std::vector<uint8_t> buffer;
  buffer.reserve(length);
  buffer.insert(buffer.begin(), std::istream_iterator<uint8_t>(fs),
                std::istream_iterator<uint8_t>());

  return buffer;
}
