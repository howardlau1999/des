//
// Created by Liuhaohua on 2019/10/2.
//

#include "utility.h"
#include "constants.h"

byte subkeys[17][6] = {0};

void shift_left(const byte *src, byte *dst, const size_t src_nr_offset, const size_t dst_nr_offset, const size_t shift,
                const size_t n_bits) {
    copy_bits(src, dst, src_nr_offset, n_bits - shift + dst_nr_offset, shift);
    copy_bits(src, dst, src_nr_offset + shift, dst_nr_offset, n_bits - shift);
}

// Create 16 subkeys, each of which is 48-bits long
void create_subkeys(byte key[KEY_BYTE_LEN]) {
    byte CD[17][KEY_BYTE_LEN - 1] = {0};
    permute_bits(key, CD[0], 0, 0, PC_1, sizeof(PC_1) / sizeof(int));

    const int half_permuted_len = (KEY_BYTE_LEN - 1) * 4;
    for (size_t n = 1; n <= 16; ++n) {
        shift_left(CD[n - 1], CD[n], 0, 0, shifts[n], half_permuted_len);
        shift_left(CD[n - 1], CD[n], half_permuted_len, half_permuted_len, shifts[n], half_permuted_len);
        permute_bits(CD[n], subkeys[n], 0, 0, PC_2, sizeof(PC_2) / sizeof(int));
    }
}

void s_box(byte src[6], byte dst[4]) {
    for (size_t n = 0; n < 8; ++n) {
        unsigned i = (test_bit(src, n * 6) << 1) | (test_bit(src, n * 6 + 5));
        unsigned j =
                (test_bit(src, n * 6 + 1) << 3) | (test_bit(src, n * 6 + 2) << 2) | (test_bit(src, n * 6 + 3) << 1) |
                (test_bit(src, n * 6 + 4));
        byte value[1] = {S[n][i][j] << 4};
        copy_bits(value, dst, 0, n * 4, 4);
    }
}

void f(byte R[4], byte K[6], byte dst[4]) {
    byte expanded[6] = {0};
    permute_bits(R, expanded, 0, 0, E, sizeof(E) / sizeof(int));
    byte xored[6] = {0};
    xor_bits(K, expanded, xored, 48);
    byte sboxed[4] = {0};
    s_box(xored, sboxed);
    permute_bits(sboxed, dst, 0, 0, P, sizeof(P) / sizeof(int));
}

// Encode each 64-bit block of data
void process_block(byte block[BLOCK_BYTE_LEN], byte output[BLOCK_BYTE_LEN], enum MODE mode) {
    byte LR[18][BLOCK_BYTE_LEN] = {0};
    permute_bits(block, LR[0], 0, 0, IP, sizeof(IP) / sizeof(int));

    for (size_t n = 1; n <= 16; ++n) {
        byte L[4] = {0}, R[4] = {0};
        copy_bits(LR[n - 1], L, 0, 0, 32);
        copy_bits(LR[n - 1], R, 32, 0, 32);

        // Ln = Rn-1
        copy_bits(R, LR[n], 0, 0, 32);

        // Rn = Ln-1 + f(Rn-1, Kn)
        byte f_output[4] = {0};
        switch (mode) {
            case ENCRYPT:
                f(R, subkeys[n], f_output);
                break;
            case DECRYPT:
                f(R, subkeys[16 - n + 1], f_output);
                break;
            default:
                break;
        }
        byte new_R[4] = {0};
        xor_bits(L, f_output, new_R, 32);

        copy_bits(new_R, LR[n], 0, 32, 32);
    }

    copy_bits(LR[16], LR[17], 0, 32, 32);
    copy_bits(LR[16], LR[17], 32, 0, 32);

    permute_bits(LR[17], output, 0, 0, IP_INV, sizeof(IP_INV) / sizeof(int));
}

void encrypt_block(byte block[BLOCK_BYTE_LEN], byte output[BLOCK_BYTE_LEN]) {
    process_block(block, output, ENCRYPT);
}

void decrypt_block(byte block[BLOCK_BYTE_LEN], byte output[BLOCK_BYTE_LEN]) {
    process_block(block, output, DECRYPT);
}