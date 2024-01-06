#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

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
    Cart cart(buffer);
    std::cout << cart.Describe() << "\n";

    return 0;
}
