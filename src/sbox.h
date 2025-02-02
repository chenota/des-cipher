#ifndef SBOX_H
#define SBOX_H

#include <stdint.h>
#include <stdlib.h>

#define BOX_ROWS 4
#define BOX_COLS 16
#define NUM_SBOXES 8 

uint32_t substituteAll(uint64_t block);

#endif