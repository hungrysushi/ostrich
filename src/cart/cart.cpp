#include "cart/cart.h"

#include <sstream>

#include "cart/constants.h"

Cart::Cart(std::vector<uint8_t>& cartridge)
    : buffer_(std::move(cartridge)),
      size_(buffer_.size()),
      entry_(buffer_.begin() + kEntryStart,
             buffer_.begin() + kEntryStart + kEntrySize),
      logo_(buffer_.begin() + kLogoStart,
            buffer_.begin() + kLogoStart + kLogoSize),
      title_(buffer_.begin() + kTitleStart,
             buffer_.begin() + kTitleStart + kTitleSize),
      newLicenseeCode_((buffer_[kNewLicenseeStart] << 8) |
                       (buffer_[kNewLicenseeStart + 1])),
      sgbFlag_(buffer_[kSbgFlag]),
      cartType_(buffer_[kCartType]),
      romSize_(32 * (1 << buffer_[kRomSize])),
      ramSize_(buffer_[kRamSize]),
      destinationCode_(buffer_[kDestinationCode]),
      oldLicenseeCode_(buffer_[kOldLicenseeCode]),
      romVersion_(buffer_[kRomVersion]),
      headerChecksum_(buffer_[kHeaderChecksum]),
      globalChecksum_((buffer_[kGlobalChecksum] << 8) |
                      (buffer_[kGlobalChecksum + 1])) {
  // compute checksum
  unsigned sum = 0;
  for (unsigned i = kTitleStart; i < kHeaderChecksum; i++) {
    sum -= buffer_[i] - 1;
  }

  if (sum & 0xFF) {
    checksumPassed_ = true;
  }

  switch (ramSize_) {
    case 0x02:
      numberOfBanks_ = 1;
      break;
    case 0x03:
      numberOfBanks_ = 4;
      break;
    case 0x04:
      numberOfBanks_ = 16;
      break;
    case 0x05:
      numberOfBanks_ = 8;
      break;
  }

  ram_.resize(numberOfBanks_ * kCartRamSize, 0);
}

Cart::~Cart() {}

const std::string Cart::Describe() {
  std::stringstream ss;

  ss << "ROM Details:"
     << "\n";
  ss << "\tTitle: " << title_ << "\n";
  ss << "\tType: " << std::hex << (unsigned)cartType_ << "\n";
  ss << "\tROM Size: " << std::dec << (unsigned)romSize_ << "\n";
  ss << "\tFile Size: " << std::dec << (unsigned)size_ << "\n";
  ss << "\tRAM Size: " << std::dec << (unsigned)ramSize_ << "\n";

  return ss.str();
}

const uint8_t Cart::Read(uint16_t addr) {
  return buffer_[addr];

  // TODO banks/switching
}

void Cart::Write(uint16_t addr, uint8_t value) {
  // invalid write to ROM
  /* buffer_[i] = byte; */
}

std::vector<uint8_t> Cart::Save() { return ram_; }

void Cart::Load(const std::vector<uint8_t> saveData) {
  ram_ = std::vector<uint8_t>(saveData);
}