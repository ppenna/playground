// Copyright (C) 2023 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Returns the minimum of three values.
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

// Computes the Levenshtein distance between two strings.
static size_t levenshtein(const char *str1, const char *str2)
{
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    size_t table[len1 + 1][len2 + 1];

    // Fill in dynamic programming table.
    for (size_t i = 0; i <= len1; i++) {
        for (size_t j = 0; j <= len2; j++) {
            // Delete all characters.
            if (i == 0) {
                table[0][j] = j;
            }
            // Insert all characters.
            else if (j == 0) {
                table[i][0] = i;
            }
            // Extend levenshtein distance.
            else {
                size_t cost = (str1[i - 1] == str2[j - 1]) ? 0 : 1;
                table[i][j] = MIN3(table[i - 1][j] + 1, table[i][j - 1] + 1, table[i - 1][j - 1] + cost);
            }
        }
    }

    return (table[len1][len2]);
}

// Tests Levenshtein.
static void test(const char *str1, const char *str2, bool verbose)
{
    size_t distance = 0;
    double tstart = 0.0;
    double tend = 0.0;
    const double MICROSECS = ((CLOCKS_PER_SEC / 1000000.0));

    if (verbose) {
        printf("Compare: \'%s\', \'%s\'\n", str1, str2);
    }

    // Search string.
    tstart = clock();
    distance = levenshtein(str1, str2);
    tend = clock();

    // Report time.
    printf("levenstein: %2.lf us\n", (tend - tstart) / MICROSECS);

    if (verbose) {
        printf("Output: %d\n", distance);
    }
}

// Prints program usage and exits.
static void usage(char *const argv[])
{
    printf("%s - Testing program for levenshtein.\n", argv[0]);
    printf("Usage: %s [--verbose] <str 1> <str 2>\n", argv[0]);
    exit(EXIT_FAILURE);
}

// Drives the test function.
int main(int argc, char *const argv[])
{
    const char *str1 = NULL;
    const char *str2 = NULL;
    bool verbose = false;

    // Check for missing arguments.
    if ((argc < 3) || (argc > 4)) {
        printf("Error: invalid number of arguments.\n");
        usage(argv);
    }

    // Parse command line arguments.
    if (argc == 3) {
        str1 = argv[1];
        str2 = argv[2];
    } else if ((argc == 4) && (!strcmp(argv[1], "--verbose"))) {
        str1 = argv[2];
        str2 = argv[3];
        verbose = true;
    } else {
        printf("Error: invalid arguments.\n");
        usage(argv);
    }

    // Run it!
    test(str1, str2, verbose);

    return (EXIT_SUCCESS);
}
