//
// Created by Liuhaohua on 2019/10/2.
//

#include "utility.h"
#include <stdio.h>

void print_hex(byte *addr, const size_t n) {
    for (size_t i = 0; i < n; ++i) {
        printf("%02X", addr[i]);
    }
}

void print_bits(byte *addr, const size_t from, const size_t n, const size_t space) {
    int count = 0;
    for (size_t i = 0; i < n; ++i) {
        printf("%d", test_bit(addr, from + i));
        ++count;
        if (count % space == 0)
            putchar(' ');
    }
}

void set_bit(byte *addr, const size_t nr) {
    addr[nr / (sizeof(byte) * 8)] |= 1u << (7 - (nr % 8));
}

void clear_bit(byte *addr, const size_t nr) {
    addr[nr / (sizeof(byte) * 8)] &= ~(1u << (7 - (nr % 8)));
}

void copy_bit(const byte *src, byte *dst, const size_t src_nr, const size_t dst_nr) {
    if (test_bit(src, src_nr))
        set_bit(dst, dst_nr);
    else
        clear_bit(dst, dst_nr);
}

void copy_bits(const byte *src, byte *dst, const size_t src_nr, const size_t dst_nr, const size_t n) {
    for (size_t i = 0; i < n; ++i) {
        copy_bit(src, dst, src_nr + i, dst_nr + i);
    }
}

void xor_bits(const byte *lhs, const byte *rhs, byte *dst, const size_t n) {
    for (size_t i = 0; i < n; ++i) {
        if (test_bit(lhs, i) ^ test_bit(rhs, i))
            set_bit(dst, i);
        else
            clear_bit(dst, i);
    }
}

void permute_bits(const byte *src, byte *dst, const size_t src_nr, const size_t dst_nr, const int permutation[],
                  const size_t n) {
    for (size_t i = 0; i < n; ++i) {
        copy_bit(src, dst, src_nr + permutation[i] - 1, dst_nr + i);
    }
}

void shift_left(const byte *src, byte *dst, const size_t src_nr_offset, const size_t dst_nr_offset, const size_t shift,
                const size_t n_bits) {
    copy_bits(src, dst, src_nr_offset, n_bits - shift + dst_nr_offset, shift);
    copy_bits(src, dst, src_nr_offset + shift, dst_nr_offset, n_bits - shift);
}

_Bool test_bit(const byte *addr, const size_t nr) {
    return addr[nr / (sizeof(byte) * 8)] & (1u << (7 - (nr % 8)));
}
