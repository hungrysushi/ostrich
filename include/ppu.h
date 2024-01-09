#pragma once

#include <cstdint>
#include <memory>
#include <queue>
#include <vector>

#include "interface/addressable.h"
#include "interface/interrupt_handler.h"


const uint32_t kLCDWidth = 160;
const uint32_t kLCDHeight = 144;

const uint32_t kCyclesPerOamScan = 80;
const uint32_t kCyclesPerLine = 456;
const uint32_t kLinesPerFrame = 154;

const uint8_t kLCDStatIntLyc = 0x01 << 6;
const uint8_t kLCDStatIntOam = 0x01 << 5; // Mode 2
const uint8_t kLCDStatIntHBlank = 0x01 << 4; // Mode 1
const uint8_t kLCDStatIntVBlank = 0x01 << 3; // Mode 0
const uint8_t kLCDStatLyc = 0x01 << 2;

const uint8_t kLCDControlEnable = 0x01 << 7;
const uint8_t kLCDControlWindowTileMapArea = 0x01 << 6; // same as bg tile map area
const uint8_t kLCDControlWindowEnable = 0x01 << 5;
const uint8_t kLCDControlBGWinTileDataArea = 0x01 << 4; // if set, 0x8000, otherwise 0x8800
const uint8_t kLCDControlBGTileMapArea = 0x01 << 3; // if set, 0x9C00, otherwise 0x9800
const uint8_t kLCDControlObjSize = 0x01 << 2; // 16 or 8
const uint8_t kLCDControlObjEnable = 0x01 << 1;
const uint8_t kLCDControlBGWinEnable = 0x01 << 0;


struct OAMData {
    uint8_t y = 0;
    uint8_t x = 0;
    uint8_t tileIndex = 0;
    uint8_t cgbPalette : 3;
    uint8_t bank : 1;
    uint8_t palette : 1;
    uint8_t xFlip : 1;
    uint8_t yFlip : 1;
    uint8_t priority : 1;
};


class PPU : public Addressable {
public:
    PPU();
    virtual ~PPU();

    enum Mode {HBLANK, VBLANK, OAM_SCAN, PIXEL_TRANSFER};

    void Tick();
    void MoveToNextLine();
    void ScanOAM(const uint8_t index);
    void ResetPixelPipeline();
    void ProcessPixelPipeline();

    const uint8_t Read(const uint16_t addr);
    void Write(const uint16_t addr, const uint8_t value);
    const uint8_t OAMRead(const uint16_t addr);
    void OAMWrite(const uint16_t addr, const uint8_t value);

    void SetMode(Mode mode);
    Mode GetMode();
    bool GetLCDStat(uint8_t type);
    void SetLCDStat(uint8_t type);
    void ClearLCDStat(uint8_t type);
    bool GetLCDControl(uint8_t type);
    void SetLCDControl(uint8_t type);
    void ClearLCDControl(uint8_t type);

    uint64_t cycles_ = 0;
    uint64_t frames_ = 0;

    std::vector<OAMData> oam_ = std::vector<OAMData>(40);
    std::vector<uint8_t> vram_ = std::vector<uint8_t>(0x2000);

    std::vector<uint32_t> screenBuffer_ = std::vector<uint32_t>(kLCDHeight * kLCDWidth);

    std::shared_ptr<InterruptHandler> interruptHandler_ = nullptr;

    // LCD
    uint8_t lcdc_ = 0x91; // 0xFF40
    uint8_t stat_; // 0xFF41
    uint8_t scy_ = 0; // 0xFF42
    uint8_t scx_ = 0; // 0xFF43
    uint8_t ly_ = 0; // 0xFF44
    uint8_t lyc_ = 0; // 0xFF45
    uint8_t bgp_ = 0xFC; // 0xFF47
    uint8_t obp0_ = 0xFF; // 0xFF48
    uint8_t obp1_ = 0xFF; // 0xFF49
    uint8_t wy_ = 0; // 0xFF4A
    uint8_t wx_ = 0; // 0xFF4B

    std::queue<uint32_t> backgroundFIFO_;
    std::queue<uint32_t> spriteFIFO_;
};
