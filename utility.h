//
// Created by Liuhaohua on 2019/10/2.
//

#ifndef DES_UTILITY_H
#define DES_UTILITY_H

#include "types.h"

void print_hex(byte *addr, size_t n);

void print_bits(byte *addr, size_t from, size_t n, size_t space);

void set_bit(byte *addr, size_t nr);

void clear_bit(byte *addr, size_t nr);

void copy_bit(const byte *src, byte *dst, size_t src_nr, size_t dst_nr);

void copy_bits(const byte *src, byte *dst, size_t src_nr, size_t dst_nr, size_t n);

void permute_bits(const byte *src, byte *dst, size_t src_nr, size_t dst_nr, const int permutation[], size_t n);

void xor_bits(const byte *lhs, const byte *rhs, byte *dst, size_t n);

_Bool test_bit(const byte *addr, size_t nr);

void shift_left(const byte *src, byte *dst, const size_t src_nr_offset, const size_t dst_nr_offset, const size_t shift,
                const size_t n_bits);

#endif //DES_UTILITY_H
