#include <atomic>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

#include "SDL2/SDL.h"
#include "spdlog/spdlog.h"

#include "address_bus.h"
#include "cart.h"
#include "cpu.h"
#include "io.h"
#include "ppu.h"
#include "timer.h"


std::string message = "";

SDL_Window* sdlWindow;
SDL_Renderer* sdlRenderer;
SDL_Texture* sdlTexture;
SDL_Surface* sdlScreen;

int scale = 2; // TODO make configurable

std::atomic<bool> quit{false};


void initWindow() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failed to init SDL2\n";
        exit(-1);
    }

    SDL_CreateWindowAndRenderer(kLCDWidth * scale, kLCDHeight * scale, 0, &sdlWindow, &sdlRenderer);
    sdlScreen = SDL_CreateRGBSurface(0,
                                     kLCDWidth * scale,
                                     kLCDHeight * scale,
                                     32,
                                     0,
                                     0,
                                     0,
                                     0);
    sdlTexture = SDL_CreateTexture(sdlRenderer,
                                   SDL_PIXELFORMAT_ARGB8888,
                                   SDL_TEXTUREACCESS_STREAMING,
                                   kLCDWidth * scale,
                                   kLCDHeight * scale);
}


void updateWindow(std::shared_ptr<PPU> ppu) {
    SDL_Rect rect;
    rect.x = rect.y = 0;
    rect.w = sdlScreen->w;
    rect.h = sdlScreen->h;

    // mimic how the ppu updates - left-to-right line-by-line
    for (int y = 0; y < kLCDHeight; y++) {
        for (int x = 0; x < kLCDWidth; x++) {
            rect.x = x * scale;
            rect.y = y * scale;
            rect.w = scale;
            rect.h = scale;

            SDL_FillRect(sdlScreen, &rect, ppu->screenBuffer_[x + (y * 160)]);
        }
    }

    SDL_UpdateTexture(sdlTexture, nullptr, sdlScreen->pixels, sdlScreen->pitch);
	SDL_RenderClear(sdlRenderer);
	SDL_RenderCopy(sdlRenderer, sdlTexture, nullptr, nullptr);
	SDL_RenderPresent(sdlRenderer);
}


void handleWindowEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e) > 0) {
        switch (e.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_WINDOWEVENT:
                if (e.window.event == SDL_WINDOWEVENT_CLOSE) {
                    quit = true;
                }
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                /* handleKeyPress(e); */
            default: break;
        }
    }
}


std::vector<uint8_t> loadRom(const std::string& filename)
{
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
    buffer.insert(buffer.begin(),
            std::istream_iterator<uint8_t>(fs),
            std::istream_iterator<uint8_t>());

    return buffer;
}


void updateSerialDebugMessage(std::shared_ptr<IO> io) {
    if (io->serialControl_ == 0x81) {
        message += io->serialData_;

        io->serialControl_ = 0x00;
    }
}


int main(int argc, char** argv)
{
    spdlog::set_level(spdlog::level::trace);
    spdlog::set_pattern("%v");

    if (argc < 2) {
        std::cout << "Enter a filename\n";
        return -1;
    }
    std::string filename(argv[1]);
    std::vector<uint8_t> buffer = loadRom(filename);
    std::shared_ptr<Cart> cart = std::make_shared<Cart>(buffer);
    std::cout << cart->Describe() << "\n";

    std::shared_ptr<AddressBus> addressBus = std::make_shared<AddressBus>();
    std::shared_ptr<CPU> cpu = std::make_shared<CPU>();
    std::shared_ptr<Timer> timer = std::make_shared<Timer>();
    std::shared_ptr<IO> io = std::make_shared<IO>();
    std::shared_ptr<PPU> ppu = std::make_shared<PPU>();

    // connect up components
    cpu->memory_ = addressBus;
    addressBus->cart_ = cart;
    addressBus->io_ = io;
    addressBus->ppu_ = ppu;
    io->timer_ = timer;
    io->cpu_ = cpu;
    io->ppu_ = ppu;
    timer->interruptHandler_ = cpu;
    ppu->memory_ = addressBus;
    ppu->interruptHandler_ = cpu;

    initWindow();

    uint32_t lastCycles_ = 0;
    while (!quit) {
        if (cpu->Step() < 0) {
            std::cout << "Error in CPU step\n";
            break;
        }

        int elapsed = cpu->cycles_ - lastCycles_;
        // timer ticks 4 times every m cycle
        for (int i = 0; i < 4 * elapsed; i++) {
            timer->Tick();
            ppu->Tick();
        }
        lastCycles_ = cpu->cycles_;

        updateSerialDebugMessage(io);
        if (message.length() > 0) {
            std::cout << "DEBUG: " << message << "\n";
        }

        updateWindow(ppu);
        handleWindowEvents();
    }

    return 0;
}
