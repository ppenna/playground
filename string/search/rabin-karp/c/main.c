// Copyright (C) 2023 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const unsigned BASE = 256;
const unsigned MOD = 101;

// A hash number.
typedef unsigned long long hash_t;

// Computes the hash value of a string.
static hash_t hash(const char *string, size_t length)
{
    hash_t h = 0;
    for (size_t i = 0; i < length; i++) {
        h = (h * BASE + string[i]) % MOD;
    }
    return h;
}

// Updates the hash value of a string.
static hash_t hash_update(hash_t h, char old, char new, const hash_t pow)
{
    return ((((h + MOD) - (old * pow) % MOD) * BASE) % MOD + new) % MOD;
}

// Searches for a pattern in a text using Rabin-Karp algorithm.
static size_t rabin_karp(const char *text, const char *pattern)
{
    size_t textlen = strlen(text);                   // Text length.
    size_t patternlen = strlen(pattern);             // Pattern length
    hash_t pattern_hash = hash(pattern, patternlen); // Hash value for pattern.
    hash_t text_hash = hash(text, patternlen);       // Hash value for text.
    fprintf(stdout, "text_hash=%llu pattern_hash=%llu\n", text_hash, pattern_hash);

    hash_t pow = 1;
    for (size_t i = 0; i < patternlen - 1; i++) {
        pow = (pow * BASE) % MOD;
    }

    // Slide a matching window through the input text.
    for (size_t i = 0; i <= (textlen - patternlen); i++) {

        // Hashes matched, thus check this string.
        if (text_hash == pattern_hash) {
            size_t j = 0;

            // Check all characters.
            for (j = 0; j < patternlen; j++) {
                // Mismatch.
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }

            // Matched.
            if (j == patternlen) {
                return (i);
            }
        }

        if (i <= (textlen - patternlen)) {
            text_hash = hash_update(text_hash, text[i], text[i + patternlen], pow);
        }
    }

    // Not found.
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
    result = rabin_karp(text, pattern);
    tend = clock();

    // Report time.
    printf("rabin-karp: %2.lf us\n", (tend - tstart) / MICROSECS);

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
    printf("%s - Testing program for rabin-karp.\n", argv[0]);
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
