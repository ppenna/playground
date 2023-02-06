// Copyright (C) 2023 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Checks if two strings match.
static size_t match(const char *s1, const char *s2, size_t length)
{
    // Check characters in reverse order.
    for (size_t j = length; j > 0; j--) {
        if (s1[j - 1] != s2[j - 1]) {
            return (j);
        }
    }
    return (0);
}

// Searches for a pattern in a text using Boyer-Moore-Horspool algorithm.
static const char *bmh(const char *text, const char *pattern)
{
    const size_t RADIX = 256;            // Number of symbols in the alphabet.
    size_t skip[RADIX];                  // Skip table.
    size_t textlen = strlen(text);       // Length of the input text.
    size_t patternlen = strlen(pattern); // Length of the search pattern.

    // Build skip table.
    for (size_t i = 0; i < RADIX; i++) {
        skip[i] = patternlen;
    }
    for (size_t i = 0; i < patternlen - 1; i++) {
        skip[(size_t)pattern[i]] = patternlen - i - 1;
    }

    // Slide a matching window through the input text.
    for (size_t i = 0; i <= (textlen - patternlen); /* */) {
        size_t j = match(&text[i], pattern, patternlen);

        // Match found.
        if (j == 0) {
            return (&text[i]);
        }

        // Slide matching window.
        i += skip[(size_t)text[i + patternlen - 1]];
    }

    // Match not found.
    return (NULL);
}

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
        printf("Search: pattern = \'%s\', text length = %zu\n", pattern, strlen(text));
    }

    // Search string.
    tstart = clock();
    result = bmh(text, pattern);
    tend = clock();

    // Report time.
    printf("bmh: %2.lf us\n", (tend - tstart) / MICROSECS);

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
    printf("%s - Testing program for bmh.\n", argv[0]);
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
