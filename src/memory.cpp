#include "memory.hpp"
bool mem_get(const Memory& mem, size_t addr, Byte& out_val) {
if (addr >= MEM_SIZE) {
return false;
}
out_val = mem.data[addr];
return true;
}
bool mem_set(Memory& mem, size_t addr, Byte val) {
if (addr >= MEM_SIZE) {
return false;
}
mem.data[addr] = val;
return true;
}

