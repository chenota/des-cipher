#ifndef SBOX_H
#define SBOX_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define BOX_ROWS 4
#define BOX_COLS 16
#define NUM_SBOXES 8 

uint32_t substitute(uint64_t block);

#endif