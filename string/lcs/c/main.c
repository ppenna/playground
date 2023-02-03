// Copyright (C) 2023 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Returns the maximum of two values.
static size_t max(size_t a, size_t b)
{
    return (a > b) ? a : b;
}

// Prints the solution of LCS.
static void print_lcs(char *output, const char *s1, const char *s2, size_t len1, size_t len2, size_t table[len1][len2])
{
    size_t i = len1 - 1;
    size_t j = len2 - 1;
    size_t k = table[len1 - 1][len2 - 1];

    output[k] = '\0';

    while ((i > 0) && (j > 0)) {
        if (s1[i - 1] == s2[j - 1]) {
            output[k - 1] = s1[i - 1];
            i--, j--, k--;
        } else if (table[i - 1][j] > table[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
}

// Searches for longest common subsequence between two strings.
static void lcs(char *solution, const char *str1, const char *str2)
{
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    size_t table[len1 + 1][len2 + 1];

    // Fill in dynamic programming table.
    for (size_t i = 0; i <= len1; i++) {
        for (size_t j = 0; j <= len2; j++) {
            // Empty subsequence.
            if ((i == 0) || (j == 0)) {
                table[i][j] = 0;
            }
            // Extend longest common subsequence.
            else if (str1[i - 1] == str2[j - 1]) {
                table[i][j] = table[i - 1][j - 1] + 1;
                continue;
            }
            // Take the maximum longest common subsequence so far.
            else {
                table[i][j] = max(table[i - 1][j], table[i][j - 1]);
            }
        }
    }

    // Print solution.
    print_lcs(solution, str1, str2, len1 + 1, len2 + 1, table);
}

// Tests LCS.
static void test(const char *str1, const char *str2, bool verbose)
{
    size_t maxlen = 4096;
    char result[maxlen];
    double tstart = 0.0;
    double tend = 0.0;
    const double MICROSECS = ((CLOCKS_PER_SEC / 1000000.0));

    if (verbose) {
        printf("Search: \'%s\', \'%s\'\n", str1, str2);
    }

    // Search string.
    tstart = clock();
    lcs(result, str1, str2);
    tend = clock();

    // Report time.
    printf("lcs: %2.lf us\n", (tend - tstart) / MICROSECS);

    if (verbose) {
        printf("Output: %s\n", (result != NULL) ? result : "not found");
    }
}

// Prints program usage and exits.
static void usage(char *const argv[])
{
    printf("%s - Testing program for lcs.\n", argv[0]);
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
