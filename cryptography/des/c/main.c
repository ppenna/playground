// Copyright (C) 2022 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//==============================================================================
// Data Standard Encryption.
//==============================================================================

// Permutation table used in the "Initial Permutation Step" of DES algorithm.
static unsigned IP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2, //
    60, 52, 44, 36, 28, 20, 12, 4, //
    62, 54, 46, 38, 30, 22, 14, 6, //
    64, 56, 48, 40, 32, 24, 16, 8, //
    57, 49, 41, 33, 25, 17, 9,  1, //
    59, 51, 43, 35, 27, 19, 11, 3, //
    61, 53, 45, 37, 29, 21, 13, 5, //
    63, 55, 47, 39, 31, 23, 15, 7  //
};

// Permutation table used in the "Final Permutation Step" of DES algorithm.
static unsigned FP[64] = {
    40, 8, 48, 16, 56, 24, 64, 32, //
    39, 7, 47, 15, 55, 23, 63, 31, //
    38, 6, 46, 14, 54, 22, 62, 30, //
    37, 5, 45, 13, 53, 21, 61, 29, //
    36, 4, 44, 12, 52, 20, 60, 28, //
    35, 3, 43, 11, 51, 19, 59, 27, //
    34, 2, 42, 10, 50, 18, 58, 26, //
    33, 1, 41, 9,  49, 17, 57, 25  //
};

// Permutation table used in the "Expansion Step" of Feistel function.
static unsigned E[48] = {
    32, 1,  2,  3,  4,  5,  //
    4,  5,  6,  7,  8,  9,  //
    8,  9,  10, 11, 12, 13, //
    12, 13, 14, 15, 16, 17, //
    16, 17, 18, 19, 20, 21, //
    20, 21, 22, 23, 24, 25, //
    24, 25, 26, 27, 28, 29, //
    28, 29, 30, 31, 32, 1   //
};

// Permutation table used in the "Permutation Step" of Feistel function.
static unsigned P[64] = {
    16, 7,  20, 21, //
    29, 12, 28, 17, //
    1,  15, 23, 26, //
    5,  18, 31, 10, //
    2,  8,  24, 14, //
    32, 27, 3,  9,  //
    19, 13, 30, 6,  //
    22, 11, 4,  25  //
};

// Substitution tables used in the "Substitution Step" of Feistel Function.
static uint8_t S[8][4][16] = {
    {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7}, //
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8}, //
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0}, //
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}  //
    },
    {
        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10}, //
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5}, //
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15}, //
        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}  //
    },
    {
        {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8}, //
        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1}, //
        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7}, //
        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}  //
    },
    {
        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15}, //
        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9}, //
        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4}, //
        {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}  //
    },
    {
        {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9}, //
        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6}, //
        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14}, //
        {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}  //
    },
    {
        {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11}, //
        {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8}, //
        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6}, //
        {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}  //
    },
    {
        {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1}, //
        {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6}, //
        {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2}, //
        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}  //
    },
    {
        {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7}, //
        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2}, //
        {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8}, //
        {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}  //
    },
};

// Permutation table used in the "Key Schedule Step" of DES algorithm.
static unsigned PC1[64] = {
    57, 49, 41, 33, 25, 17, 9,  //
    1,  58, 50, 42, 34, 26, 18, //
    10, 2,  59, 51, 43, 35, 27, //
    19, 11, 3,  60, 52, 44, 36, //
    63, 55, 47, 39, 31, 23, 15, //
    7,  62, 54, 46, 38, 30, 22, //
    14, 6,  61, 53, 45, 37, 29, //
    21, 13, 5,  28, 20, 12, 4   //
};

// Permutation table used in the "Key Schedule Step" of DES algorithm.
static unsigned PC2[64] = {
    14, 17, 11, 24, 1,  5,  //
    3,  28, 15, 6,  21, 10, //
    23, 19, 12, 4,  26, 8,  //
    16, 7,  27, 20, 13, 2,  //
    41, 52, 31, 37, 47, 55, //
    30, 40, 51, 45, 33, 48, //
    44, 49, 39, 56, 34, 53, //
    46, 42, 50, 36, 29, 32  //
};

//==============================================================================
// Utility Functions
//==============================================================================

// Computes the permutation of a N-bit block.
static uint64_t permute(uint64_t blk, unsigned *t, unsigned n)
{
    uint64_t out = 0;

    // Traverses the block swapping bits according to the permutation table.
    for (unsigned i = 0; i < n; i++) {
        out |= ((blk & (((uint64_t)1) << (t[i] - 1))) >> (t[i] - 1)) << i;
    }

    return (out);
}

// Converts a text string to a binary string.
static void txt2bin(uint64_t *bin, const char *txt, size_t n)
{
    // Handle all full 8-byte blocks.
    for (unsigned i = 0; i < n; i += 8) {
        unsigned j = i >> 3;
        bin[j] = 0;
        for (unsigned k = 0; k < 8; k++) {
            uint8_t c = txt[i + k];
            bin[j] |= (uint64_t)c << (k << 3);
        }
    }

    // Handle corner case when n is not a multiple of 8.
    for (unsigned i = (n / 8) * 8; i < n; i++) {
        bin[n >> 3] |= (uint64_t)txt[i] << ((i & 7) << 3);
    }
}

// Converts a binary string to a text string.
static void bin2txt(char *txt, const uint64_t *bin, size_t n)
{
    // Handle all full 8-byte blocks.
    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j < 8; j++) {
            uint8_t c = (bin[i] & ((uint64_t)0xff << (j << 3))) >> (j << 3);
            txt[(i << 3) + j] = c;
        }
    }

    // Ensure a null-terminated string.
    txt[n << 3] = '\0';
}

//==============================================================================
// Feistel Function
//==============================================================================

// Computes the "Expansion Step" of the Feistel function.
static uint64_t feistel_expansion(uint32_t blk)
{
    return (permute(blk, E, 48));
}

// Computes the "Key Mixing Step" of the Feistel function.
static uint64_t feistel_key_mixing(uint64_t e, uint64_t subkey)
{
    return (e ^ subkey);
}

// Computes the "Substitution Step" of the Feistel function.
static uint32_t feistel_substitution(uint64_t x)
{
    uint32_t s = 0;

    for (unsigned i = 0, j = 0; i < 48; i += 6, j++) {
        uint8_t y = x & (0x3f << i) >> i;

        // Select first and last bits (X----X).
        unsigned row = ((y & (1 << 5)) >> 4) + (y & 1);

        // Select middle 4 bits (-XXXX-).
        unsigned col = (y & 0x1E) >> 1;

        s |= S[j][row][col] << (j << 2);
    }

    return (s);
}

// Computes the "Permutation Step" of the Feistel function.
static uint32_t feistel_permutation(uint32_t block)
{
    return (permute(block, P, 32));
}

// Computes the Feistel function.
static uint64_t feistel(uint32_t block, uint64_t subkey)
{
    uint64_t e = feistel_expansion(block);
    uint64_t x = feistel_key_mixing(e, subkey);
    uint32_t s = feistel_substitution(x);
    uint32_t p = feistel_permutation(s);

    return (p);
}

//==============================================================================
// DES
//==============================================================================

// Computes the key schedule for the DES algorithm.
static uint64_t key_schedule(uint64_t key, unsigned round)
{
    uint64_t permutated_key = permute(key, PC1, 64);
    uint32_t left = permutated_key >> 28;
    uint32_t right = permutated_key & 0xFFFFFFF;

    for (unsigned i = 0; i < round; i++) {
        left = (left << 1) | (left >> 27);
        right = (right << 1) | (right >> 27);
    }

    uint64_t cd = (left << 28) | right;

    return (permute(cd, PC2, 64));
}

// Encrypts a 64-bit block using the DES algorithm.
static uint64_t des_encrypt(uint64_t block, uint64_t key)
{
    uint64_t ip = permute(block, IP, 64);
    uint32_t left = (ip & 0xffffffff00000000) >> 32;
    uint32_t right = (ip & 0x000000000FFFFFFFF);

    for (unsigned i = 0; i < 16; i++) {
        uint64_t subkey = key_schedule(key, i);
        uint32_t new_left = right;
        uint32_t new_right = left ^ feistel(right, subkey);
        left = new_left;
        right = new_right;
    }

    uint64_t rl = ((uint64_t)right << 32) | (uint64_t)left;
    uint64_t fp = permute(rl, FP, 64);

    return (fp);
}

// Decrypts a 64-bit block using the DES algorithm.
static uint64_t des_decrypt(uint64_t block, uint64_t key)
{
    uint64_t ip = permute(block, IP, 64);
    uint32_t left = (ip & 0xffffffff00000000) >> 32;
    uint32_t right = (ip & 0x000000000FFFFFFFF);

    for (unsigned i = 0; i < 16; i++) {
        uint64_t subkey = key_schedule(key, 15 - i);
        uint32_t new_left = right;
        uint32_t new_right = left ^ feistel(right, subkey);
        left = new_left;
        right = new_right;
    }

    uint64_t rl = ((uint64_t)right << 32) | (uint64_t)left;
    uint64_t fp = permute(rl, FP, 64);

    return (fp);
}

//==============================================================================
// Test
//==============================================================================

// Tests function.
static void test(unsigned key, const char *input, bool verbose)
{
    double tstart = 0.0;
    double tend = 0.0;
    double tencrypt = 0.0;
    double tdecrypt = 0.0;
    size_t txtlen = strlen(input);
    size_t binlen = (txtlen / 8) + (((txtlen % 8) != 0) ? 1 : 0);
    uint64_t binary[binlen];
    char output[txtlen + 1];
    const double MICROSECS = ((CLOCKS_PER_SEC / 1000000.0));
    assert(txtlen != 0);

    if (verbose) {
        printf("key = %u\n", key);
        printf("text = %s\n", input);
        printf("text length = %lu\n", txtlen);
        printf("binary length = %lu\n", binlen);
    }

    txt2bin(binary, input, strlen(input));

    // Convert text to binary.
    for (unsigned i = 0; i < txtlen / 8 + 1; i++) {
        uint64_t tmp = 0;

        if (verbose) {
            printf("%16s = 0x%" PRIx64 "\n", "input block", binary[i]);
        }

        // Encrypt.
        tstart = clock();
        tmp = des_encrypt(binary[i], key);
        tend = clock();
        tencrypt += (tend - tstart);

        if (verbose) {
            printf("%16s = 0x%" PRIx64 "\n", "encrypted block", tmp);
        }

        // Decrypt.
        tstart = clock();
        binary[i] = des_decrypt(tmp, key);
        tend = clock();
        tdecrypt += (tend - tstart);

        if (verbose) {
            printf("%16s = 0x%" PRIx64 "\n", "decrypted block", binary[i]);
        }
    }

    bin2txt(output, binary, binlen);

    if (verbose) {
        printf("output = %s\n", output);
    }

    printf("%12s: %2.lf us\n", "des_encrypt()", (tend - tstart) / MICROSECS);
    printf("%12s: %2.lf us\n", "des_decrypt()", (tend - tstart) / MICROSECS);
}

//==============================================================================
// Usage
//==============================================================================

// Prints program usage and exits.
static void usage(char *const argv[])
{
    printf("%s - Testing program for caesar cipher.\n", argv[0]);
    printf("Usage: %s [--verbose] <key> <text>\n", argv[0]);
    exit(EXIT_FAILURE);
}

//==============================================================================
// Main
//==============================================================================

// Drives the test function.
int main(int argc, char *const argv[])
{
    unsigned key = 0;
    const char *text = NULL;
    bool verbose = false;

    // Check for missing arguments.
    if ((argc < 3) || (argc > 4)) {
        printf("Error: invalid number of arguments.\n");
        usage(argv);
    }

    // Parse command line arguments.
    if (argc == 3) {
        sscanf(argv[1], "%u", &key);
        text = argv[2];
    } else if ((argc == 4) && (!strcmp(argv[1], "--verbose"))) {
        sscanf(argv[2], "%u", &key);
        text = argv[3];
        verbose = true;
    } else {
        printf("Error: invalid arguments.\n");
        usage(argv);
    }

    // Sanity check arguments.
    if (strlen(text) == 0) {
        printf("Error: missing input text\n");
        usage(argv);
    }

    // Run it!
    test(key, text, verbose);

    return (EXIT_SUCCESS);
}
