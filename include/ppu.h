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
const uint8_t kLCDControlWindowTileMapAreaSelect = 0x01 << 6; // same as bg tile map area
const uint8_t kLCDControlWindowEnable = 0x01 << 5;
const uint8_t kLCDControlBGWinTileDataAreaSelect = 0x01 << 4; // if set, 0x8000, otherwise 0x8800
const uint8_t kLCDControlBGTileMapAreaSelect = 0x01 << 3; // if set, 0x9C00, otherwise 0x9800
const uint8_t kLCDControlObjSize = 0x01 << 2; // 16 or 8
const uint8_t kLCDControlObjEnable = 0x01 << 1;
const uint8_t kLCDControlBGWinEnable = 0x01 << 0;

const uint16_t kLCDControlWindowTileMapArea0 = 0x9800;
const uint16_t kLCDControlWindowTileMapArea1 = 0x9C00;
const uint16_t kLCDControlBGWinTileDataArea0 = 0x8800;
const uint16_t kLCDControlBGWinTileDataArea1 = 0x8000;
const uint16_t kLCDControlBGTileMapArea0 = 0x9800;
const uint16_t kLCDControlBGTileMapArea1 = 0x9C00;

const uint32_t kDefaultColors_[4] = {0xFFFFFFFF, 0xFFA9A9A9, 0xFF545454, 0xFF000000};


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
    enum PixelFetcherStep {TILE, DATALOW, DATAHIGH, SLEEP, PUSH};

    void Tick();
    void MoveToNextLine();
    void ScanOAM(const uint8_t index);
    void ResetPixelPipeline();
    void ProcessPixelPipeline();
    void FetchTile();
    void FetchTileDataLow();
    void FetchTileDataHigh();
    void FetchSleep();
    void PushToFIFO();
    void PushPixelToLCD();

    void DMAInit(const uint8_t start);
    void DMAProcess();

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
    uint16_t GetBackgroundTileMapArea();
    uint16_t GetTileDataArea();
    uint16_t GetWindowTileMapArea();
    void UpdatePaletteSelections(const uint8_t data, uint8_t* palette);
    bool WindowIsVisible();

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

    // pixel pipeline state/vars
    std::queue<uint32_t> backgroundFIFO_;
    std::queue<uint32_t> spriteFIFO_;
    PixelFetcherStep fetchStep_ = TILE;
    uint8_t fetcherX_ = 0; // track where the fetcher is in the current line
    uint8_t tileNumber_ = 0;
    uint8_t tileDataLow_ = 0;
    uint8_t tileDataHigh_ = 0;
    uint8_t backgroundPalette_[4]; // holds the palette selections as indices of the defaultColors;
    uint8_t lcdPushedX_ = 0;
    uint8_t lcdLineX_ = 0;
    uint8_t windowY_ = 0; //

    // DMA
    std::shared_ptr<Addressable> memory_ = nullptr;
    uint8_t dmaOffset_ = 0; // 0xFF46
    bool dmaActive_ = false;
    uint8_t dmaByte_;
    uint8_t dmaStartDelay_;
};
