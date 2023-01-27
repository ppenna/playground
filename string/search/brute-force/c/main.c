// Copyright (C) 2023 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Reads a line from a stream.
static int readline(FILE *stream, char *buffer, size_t maxlen)
{
    size_t length = 0;

    // Readline.
    if (fgets(buffer, maxlen, stream) == NULL)
        return (length);

    length = strlen(buffer);

    // Handle string truncation
    if (buffer[length - 1] != '\n') {
        // Read all remainder characters until we hit a new line.
        for (char ch = getchar(); (ch != '\n') && (ch != EOF); ch = getchar()) {
            // noop.
        }
        return length;
    }

    // Replace newline character.
    buffer[length - 1] = '\0';
    return (length - 1);
}

// Searches for a pattern in a text using a Brute Force algorithm.
static const char *brute_force(const char *text, const char *pattern)
{
    size_t textlen = strlen(text);
    size_t patternlen = strlen(pattern);

    // For each character in the text...
    for (size_t i = 0; i < textlen - patternlen; i++) {
        size_t j = 0;

        // ... try to match a pattern starting there.
        for (j = 0; j < patternlen; j++) {
            // Mismatch.
            if (pattern[j] != text[i + j]) {
                break;
            }
        }

        // Matched.
        if (j == patternlen) {
            return (&text[i]);
        }
    }

    // Not found.
    return (NULL);
}

// Tests Binary Search.
static void test(const char *pattern, bool verbose)
{
    size_t maxlen = 4096;
    char text[maxlen];
    const char *result = NULL;
    double tstart = 0.0;
    double tend = 0.0;
    const double MICROSECS = ((CLOCKS_PER_SEC / 1000000.0));

    // Read input.
    readline(stdin, text, maxlen);

    if (verbose) {
        printf("Search: pattern = \'%s\'\n", pattern);
    }

    // Search string.
    tstart = clock();
    result = brute_force(text, pattern);
    tend = clock();

    // Report time.
    printf("KMP: %2.lf us\n", (tend - tstart) / MICROSECS);

    if (verbose) {
        printf("Output: %s\n", (result != NULL) ? "found" : "not found");
    }

    // Sanity check result.
    for (size_t i = 0; i < strlen(pattern); i++) {
        assert(result[i] == pattern[i]);
    }
}

// Prints program usage and exits.
static void usage(char *const argv[])
{
    printf("%s - Testing program for kmp.\n", argv[0]);
    printf("Usage: %s [--verbose] <pattern>\n", argv[0]);
    exit(EXIT_FAILURE);
}

// Drives the test function.
int main(int argc, char *const argv[])
{
    const char *pattern = NULL;
    bool verbose = false;

    // Check for missing arguments.
    if ((argc < 2) || (argc > 3)) {
        printf("Error: invalid number of arguments.\n");
        usage(argv);
    }

    // Parse command line arguments.
    if (argc == 2) {
        pattern = argv[1];
    } else if ((argc == 3) && (!strcmp(argv[1], "--verbose"))) {
        pattern = argv[2];
        verbose = true;
    } else {
        printf("Error: invalid arguments.\n");
        usage(argv);
    }

    // Run it!
    test(pattern, verbose);

    return (EXIT_SUCCESS);
}
