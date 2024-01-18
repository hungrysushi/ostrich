#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "cart/constants.h"
#include "interface/addressable.h"

class Cart : public Addressable {
 public:
  Cart(std::vector<uint8_t>& buffer);
  virtual ~Cart();

  virtual const std::string Describe();
  virtual const uint8_t Read(uint16_t addr);
  virtual void Write(uint16_t addr, uint8_t value);

  const std::vector<uint8_t> buffer_;
  const uint32_t size_;

  std::vector<uint8_t> ram_;
  uint8_t numberOfBanks_ = 0;

  // header fields
  const std::vector<uint8_t> entry_;
  const std::vector<uint8_t> logo_;
  const std::string title_;
  const uint16_t newLicenseeCode_;
  const uint8_t sgbFlag_;
  const uint8_t cartType_;
  const uint16_t romSize_;
  const uint16_t ramSize_;
  const uint8_t destinationCode_;
  const uint8_t oldLicenseeCode_;
  const uint8_t romVersion_;
  const uint8_t headerChecksum_;
  const uint16_t globalChecksum_;

  bool checksumPassed_ = false;
};
