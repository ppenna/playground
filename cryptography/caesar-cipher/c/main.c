// Copyright (C) 2022 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//==============================================================================
// Ceasar Cipher
//==============================================================================

// Encrypts a text using the Ceasar Cipher.
static char *ceaser_cipher(unsigned key, const char *text)
{
    char *ciphertext = NULL;
    size_t len = strlen(text);

    ciphertext = malloc((len + 1) * sizeof(char));
    assert(ciphertext != NULL);

    for (size_t i = 0; i < len; i++) {
        ciphertext[i] = (text[i] + key) & 255;
    }

    ciphertext[len] = '\0';

    return (ciphertext);
}

// Decrypts a text using the Ceasar Cipher.
static char *ceaser_decipher(unsigned key, const char *text)
{
    char *plaintext = NULL;
    size_t len = strlen(text);

    plaintext = malloc((len + 1) * sizeof(char));
    assert(plaintext != NULL);

    for (size_t i = 0; i < len; i++) {
        plaintext[i] = (text[i] - key) & 255;
    }

    plaintext[len] = '\0';

    return (plaintext);
}

//==============================================================================
// Test
//==============================================================================

// Tests function.
static void test(unsigned key, const char *text, bool verbose)
{
    double tstart = 0.0;
    double tend = 0.0;
    char *ciphertext = NULL;
    char *plaintext = NULL;
    const double MICROSECS = ((CLOCKS_PER_SEC / 1000000.0));

    if (verbose) {
        printf("key = %u\n", key);
        printf("text = %s\n", text);
    }

    // Cipher.
    tstart = clock();
    ciphertext = ceaser_cipher(key, text);
    tend = clock();
    if (verbose) {
        printf("ciphertext = %s\n", ciphertext);
    }
    printf("%12s: %2.lf us\n", "ceaser_cipher()", (tend - tstart) / MICROSECS);

    // Decipher.
    tstart = clock();
    plaintext = ceaser_decipher(key, ciphertext);
    tend = clock();
    if (verbose) {
        printf("plaintext = %s\n", plaintext);
    }
    printf(
        "%12s: %2.lf us\n", "ceaser_decipher()", (tend - tstart) / MICROSECS);

    // Release resources.
    free(ciphertext);
    free(plaintext);
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

    // Run it!
    test(key, text, verbose);

    return (EXIT_SUCCESS);
}
