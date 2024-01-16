#pragma once

#include <cstdint>

class Addressable {
 public:
  Addressable(){};
  virtual ~Addressable(){};

  virtual const uint8_t Read(const uint16_t i) = 0;
  virtual void Write(const uint16_t i, const uint8_t byte) = 0;
};
