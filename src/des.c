#include "des.h"

uint64_t desRound(uint64_t block, uint64_t key, char verbose) {
    // Split left and right halves
    uint32_t right = block & 0xFFFFFFFF;
    uint32_t left = block >> 32;
    // Put right though e-table
    uint64_t right_e = expand(right);
    // Verbose print
    if(verbose > 1) printf("E      : %012lx\n", right_e);
    // XOR right with the key
    uint64_t right_k = right_e ^ key;
    // Verbose print
    if(verbose > 1) printf("KS     : %012lx\nE + KS : %012lx\n", key, right_k);
    // Put right through s-box
    uint32_t right_s = substitute(right_k);
    // Verbose print
    if(verbose > 1) printf("Sbox   : %08x\n", right_s);
    // Permute right
    uint32_t right_p = permute(right_s);
    // Verbose print
    if(verbose > 1) printf("P      : %08x\n", right_p);
    // XOR right with the left
    uint32_t right_l = right_p ^ left;
    // Verbose print
    if(verbose > 1) printf("L[i]   : %08x\nR[i]   : %08x\n", right, right_l);
    // Return
    return ((uint64_t) right) << 32 | (uint64_t) right_l;
}

uint64_t encrypt(uint64_t plaintext, uint64_t key, size_t n, char verbose) {
    // Start out w/ initial permutation
    uint64_t result = initialPermutation(plaintext);
    // Verbose print
    if(verbose == 1) printf("Round: IP\n K:\n L: %08lx\n R: %08lx\n", result >> 32, result & 0xFFFFFFFF);
    if(verbose > 1) printf("Input  : %lx\nKey    : %lx\n\n", plaintext, key);
    // PC1 key
    key = pc1(key);
    // Verbose print
    if(verbose > 1) printf("CD[0]  : %014lx\n", key);
    // Generate 16 round keys
    uint64_t roundKeys[16];
    for(size_t i = 0; i < 16; i++) {
        // Shift key
        key = shiftKey(key, i);
        // Verbose print
        if(verbose > 1) printf("CD[%02ld] : %014lx\nKS[%02ld] : %012lx\n", i + 1, key, i + 1, pc2(key));
        // Save key
        roundKeys[i] = pc2(key);
    }
    // Verbose print
    if(verbose > 1) printf("\nL[0]   : %08lx\nR[0]   : %08lx\n\n", result >> 32, result & 0xFFFFFFFF);
    // Perform n rounds of des
    for(size_t i = 0; i < n; i++) {
        // Verbose print
        if(verbose > 1) printf("Round %ld\n", i + 1);
        // Perform single round
        result = desRound(result, roundKeys[i % 16], verbose);
        // Verbose print
        if(verbose > 1) printf("\n");
        if(verbose == 1) printf("Round: %ld\n K: %016lx\n L: %08lx\n R: %08lx\n", i + 1, pc2(key), result >> 32, result & 0xFFFFFFFF);
    }
    // Reverse the left and right
    result = (result >> 32) | (result << 32);
    // Verbose print
    if(verbose > 1) printf("RL[16] : %016lx\n\n", result);
    // Perform inverse IP
    result = inverseInitialPermutation(result);
    // Verbose print
    if(verbose == 1) printf("Round: IP-1\n K:\n L: %08lx\n R: %08lx\n", result >> 32, result & 0xFFFFFFFF);
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
        key = shiftKey(key, i);
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
        result = desRound(result, pc2(subkeys[15 - (i % 16)]), 0);
        // Verbose print
        if(verbose) printf("Round: %ld\n K: %016lx\n L: %08lx\n R: %08lx\n", i + 1, pc2(subkeys[15 - (i % 16)]), result >> 32, result & 0xFFFFFFFF);
    }
    // Reverse the left and right
    result = (result >> 32) | (result << 32);
    // Perform IP
    result = initialPermutation(result);
    // Verbose print
    if(verbose) printf("Round: IP\n K:\n L: %08lx\n R: %08lx\n", result >> 32, result & 0xFFFFFFFF);
    // Return as plaintext
    return result;
}