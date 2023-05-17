// Copyright (C) 2022 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//==============================================================================
// Sieve of Eratosthenes
//==============================================================================

// Sieve of Eratosthenes.
static void eratosthenes(unsigned *numbers, unsigned n)
{
    // Initialize.
    for (unsigned i = 0; i < n; i++) {
        numbers[i] = i;
    }

    // Run sieve.
    for (unsigned i = 2; i < n; i++) {
        if (numbers[i] != 0) {
            for (unsigned j = i + i; j < n; j += i) {
                numbers[j] = 0;
            }
        }
    }
}

//==============================================================================
// Test
//==============================================================================

// Tests Sieve of Eratosthenes.
static void test(unsigned n, bool verbose)
{
    double tstart = 0.0;
    double tend = 0.0;
    const double MICROSECS = ((CLOCKS_PER_SEC / 1000000.0));
    unsigned *numbers = malloc(n * sizeof(unsigned));

    // Fix random number generator seed
    // to have a determinist behavior across runs.
    srand(0);

    // Run.
    tstart = clock();
    eratosthenes(numbers, n);
    tend = clock();

    // Report time.
    printf("Sieve of Eratoesthenes: %2.lf us\n", (tend - tstart) / MICROSECS);

    if (verbose) {
        printf("Prime Numbers:\n");
        for (unsigned i = 0; i < n; i++) {
            if (numbers[i] != 0) {
                printf("%u ", numbers[i]);
            }
        }
        printf("\n");
    }

    free(numbers);
}

//==============================================================================
// Usage
//==============================================================================

// Prints program usage and exits.
static void usage(char *const argv[])
{
    printf("%s - Testing program for sieve of eratosthenes.\n", argv[0]);
    printf("Usage: %s [--verbose] <max number>\n", argv[0]);
    exit(EXIT_FAILURE);
}

//==============================================================================
// Main
//==============================================================================

// Drives the test function.
int main(int argc, char *const argv[])
{
    unsigned n = 0;
    bool verbose = false;

    // Check for missing arguments.
    if ((argc < 2) || (argc > 3)) {
        printf("Error: invalid number of arguments.\n", argc);
        usage(argv);
    }

    // Parse command line arguments.
    if (argc == 2) {
        sscanf(argv[1], "%u", &n);
    } else if ((argc == 3) && (!strcmp(argv[1], "--verbose"))) {
        sscanf(argv[2], "%u", &n);
        verbose = true;
    } else {
        printf("Error: invalid arguments.\n");
        usage(argv);
    }

    // Run it!
    test(n, verbose);

    return (EXIT_SUCCESS);
}
