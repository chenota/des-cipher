#include <stdint.h>
#include <stdlib.h>

#define P_TABLE_SIZE 32
#define E_TABLE_SIZE 48

uint64_t expand(uint64_t block);
uint64_t permute(uint64_t block);