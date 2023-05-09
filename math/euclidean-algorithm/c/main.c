// Copyright (C) 2022 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//==============================================================================
// Euclidean Algorithm
//==============================================================================

// Computes the greatest common divisor of two numbers.
static unsigned euclidean_algorithm(unsigned a, unsigned b)
{
    unsigned r = 0;

    while (b != 0) {
        r = a % b;
        a = b;
        b = r;
    }

    return (a);
}

//==============================================================================
// Test
//==============================================================================

// Tests function.
static void test(unsigned a, unsigned b, bool verbose)
{
    double tstart = 0.0;
    double tend = 0.0;
    unsigned gcd = 0;
    const double MICROSECS = ((CLOCKS_PER_SEC / 1000000.0));

    if (verbose) {
        printf("a = %u, b = %u\n", a, b);
    }

    // Run.
    tstart = clock();
    gcd = euclidean_algorithm(a, b);
    tend = clock();
    if (verbose) {
        printf("gcd = %u\n", gcd);
    }
    printf("%12s: %2.lf us\n",
           "euclidean_algorithm()",
           (tend - tstart) / MICROSECS);
}

//==============================================================================
// Usage
//==============================================================================

// Prints program usage and exits.
static void usage(char *const argv[])
{
    printf("%s - Testing program for eucliean algorithm.\n", argv[0]);
    printf("Usage: %s [--verbose] <first number> <second number>\n", argv[0]);
    exit(EXIT_FAILURE);
}

//==============================================================================
// Main
//==============================================================================

// Drives the test function.
int main(int argc, char *const argv[])
{
    unsigned a = 0;
    unsigned b = 0;
    bool verbose = false;

    // Check for missing arguments.
    if ((argc < 3) || (argc > 4)) {
        printf("Error: invalid number of arguments.\n");
        usage(argv);
    }

    // Parse command line arguments.
    if (argc == 3) {
        sscanf(argv[1], "%u", &a);
        sscanf(argv[2], "%u", &b);
    } else if ((argc == 4) && (!strcmp(argv[1], "--verbose"))) {
        sscanf(argv[2], "%u", &a);
        sscanf(argv[3], "%u", &b);
        verbose = true;
    } else {
        printf("Error: invalid arguments.\n");
        usage(argv);
    }

    // Run it!
    test(a, b, verbose);

    return (EXIT_SUCCESS);
}
