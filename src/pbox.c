#include "pbox.h"

static const uint8_t E_TABLE[E_TABLE_SIZE] = {
    {32,  1,  2,  3,  4,  5},
    { 4,  5,  6,  7,  8,  9},
    { 8,  9, 10, 11, 12, 13},
    {12, 13, 14, 15, 16, 17},
    {16, 17, 18, 19, 20, 21},
    {20, 21, 22, 23, 24, 25},
    {24, 25, 26, 27, 28, 29},
    {28, 29, 30, 31, 32,  1}
};

static const uint8_t P_TABLE[P_TABLE_SIZE] = {
    {16,  7, 20, 21, 29, 12, 28, 17},
    { 1, 15, 23, 26,  5, 18, 31, 10},
    { 2,  8, 24, 14, 32, 27,  3,  9},
    {19, 13, 30,  6, 22, 11,  4, 25}
};

uint64_t expand(uint64_t block) {
    // Create space for new block
    uint64_t newBlock = 0;
    // Re-map bits of original block
    for(size_t i = 0; i < E_TABLE_SIZE; i++) newBlock |= ((block >> (E_TABLE[i] - 1)) & 1) << i;
    // Return new block
    return newBlock;
}

uint64_t permute(uint64_t block) {
    // Create space for new block
    uint64_t newBlock = 0;
    // Re-map bits of original block
    for(size_t i = 0; i < P_TABLE_SIZE; i++) newBlock |= ((block >> (P_TABLE[i] - 1)) & 1) << i;
    // Return new block
    return newBlock;
}