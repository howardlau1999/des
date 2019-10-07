#include <stdio.h>
#include "utility.h"
#include "des.h"
#include "constants.h"

int main(int argc, char *argv[]) {
    enum MODE mode = ENCRYPT;
    switch (argv[1][0]) {
        case 'd':
            mode = DECRYPT;
            break;
        case 'e':
            mode = ENCRYPT;
            break;
    }
    FILE *in = fopen(argv[2], "rb");
    FILE *out = fopen(argv[3], "wb");
    FILE *key = fopen(argv[4], "rb");

    // Read key
    byte key_buf[KEY_BYTE_LEN];
    fread(key_buf, 1, KEY_BYTE_LEN, key);
    create_subkeys(key_buf);

    // Iterate all blocks;
    size_t len = 0;
    byte in_buf[BLOCK_BYTE_LEN] = {0};
    byte out_buf[BLOCK_BYTE_LEN] = {0};
    while (!feof(in)) {
        size_t _n = fread(in_buf, 1, 8, in);
        if (mode == DECRYPT && _n == 0)
            break;
        for (byte pad_byte = BLOCK_BYTE_LEN - _n; mode == ENCRYPT && _n < BLOCK_BYTE_LEN; ++_n) {
            in_buf[_n] = pad_byte;
        }
        process_block(in_buf, out_buf, mode);
        fwrite(out_buf, 1, BLOCK_BYTE_LEN, out);
    }

    fclose(in);
    fclose(out);
    fclose(key);

    return 0;
}