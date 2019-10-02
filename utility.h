//
// Created by Liuhaohua on 2019/10/2.
//

#ifndef DES_UTILITY_H
#define DES_UTILITY_H

#include "types.h"

void set_bit(byte* addr, size_t nr);
void clear_bit(byte* addr, size_t nr);
_Bool test_bit(const byte* addr, size_t nr);

#endif //DES_UTILITY_H
