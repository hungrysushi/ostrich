#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

#include "spdlog/spdlog.h"

#include "address_bus.h"
#include "cart.h"
#include "cpu.h"
#include "io.h"
#include "ppu.h"
#include "timer.h"


std::string message = "";


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
    addressBus->cart_ = cart;
    addressBus->io_ = io;
    addressBus->ppu_ = ppu;
    cpu->memory_ = addressBus;
    io->timer_ = timer;
    io->cpu_ = cpu;
    io->ppu_ = ppu;
    timer->interruptHandler_ = cpu;

    uint32_t lastCycles_ = 0;
    while (true) {
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
    }

    return 0;
}
