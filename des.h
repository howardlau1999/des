//
// Created by Liuhaohua on 2019/10/2.
//

#ifndef DES_DES_H
#define DES_DES_H

#include "types.h"
#include "constants.h"

void shift_left(const byte *src, byte *dst, const size_t src_nr_offset, const size_t dst_nr_offset, const size_t shift,
                const size_t n_bits);

void create_subkeys(byte key[KEY_BYTE_LEN]);

void process_block(byte block[BLOCK_BYTE_LEN], byte output[BLOCK_BYTE_LEN], enum MODE mode);
void encrypt_block(byte block[BLOCK_BYTE_LEN], byte output[BLOCK_BYTE_LEN]);
void decrypt_block(byte block[BLOCK_BYTE_LEN], byte output[BLOCK_BYTE_LEN]);

#define DEBUG

#endif //DES_DES_H
