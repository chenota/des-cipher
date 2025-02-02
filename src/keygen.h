#include <stdint.h>
#include <stdlib.h>

#define PC1_SIZE 56
#define HALF_PC1_SIZE (PC1_SIZE / 2)
#define PC2_SIZE 48
#define MAX_ROUNDS 16

uint64_t pc1(uint64_t block);
uint64_t pc2(uint64_t block);
uint64_t shift_key(uint64_t block, uint8_t round);