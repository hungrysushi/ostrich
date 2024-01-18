#pragma once

#include <memory>
#include <string>
#include <vector>

#include "cart/cart.h"
#include "cart/constants.h"
#include "cart/mbc1.h"
#include "cart/util.h"
#include "spdlog/spdlog.h"

static std::shared_ptr<Cart> CreateCartridge(std::string& filename) {
  std::vector<uint8_t> romBuffer = LoadRom(filename);
  uint8_t romType = romBuffer[kCartType];

  switch (romType) {
    case kRomOnly:
      return std::make_shared<Cart>(romBuffer);
      break;
    case kMbc1:
    case kMbc1Ram:
    case kMbc1RamBattery:
      return std::make_shared<MBC1Cart>(romBuffer);
      break;
    default:
      spdlog::warn("Unsupported ROM type: 0x{:X} {}", romType,
                   RomTypeToString(romType));
  }
}