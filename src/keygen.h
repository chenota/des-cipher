#ifndef KEYGEN_H
#define KEYGEN_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define PC1_SIZE 56
#define HALF_PC1_SIZE 28
#define PC2_SIZE 48
#define MAX_ROUNDS 16

uint64_t pc1(uint64_t block);
uint64_t pc2(uint64_t block);
uint64_t shiftKey(uint64_t block, size_t round);

#endif