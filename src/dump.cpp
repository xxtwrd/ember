#include "dump.hpp"
#include <iostream>
#include <iomanip>

void show_byte(Byte val) {
    std::cout << std::setw(3) << static_cast<int>(val) << "  ";
    std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(val) << std::dec << std::setfill(' ') << "  ";
    std::cout << "0b";
    for (int i = 7; i >= 0; --i) {
        std::cout << ((val >> i) & 1);
    }
    std::cout << "  ";
    char c = static_cast<char>(val);
    if (val >= 32 && val <= 126) {
        std::cout << '\'' << c << '\'';
    } else {
        std::cout << '\'.\'';
    }
}

void mem_dump(const Memory& mem) {
    for (size_t i = 0; i < MEM_SIZE; i += 16) {
        std::cout << std::hex << std::setw(4) << std::setfill('0') << i << std::dec << std::setfill(' ') << ": ";
        for (size_t j = 0; j < 16; ++j) {
            if (i + j < MEM_SIZE) {
                std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(mem.data[i + j]) << std::dec << std::setfill(' ') << " ";
            } else {
                std::cout << "   ";
            }
        }
        std::cout << " |";
        for (size_t j = 0; j < 16; ++j) {
            if (i + j < MEM_SIZE) {
                Byte b = mem.data[i + j];
                if (b >= 32 && b <= 126) {
                    std::cout << static_cast<char>(b);
                } else {
                    std::cout << '.';
                }
            }
        }
        std::cout << "|" << std::endl;
    }
}