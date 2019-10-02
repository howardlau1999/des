//
// Created by Liuhaohua on 2019/10/2.
//

#include "des.h"
#include "utility.h"

void permute_bits(const byte* src, byte* dst, const int permutation[], const int n) {
    for (int i = 0; i < n; ++i) {
        if (test_bit(src, permutation[i] - 1))
            set_bit(dst, i);
        else
            clear_bit(dst, i);
    }
}


