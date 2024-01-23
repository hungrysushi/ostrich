#include <emscripten.h>
#include <emscripten/bind.h>

#include <atomic>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include "SDL2/SDL.h"
#include "address_bus.h"
#include "cart.h"
#include "cpu.h"
#include "io.h"
#include "ppu.h"
#include "spdlog/spdlog.h"
#include "timer.h"

SDL_Window* sdlWindow;
SDL_Renderer* sdlRenderer;
SDL_Texture* sdlTexture;
SDL_Surface* sdlScreen;

const int scale = 4;  // TODO make configurable
const float targetMsPerFrame = (100.0) / 6.0;

static std::atomic<bool> quit{false};
static std::atomic<bool> run{false};

static std::shared_ptr<Cart> cart = nullptr;
static std::shared_ptr<AddressBus> addressBus = nullptr;
static std::shared_ptr<CPU> cpu = nullptr;
static std::shared_ptr<Timer> timer = nullptr;
static std::shared_ptr<IO> io = nullptr;
static std::shared_ptr<PPU> ppu = nullptr;

static std::thread* cycleThread = nullptr;
static std::atomic<bool> threadRunning{false};

static std::vector<uint8_t> romBuffer;
static std::vector<uint8_t> saveBuffer;

static uint32_t lastCycles = 0;
static uint32_t lastFrameTime = 0;
static uint32_t lastMeasureTime = 0;
static uint32_t lastFrameCount = 0;
static uint32_t frames = 0;

void initWindow() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "Failed to init SDL2\n";
    exit(-1);
  }

  SDL_CreateWindowAndRenderer(kLCDWidth * scale, kLCDHeight * scale, 0,
                              &sdlWindow, &sdlRenderer);
  sdlScreen =
      SDL_CreateRGBSurface(0, kLCDWidth * scale, kLCDHeight * scale, 32,
                           0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
  sdlTexture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_ARGB8888,
                                 SDL_TEXTUREACCESS_STREAMING, kLCDWidth * scale,
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

void handleKeyPress(SDL_Event e, std::shared_ptr<IO> io) {
  SDL_KeyboardEvent keyEvent = e.key;

  bool pressed = !(keyEvent.type == SDL_KEYUP);

  switch (keyEvent.keysym.sym) {
    case SDLK_z:
      io->a_ = pressed;
      break;
    case SDLK_x:
      io->b_ = pressed;
      break;
    case SDLK_a:
      io->start_ = pressed;
      break;
    case SDLK_s:
      io->select_ = pressed;
      break;
    case SDLK_LEFT:
      io->left_ = pressed;
      break;
    case SDLK_RIGHT:
      io->right_ = pressed;
      break;
    case SDLK_UP:
      io->up_ = pressed;
      break;
    case SDLK_DOWN:
      io->down_ = pressed;
      break;
    default:
      spdlog::warn("Unmapped key pressed: {}", keyEvent.keysym.sym);
  }
}

void handleWindowEvents(std::shared_ptr<IO> io) {
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
        handleKeyPress(e, io);
      default:
        break;
    }
  }
}

void runGameboy() {
  threadRunning = true;
  std::cout << "Starting Gameboy thread\n";
  while (!quit) {
    if (cpu->Step() < 0) {
      std::cout << "Error in CPU step\n";
      break;
    }

    int elapsed = cpu->cycles_ - lastCycles;
    // timer ticks 4 times every m cycle
    for (int i = 0; i < 4 * elapsed; i++) {
      timer->Tick();
      ppu->Tick();
    }

    lastCycles = cpu->cycles_;

    if (ppu->frames_ != lastFrameCount) {
      uint32_t currentMs = SDL_GetTicks();
      uint32_t frameMs = currentMs - lastFrameTime;
      if (frameMs < targetMsPerFrame) {
        std::this_thread::sleep_for(
            std::chrono::milliseconds((int)targetMsPerFrame - frameMs));
      }
      if (currentMs - lastMeasureTime >= 1000) {
        if (currentMs - lastMeasureTime < 1000) {
          std::this_thread::sleep_for(
              std::chrono::milliseconds((int)currentMs - lastMeasureTime));
        }
        spdlog::info("{} frames per second", frames);
        lastMeasureTime = currentMs;
        frames = 0;
      }
      frames++;
      lastFrameTime = currentMs;
      lastFrameCount = ppu->frames_;
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
  }
  std::cout << "Exiting Gameboy thread\n";
  threadRunning = false;
}

void initGameboy() {
  run = false;
  quit = true;
  if (threadRunning) {
    std::cout << "Gameboy thread still running, waiting for exit\n";
    SDL_Delay(100);
  }

  // reset counters for frame timing
  lastCycles = 0;
  lastFrameTime = 0;
  lastMeasureTime = 0;
  lastFrameCount = 0;
  frames = 0;

  cart = CreateCartridge(romBuffer);
  std::cout << cart->Describe() << "\n";

  if (saveBuffer.size() > 0) {
    cart->Load(saveBuffer);
  }

  addressBus = std::make_shared<AddressBus>();
  cpu = std::make_shared<CPU>();
  timer = std::make_shared<Timer>();
  io = std::make_shared<IO>();
  ppu = std::make_shared<PPU>();

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

  quit = false;
  cycleThread = new std::thread(runGameboy);
  cycleThread->detach();

  run = true;
}

void mainLoop() {
  if (run) {
    if (ppu != nullptr) {
      updateWindow(ppu);
    }

    if (io != nullptr) {
      handleWindowEvents(io);
    }
  }
}

int main() {
  spdlog::set_level(spdlog::level::info);
  spdlog::set_pattern("%v");

  initWindow();

  emscripten_set_main_loop(mainLoop, 0, 1);

  return 0;
}

void test() { std::cout << "test prints of bel air\n"; }

void clearRomBuffer() { romBuffer = {}; }

void pushByteToRomBuffer(uint8_t data) { romBuffer.push_back(data); }

void clearSaveBuffer() { saveBuffer = {}; }

void pushByteToSaveBuffer(uint8_t data) { saveBuffer.push_back(data); }

emscripten::val readSaveData() {
  std::vector<uint8_t> saveData = cart->Save();
  return emscripten::val(
      emscripten::typed_memory_view(saveData.size(), saveData.data()));
}

EMSCRIPTEN_BINDINGS(my_module) {
  emscripten::register_vector<uint8_t>("ByteVector");
  emscripten::function("initGameboy", &initGameboy);
  emscripten::function("test", &test);
  emscripten::function("pushByteToRomBuffer", &pushByteToRomBuffer);
  emscripten::function("clearRomBuffer", &clearRomBuffer);
  emscripten::function("pushByteToSaveBuffer", &pushByteToSaveBuffer);
  emscripten::function("clearSaveBuffer", &clearSaveBuffer);
  emscripten::function("readSaveData", &readSaveData,
                       emscripten::allow_raw_pointers());
}
