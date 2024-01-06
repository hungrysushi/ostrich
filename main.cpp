#include <iostream>


int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cout << "Enter a filename\n";
        return -1;
    }
    std::string filename(argv[1]);

    return 0;
}
