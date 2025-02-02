#include <stdint.h>
#include <stdlib.h>

#define BOX_ROWS 4
#define BOX_COLS 16
#define NUM_SBOXES 8 

uint64_t substitute(uint64_t block, uint8_t boxIdx);