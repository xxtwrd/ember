#ifndef MEMORY_HPP
#define MEMORY_HPP
#include <cstdint>
#include <cstddef>
using Byte = uint8_t;
constexpr size_t MEM_SIZE = 256;
struct Memory {
Byte data[MEM_SIZE]{};
};
bool mem_get(const Memory& mem, size_t addr, Byte& out_val);
bool mem_set(Memory& mem, size_t addr, Byte val);
#endif

