#include <stdint.h>
#include <stdlib.h>

#define BOX_ROWS 4
#define BOX_COLS 16
#define NUM_SBOXES 8 

uint8_t substitute(uint8_t block, uint8_t boxIdx);
uint32_t substituteAll(uint64_t block);