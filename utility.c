//
// Created by Liuhaohua on 2019/10/2.
//

#include "utility.h"

void set_bit(byte* addr, size_t nr) {
    addr[nr / (sizeof(byte) * 8)] |= 1u << (nr % 8);
}

void clear_bit(byte* addr, size_t nr) {
    addr[nr / (sizeof(byte) * 8)] &= ~(1u << (nr % 8));
}

_Bool test_bit(const byte* addr, size_t nr) {
    return addr[nr / (sizeof(byte) * 8)] & (1u << (nr % 8));
}
