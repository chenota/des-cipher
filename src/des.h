#ifndef DES_H
#define DES_H

#include <stdint.h>
#include <stdlib.h>
#include "pbox.h"
#include "sbox.h"
#include "keygen.h"

uint64_t encrypt(uint64_t plaintext, uint64_t key, size_t n);
uint64_t decrypt(uint64_t ciphertext, uint64_t key, size_t n);

#endif