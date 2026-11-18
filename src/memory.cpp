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
bool set16(Memory& mem, size_t addr, uint16_t value) {
    if (!mem_set(mem, addr, static_cast<Byte>(value & 0xFF))) {
        return false;
    }
    if (!mem_set(mem, addr + 1, static_cast<Byte>((value >> 8) & 0xFF))) {
        return false;
    }
    return true;
}

bool get16(const Memory& mem, size_t addr, uint16_t& out_val) {
    Byte lo, hi;
    if (!mem_get(mem, addr, lo) || !mem_get(mem, addr + 1, hi)) {
        return false;
    }
    out_val = static_cast<uint16_t>(lo | (hi << 8));
    return true;
}