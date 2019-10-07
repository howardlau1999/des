# C implementation of DES algorithm

Note: this implementation uses PKCS#5 padding for original message.

## Build

```bash
mkdir build && cd build
cmake ..
make
```

## Run

This program accepts any file format as input. There is already a demo key file in the project.

### Encryption

```bash
./des e plain.txt encrpyted.bin key.bin
```

### Decryption

```bash
./des d encrpyted.bin decrypted.txt key.bin
```