#include "des.h"

uint64_t desRound(uint64_t block, uint64_t key) {
    // Split left and right halves
    uint32_t right = block & 0xFFFFFFFF;
    uint32_t left = block >> 32;
    // Put right though e-table
    uint64_t right_e = expand(right);
    // XOR right with the key
    uint64_t right_k = right ^ key;
    // Put right through s-box
    uint32_t right_s = substitute(right_k);
    // Permute right
    uint32_t right_p = permute(right_s);
    // XOR right with the left
    uint32_t right_l = right_p ^ left;
    // Return
    return ((uint64_t) right) << 32 | (uint64_t) right_l;
}

uint64_t encrypt(uint64_t plaintext, uint64_t key, size_t n, char verbose) {
    // Start out w/ initial permutation
    uint64_t result = initialPermutation(plaintext);
    // Verbose print
    if(verbose) printf("Round: IP\n K:\n L: %08lx\n R: %08lx\n", result >> 32, result & 0xFFFFFFFF);
    // PC1 key
    key = pc1(key);
    // Perform n rounds of des
    for(size_t i = 0; i < n; i++) {
        // Perform shift and pc2 on key
        key = pc2(shiftKey(key, i));
        // Perform single round
        result = desRound(result, key);
        // Verbose print
        if(verbose) printf("Round: %ld\n K: %016lx\n L: %08lx\n R: %08lx\n", i + 1, key, result >> 32, result & 0xFFFFFFFF);
    }
    // Perform inverse IP
    result = inverseInitialPermutation(result);
    // Return as ciphertext
    return result;  
}

uint64_t decrypt(uint64_t ciphertext, uint64_t key, size_t n, char verbose) {
    // PC1 key
    key = pc1(key);
    // Generate 16 round sub-keys
    uint64_t subkeys[16];
    for(size_t i = 0; i < 16; i++) { 
        // Shift key
        key = pc2(shiftKey(key, i));
        // Save key
        subkeys[i] = key; 
    }
    // Start out w/ inverse initial permutation
    uint64_t result = inverseInitialPermutation(ciphertext);
    // Verbose print
    if(verbose) printf("Round: IP-1\n K:\n L: %08lx\n R: %08lx\n", result >> 32, result & 0xFFFFFFFF);
    // Perform n rounds of DES, count through keys backwards
    for(size_t i = 0; i < n; i++) {
        // Perform single round
        result = desRound(result, subkeys[15 - (i % 16)]);
        // Verbose print
        if(verbose) printf("Round: %ld\n K: %016lx\n L: %08lx\n R: %08lx\n", i + 1, subkeys[15 - (i % 16)], result >> 32, result & 0xFFFFFFFF);
    }
    // Perform IP
    result = initialPermutation(result);
    // Return as plaintext
    return result;
}