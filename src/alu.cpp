#include "alu.hpp"
#include "cpu.hpp"

static void update_zn(Byte res, Flags& f) {
    f.z = (res == 0);
    f.n = ((res & 0x80) != 0);
}

Byte alu_add(Byte a, Byte b, Flags& f) {
    unsigned int sum = static_cast<unsigned int>(a) + b;
    Byte res = static_cast<Byte>(sum);
    update_zn(res, f);
    f.c = (sum > 0xFF);
    return res;
}

Byte alu_sub(Byte a, Byte b, Flags& f) {
    int diff = static_cast<int>(a) - b;
    Byte res = static_cast<Byte>(diff);
    update_zn(res, f);
    f.c = (a < b);
    return res;
}

Byte alu_and(Byte a, Byte b, Flags& f) {
    Byte res = a & b;
    update_zn(res, f);
    f.c = false;
    return res;
}

Byte alu_or(Byte a, Byte b, Flags& f) {
    Byte res = a | b;
    update_zn(res, f);
    f.c = false;
    return res;
}

Byte alu_xor(Byte a, Byte b, Flags& f) {
    Byte res = a ^ b;
    update_zn(res, f);
    f.c = false;
    return res;
}

Byte alu_not(Byte a, Flags& f) {
    Byte res = ~a;
    update_zn(res, f);
    f.c = false;
    return res;
}

Byte alu_shl(Byte a, Byte b, Flags& f) {
    unsigned int shift = b & 0x07;
    unsigned int val = static_cast<unsigned int>(a) << shift;
    Byte res = static_cast<Byte>(val);
    update_zn(res, f);
    f.c = ((val & 0x100) != 0);
    return res;
}

Byte alu_shr(Byte a, Byte b, Flags& f) {
    unsigned int shift = b & 0x07;
    Byte res = a >> shift;
    update_zn(res, f);
    f.c = (shift > 0) ? ((a >> (shift - 1)) & 1) : false;
    return res;
}

Byte alu_inc(Byte a, Flags& f) {
    return alu_add(a, 1, f);
}

Byte alu_dec(Byte a, Flags& f) {
    return alu_sub(a, 1, f);
}