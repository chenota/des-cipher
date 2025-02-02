#include <stdint.h>
#include <stdlib.h>

#define P_TABLE_SIZE 32
#define E_TABLE_SIZE 48

uint64_t expand(uint32_t block);
uint32_t permute(uint32_t block);