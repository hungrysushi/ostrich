#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

#include "address_bus.h"
#include "cart.h"


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


int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cout << "Enter a filename\n";
        return -1;
    }
    std::string filename(argv[1]);
    std::vector<uint8_t> buffer = loadRom(filename);
    std::shared_ptr<Cart> cart = std::make_shared<Cart>(buffer);
    std::cout << cart->Describe() << "\n";

    std::shared_ptr<AddressBus> addressBus = std::make_shared<AddressBus>();

    addressBus->cart_ = cart;

    return 0;
}
