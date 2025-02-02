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

uint64_t expand(uint32_t block) {
    // Create space for new block
    uint64_t newBlock = 0;
    // Re-map bits of original block
    for(size_t i = 0; i < E_TABLE_SIZE; i++) newBlock |= ((block >> (E_TABLE[i] - 1)) & 1) << i;
    // Return new block
    return newBlock;
}

uint32_t permute(uint32_t block) {
    // Create space for new block
    uint64_t newBlock = 0;
    // Re-map bits of original block
    for(size_t i = 0; i < P_TABLE_SIZE; i++) newBlock |= ((block >> (P_TABLE[i] - 1)) & 1) << i;
    // Return new block
    return newBlock;
}

// Table for initial permutation
static const uint8_t IP_TABLE[64] = {
    {58, 50, 42, 34, 26, 18, 10, 2},
    {60, 52, 44, 36, 28, 20, 12, 4},
    {62, 54, 46, 38, 30, 22, 14, 6},
    {64, 56, 48, 40, 32, 24, 16, 8},
    {57, 49, 41, 33, 25, 17,  9, 1},
    {59, 51, 43, 35, 27, 19, 11, 3},
    {61, 53, 45, 37, 29, 21, 13, 5},
    {63, 55, 47, 39, 31, 23, 15, 7}
};

// Table for inverse initial permutation
static const uint8_t INV_IP_TABLE[64] = {
    {40, 8, 48, 16, 56, 24, 64, 32},
    {39, 7, 47, 15, 55, 23, 63, 31},
    {38, 6, 46, 14, 54, 22, 62, 30},
    {37, 5, 45, 13, 53, 21, 61, 29},
    {36, 4, 44, 12, 52, 20, 60, 28},
    {35, 3, 43, 11, 51, 19, 59, 27},
    {34, 2, 42, 10, 50, 18, 58, 26},
    {33, 1, 41,  9, 49, 17, 57, 25}
};

uint64_t initialPermutation(uint64_t block) {
    // Create space for new block
    uint64_t newBlock = 0;
    // Re-map bits of original block
    for(size_t i = 0; i < 64; i++) newBlock |= ((block >> (IP_TABLE[i] - 1)) & 1) << i;
    // Return new block
    return newBlock;
}

uint64_t inverseInitialPermutation(uint64_t block) {
    // Create space for new block
    uint64_t newBlock = 0;
    // Re-map bits of original block
    for(size_t i = 0; i < 64; i++) newBlock |= ((block >> (INV_IP_TABLE[i] - 1)) & 1) << i;
    // Return new block
    return newBlock;
}