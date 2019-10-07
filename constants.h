//
// Created by Liuhaohua on 2019/10/2.
//

#ifndef DES_CONSTANTS_H
#define DES_CONSTANTS_H

#include "types.h"

#define KEY_BYTE_LEN 8
#define BLOCK_BYTE_LEN 8

enum MODE {
    ENCRYPT, DECRYPT
};

extern const size_t KEY_LEN;

extern const int shifts[17];

extern const int PC_1[56];

extern const int PC_2[48];

extern const int P[32];

extern const int IP[64];

extern const int IP_INV[64];

extern const int E[48];

extern const int S[8][4][16];

#endif //DES_CONSTANTS_H
