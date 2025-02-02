#ifndef DES_H
#define DES_H

#include <stdint.h>
#include <stdlib.h>
#include "pbox.h"
#include "sbox.h"
#include "keygen.h"
#include "stdio.h"

uint64_t doDES(uint64_t plaintext, uint64_t key, size_t n, char mode, char verbose);

#endif