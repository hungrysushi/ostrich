#include "ppu.h"

#include "spdlog/spdlog.h"


PPU::PPU() { }

PPU::~PPU() { }

void PPU::Tick() {
    cycles_++;  // cycles in this current line

    // process DMA every m-cycle
    if (dmaActive_ && cycles_ % 4 == 0) {
        DMAProcess();
    }

    switch(GetMode()) {
        case OAM_SCAN:
            if (cycles_ >= kCyclesPerOamScan) {
                SetMode(PIXEL_TRANSFER);

                ResetPixelPipeline();
            }

            // scan OAM for sprites, using the first 40 cycles as the index to check
            if (cycles_ < 40) {
                ScanOAM(cycles_);
            }

            break;
        case PIXEL_TRANSFER: // process and push pixels
            ProcessPixelPipeline();

            if (cycles_ >= 80 + 172) { // xres pixels sent
                SetMode(HBLANK);

                if (GetLCDStat(kLCDStatIntHBlank)) {
                    interruptHandler_->Request(kInterruptLCD);
                }
            }
            break;
        case HBLANK:
            if (cycles_ >= kCyclesPerLine) {
                MoveToNextLine();

                if (ly_ >= kLCDHeight) { // line is now outside the visible screen
                    SetMode(VBLANK);

                    interruptHandler_->Request(kInterruptVBlank);

                    if (GetLCDStat(kLCDStatIntVBlank)) {
                        interruptHandler_->Request(kInterruptLCD);
                    }
                } else {
                    SetMode(OAM_SCAN);
                }

                cycles_ = 0;
            }
            break;
        case VBLANK:
            if (cycles_ >= kCyclesPerLine) {
                MoveToNextLine();

                if (ly_ >= kLinesPerFrame) {
                    SetMode(OAM_SCAN);
                    ly_ = 0;
                }

                cycles_ = 0;
            }
            break;
    }
}

void PPU::MoveToNextLine() {
    ly_++;
    if (ly_ == lyc_) {
        SetLCDStat(kLCDStatLyc);

        if (GetLCDStat(kLCDStatIntLyc)) {
            interruptHandler_->Request(kInterruptLCD);
        }
    } else {
        ClearLCDStat(kLCDStatLyc);
    }
}

void PPU::ScanOAM(const uint8_t index) {
    // TODO
}

void PPU::ResetPixelPipeline() {
    backgroundFIFO_ = {};
    spriteFIFO_ = {};
}

void PPU::ProcessPixelPipeline() {
    // TODO
}

void PPU::DMAInit(const uint8_t start) {
    dmaActive_ = true;
    dmaByte_ = 0;
    dmaStartDelay_ = 2;
    dmaOffset_ = start;
}

void PPU::DMAProcess() {
    // dma doesn't start immediately
    if (dmaStartDelay_ > 0) {
        dmaStartDelay_--;
        return;
    }

    OAMWrite(dmaByte_, memory_->Read((dmaOffset_ * 0x100) + dmaByte_));
    dmaByte_++;

    if (dmaByte_ >= 0xA0) { // 160 bytes transferred
        dmaActive_ = false;
    }
}

const uint8_t PPU::Read(const uint16_t addr) {
    if (addr >= 0x8000 && addr < 0xA000) {
        return vram_[addr - 0x8000];
    }

    if (addr >= 0xFE00 && addr <= 0xFE9F) {
        if (dmaActive_) {
            return 0xFF;
        }

        return OAMRead(addr - 0xFE00);
    }

    switch(addr) {
        case 0xFF40:
            return lcdc_;
        case 0xFF41:
            return stat_;
        case 0xFF42:
            return scy_;
        case 0xFF43:
            return scx_;
        case 0xFF44:
            /* return ly_; */
            return 0x94;
        case 0xFF45:
            return lyc_;
        case 0xFF46:
            return dmaOffset_;
        case 0xFF47:
            return bgp_;
        case 0xFF48:
            return obp0_;
        case 0xFF49:
            return obp1_;
        case 0xFF4A:
            return wy_;
        case 0xFF4B:
            return wx_;
    }

    spdlog::warn("Unimplemented PPU memory read: {:4X}", addr);
    return 0;
}

void PPU::Write(const uint16_t addr, const uint8_t value) {
    if (addr >= 0x8000 && addr < 0xA000) {
        vram_[addr - 0x8000] = value;
        return;
    }

    if (addr >= 0xFE00 && addr < 0xFE9F) {
        if (dmaActive_) {
            return;
        }

        return OAMWrite(addr - 0xFE00, value);
    }

    switch(addr) {
        case 0xFF40:
            lcdc_ = value;
            return;
        case 0xFF41:
            stat_ = value;
            return;
        case 0xFF42:
            scy_ = value;
            return;
        case 0xFF43:
            scx_ = value;
            return;
        case 0xFF44:
            ly_ = value;
            return;
        case 0xFF45:
            lyc_ = value;
            return;
        case 0xFF46:
            DMAInit(value);
            return;
        case 0xFF4A:
            wy_ = value;
            return;
        case 0xFF4B:
            wx_ = value;
            return;
        default:
            spdlog::warn("Unimplemented PPU memory write: {:4X}", addr);
    }
}

// operate on OAM bytes using an already offset address (ie addr - 0xFE00)
const uint8_t PPU::OAMRead(const uint16_t addr) {
    OAMData* obj = oam_.data();
    uint8_t* objBytes = reinterpret_cast<uint8_t*>(obj);

    return objBytes[addr];
}

void PPU::OAMWrite(const uint16_t addr, const uint8_t value) {
    OAMData* obj = oam_.data();
    uint8_t* objBytes = reinterpret_cast<uint8_t*>(obj);

    objBytes[addr] = value;
}

PPU::Mode PPU::GetMode() {
    return (Mode) (stat_ & 0b11);
}

void PPU::SetMode(Mode mode) {
    stat_ &= ~0b11;
    stat_ |= mode;
}

bool PPU::GetLCDStat(uint8_t type) {
    return stat_ & type;
}

void PPU::SetLCDStat(uint8_t type) {
    stat_ |= type;
}

void PPU::ClearLCDStat(uint8_t type) {
    stat_ &= ~type;
}

bool PPU::GetLCDControl(uint8_t type) {
    return lcdc_ & type;
}

void PPU::SetLCDControl(uint8_t type) {
    lcdc_ |= type;
}

void PPU::ClearLCDControl(uint8_t type) {
    lcdc_ &= ~type;
}
