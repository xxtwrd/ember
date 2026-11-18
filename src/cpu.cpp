#include "cpu.hpp"
#include "alu.hpp"
#include <iostream>
#include <iomanip>

void dump_regs(const CPU& cpu) {
    std::cout << "PC=" << std::hex << std::setw(4) << std::setfill('0') << cpu.pc << std::dec << std::setfill(' ')
        << "  H=" << std::hex << std::setw(4) << std::setfill('0') << cpu.h << std::dec << std::setfill(' ')
        << "  A=" << static_cast<int>(cpu.a)
        << "  B=" << static_cast<int>(cpu.b)
        << "  Z=" << (cpu.f.z ? 1 : 0)
        << "  N=" << (cpu.f.n ? 1 : 0)
        << "  C=" << (cpu.f.c ? 1 : 0)
        << (cpu.halted ? "  [HALTED]" : "")
        << std::endl;
}

void run(CPU& cpu) {
    while (!cpu.halted) {
        step(cpu);
    }
}
void step(CPU& cpu) {
    if (cpu.halted) {
        std::cout << "halted\n";
        return;
    }

    Byte op = 0;
    if (!mem_get(*cpu.mem, cpu.pc, op)) {
        std::cout << "Error: PC out of bounds at 0x" << std::hex << cpu.pc << std::dec << "\n";
        cpu.halted = true;
        return;
    }

    switch (op) {
    case OP_HALT:
        cpu.halted = true;
        cpu.pc += 1;
        break;
    case OP_NOP:
        cpu.pc += 1;
        break;
    case OP_OUT:
        std::cout << static_cast<char>(cpu.a);
        cpu.pc += 1;
        break;
    case OP_OUTN:
        std::cout << static_cast<int>(cpu.a);
        cpu.pc += 1;
        break;
    case OP_ADD:
        cpu.a = alu_add(cpu.a, cpu.b, cpu.f);
        cpu.pc += 1;
        break;
    case OP_SUB:
        cpu.a = alu_sub(cpu.a, cpu.b, cpu.f);
        cpu.pc += 1;
        break;
    case OP_AND:
        cpu.a = alu_and(cpu.a, cpu.b, cpu.f);
        cpu.pc += 1;
        break;
    case OP_OR:
        cpu.a = alu_or(cpu.a, cpu.b, cpu.f);
        cpu.pc += 1;
        break;
    case OP_XOR:
        cpu.a = alu_xor(cpu.a, cpu.b, cpu.f);
        cpu.pc += 1;
        break;
    case OP_NOT:
        cpu.a = alu_not(cpu.a, cpu.f);
        cpu.pc += 1;
        break;
    case OP_SHL:
        cpu.a = alu_shl(cpu.a, cpu.b, cpu.f);
        cpu.pc += 1;
        break;
    case OP_SHR:
        cpu.a = alu_shr(cpu.a, cpu.b, cpu.f);
        cpu.pc += 1;
        break;
    case OP_INC:
        cpu.a = alu_inc(cpu.a, cpu.f);
        cpu.pc += 1;
        break;
    case OP_DEC:
        cpu.a = alu_dec(cpu.a, cpu.f);
        cpu.pc += 1;
        break;
    case OP_LOADI: {
        Byte imm = 0;
        if (!mem_get(*cpu.mem, cpu.pc + 1, imm)) {
            std::cout << "Error: LOADI out of bounds\n";
            cpu.halted = true;
            return;
        }
        cpu.a = imm;
        cpu.pc += 2;
        break;
    }

    case OP_LOADH: {
        Byte lo = 0, hi = 0;
        mem_get(*cpu.mem, cpu.pc + 1, lo);
        mem_get(*cpu.mem, cpu.pc + 2, hi);
        cpu.h = static_cast<uint16_t>(lo | (hi << 8));
        cpu.pc += 3;
        break;
    }

    case OP_LOAD_H: {
        Byte val = 0;
        if (!mem_get(*cpu.mem, cpu.h, val)) {
            std::cout << "Error: LOAD [H] out of bounds at address 0x" << std::hex << cpu.h << std::dec << "\n";
            cpu.halted = true;
            return;
        }
        cpu.a = val;
        cpu.pc += 1;
        break;
    }

    case OP_INCH:
        cpu.h++;
        cpu.pc += 1;
        break;
    default:
        std::cout << "Unknown opcode: 0x" << std::hex << static_cast<int>(op) << std::dec << "\n";
        cpu.pc += 1;
        break;
    }
}