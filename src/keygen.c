#include "keygen.h"

// Table for pc1
static const uint8_t PC1_TABLE[PC1_SIZE] = {
    57, 49, 41, 33, 25, 17,  9,
     1, 58, 50, 42, 34, 26, 18,
    10,  2, 59, 51, 43, 35, 27,
    19, 11,  3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
     7, 62, 54, 46, 38, 30, 22,
    14,  6, 61, 53, 45, 37, 29,
    21, 13,  5, 28, 20, 12,  4
};

// Table for pc2
static const uint8_t PC2_TABLE[PC2_SIZE] = {
    14, 17, 11, 24,  1,  5,
     3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8,
    16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

// Key shift schedule
static const uint8_t SHIFT_SCHEDULE[MAX_ROUNDS] = {
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

uint64_t pc1(uint64_t block) {
    // Create space for new block
    uint64_t newBlock = 0;
    // Re-map bits of original block
    for(size_t i = 0; i < PC1_SIZE; i++) newBlock |= ((block >> (64 - PC1_TABLE[i])) & 1) << PC1_SIZE - (i + 1);
    // Return new block
    return newBlock;
}

uint64_t pc2(uint64_t block) {
    // Create space for new block
    uint64_t newBlock = 0;
    // Re-map bits of original block
    for(size_t i = 0; i < PC2_SIZE; i++) newBlock |= ((block >> (PC1_SIZE - PC2_TABLE[i])) & 1) << PC2_SIZE - (i + 1);
    // Return new block
    return newBlock;
}

uint64_t shiftKey(uint64_t block, size_t round) {
    // Compute masks to isolate top and bottom halfs of block
    const uint64_t mask = (1 << HALF_PC1_SIZE) - 1;
    // Get shift amount
    const uint8_t shiftAmount = SHIFT_SCHEDULE[round % MAX_ROUNDS];
    // Isolate sections c and d
    uint64_t right = block & mask;
    uint64_t left = (block >> HALF_PC1_SIZE) & mask;
    // Left rotate each section according to schedule amount
    right = ((right << shiftAmount) | ((right >> (HALF_PC1_SIZE - shiftAmount)) & ((1 << shiftAmount) - 1))) & mask;
    left = ((left << shiftAmount) | ((left >> (HALF_PC1_SIZE - shiftAmount)) & ((1 << shiftAmount) - 1))) & mask;
    // Return result
    return (left << HALF_PC1_SIZE) | right;
}