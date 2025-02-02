#ifndef PBOX_H
#define PBOX_H

#include <stdint.h>
#include <stdlib.h>

#define P_TABLE_SIZE 32
#define E_TABLE_SIZE 48

uint64_t expand(uint32_t block);
uint32_t permute(uint32_t block);
uint64_t initialPermutation(uint64_t block);
uint64_t inverseInitialPermutation(uint64_t block);

#endif