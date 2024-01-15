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

            if (lcdPushedX_ >= kLCDWidth) { // xres pixels sent
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
                    windowY_ = 0;
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

    // check if window is in fetching range
    if (WindowIsVisible() && ly_ >= wy_ && ly_ < (wy_ + kLCDHeight)) {
        windowY_++;
    }
}

void PPU::ScanOAM(const uint8_t index) {
    // TODO
}

void PPU::ResetPixelPipeline() {
    backgroundFIFO_ = {};
    spriteFIFO_ = {};

    // background fetcher state
    fetcherX_ = 0;
    lcdPushedX_ = 0;
    lcdLineX_ = 0;
}

void PPU::ProcessPixelPipeline() {
    // state machine for processing background, window, and sprite pixels
    // processed every other dot, to simulate each of the first 4 stages taking two dots
    if (cycles_ % 2) {
        switch(fetchStep_) {
            case TILE: FetchTile(); break;
            case DATALOW: FetchTileDataLow(); break;
            case DATAHIGH: FetchTileDataHigh(); break;
            case SLEEP: FetchSleep(); break;
            case PUSH: PushToFIFO(); break; // in the actual process, push happens every dot
        }
    }

    PushPixelToLCD();
}

void PPU::FetchTile() {
    if (GetLCDControl(kLCDControlBGWinEnable)) {
        uint16_t addr = 0x00;

        if (WindowIsVisible() &&
                fetcherX_ + 7 >= wx_ && fetcherX_ + 7 < wx_ + kLCDHeight + 14 &&
                ly_ >= wy_ && ly_ < wy_ + kLCDWidth) {
            // render window tile over background

            uint8_t windowTileY = windowY_ / 8;
            addr = GetWindowTileMapArea() + (fetcherX_ - wx_ + 7) / 8 + windowTileY * 32;
        } else {
            uint8_t mapY = ly_ + scy_;
            uint8_t mapX = fetcherX_ + scx_;
            addr = GetBackgroundTileMapArea() + (mapX / 8) + (mapY / 8) * 32;
        }

        tileNumber_ = memory_->Read(addr);
        if (!GetLCDControl(kLCDControlBGWinTileDataAreaSelect)) { // offset address based on addressing mode for tile
            tileNumber_ += 128;
        }
    }

    fetchStep_ = DATALOW;
    fetcherX_ += 8;
}

void PPU::FetchTileDataLow() {
    uint8_t mapY = ly_ + scy_;
    uint8_t tileY = (mapY % 8) * 2;
    uint16_t addr = GetTileDataArea() + (tileNumber_ * 16) + tileY;

    tileDataLow_ = memory_->Read(addr);

    fetchStep_ = DATAHIGH;
}

void PPU::FetchTileDataHigh() {
    uint8_t mapY = ly_ + scy_;
    uint8_t tileY = (mapY % 8) * 2;
    uint16_t addr = GetTileDataArea() + (tileNumber_ * 16) + tileY + 1;

    tileDataHigh_ = memory_->Read(addr);

    fetchStep_ = SLEEP;
}

void PPU::FetchSleep() {
    fetchStep_ = PUSH;
}

void PPU::PushToFIFO() {
    if (backgroundFIFO_.size() > 8) {
        return;
    }

    for (int i = 7; i >= 0; i--) {
        bool setLow = tileDataLow_ & (0x01 << i);
        bool setHigh = tileDataHigh_ & (0x01 << i);
        uint8_t colorIndex = (setHigh << 1) | setLow;
        uint32_t color = kDefaultColors_[backgroundPalette_[0]];

        if (GetLCDControl(kLCDControlBGWinEnable)) {
            color = kDefaultColors_[backgroundPalette_[colorIndex]];
        }

        if (fetcherX_ - (8 - scx_ % 8) >= 0){
            backgroundFIFO_.push(color);
        }
    }

    fetchStep_ = TILE;
}

void PPU::PushPixelToLCD() {
    if (backgroundFIFO_.size() > 8) {
        uint32_t color = backgroundFIFO_.front();
        backgroundFIFO_.pop();

        if (lcdLineX_ >= (scx_ % 8)) {
            screenBuffer_[lcdPushedX_ + ly_ * kLCDWidth] = color;

            lcdPushedX_++;
        }

        lcdLineX_++;
    }
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
            return ly_;
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
        case 0xFF47:
            bgp_ = value;
            UpdatePaletteSelections(value, backgroundPalette_);
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

uint16_t PPU::GetBackgroundTileMapArea() {
    return GetLCDControl(kLCDControlBGTileMapAreaSelect) ? kLCDControlBGTileMapArea1 : kLCDControlBGTileMapArea0;
}

uint16_t PPU::GetTileDataArea() {
    return GetLCDControl(kLCDControlBGWinTileDataAreaSelect) ? kLCDControlBGWinTileDataArea1 : kLCDControlBGWinTileDataArea0;
}

uint16_t PPU::GetWindowTileMapArea() {
    return GetLCDControl(kLCDControlWindowTileMapAreaSelect) ? kLCDControlWindowTileMapArea1 : kLCDControlWindowTileMapArea0;
}

void PPU::UpdatePaletteSelections(const uint8_t data, uint8_t* palette) {
    // every two bits selects one of the indices from the default 4 colors
    for (int i = 0; i < 4; i++) {
        palette[i] = (data >> (2 * i)) & 0b11;
    }
}

bool PPU::WindowIsVisible() {
    return GetLCDControl(kLCDControlWindowEnable) && (wx_ - 7) < kLCDWidth && wy_ < kLCDHeight;
}
