// Copyright (C) 2023 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Type of elements that are stored in the array.
typedef int type_t;

// Sorts an array using Shell Sort.
static void shell_sort(type_t array[], size_t length)
{
    size_t gap = 1;

    // Find initial gap in Knuth's Sequence (3^k - 1)/2.
    while (gap < length) {
        gap = 3 * gap + 1;
    }

    // Perform gapped insertion sort using Knuth's sequence.
    while (gap > 0) {
        // Run gapped insertion sort.
        for (size_t i = gap; i < length; i += gap) {
            size_t j = i;
            type_t tmp = array[i];

            // Shift right elements while searching for insertion point.
            while ((j >= gap) && (tmp < array[j - gap])) {
                array[j] = array[j - gap];
                j -= gap;
            }

            array[j] = tmp;
        }

        // Next gap in Knuth's sequence.
        gap /= 3;
    }
}

// Prints an array.
static void print_array(const type_t array[], size_t length)
{
    printf("[ ");
    for (size_t i = 0; i < length; i++) {
        printf("%d%s", array[i], ((i + 1) == length) ? " ]" : " ");
    }
    printf("\n");
}

// Initializes an array.
static void initialize_array(type_t array[], size_t length)
{
    for (size_t i = 0; i < length; i++) {
        array[i] = (type_t)(rand() % length);
    }
}

// Checks if an array is sorted.
static bool is_sorted(const type_t array[], size_t length)
{
    for (size_t i = 1; i < length; i++) {
        if (array[i] < array[i - 1]) {
            return (false);
        }
    }
    return (true);
}

// Tests Shell Sort.
static void test(size_t length, bool verbose)
{
    double tstart = 0.0;
    double tend = 0.0;
    type_t *array = NULL;
    const double MICROSECS = ((CLOCKS_PER_SEC / 1000000.0));

    // Fix random number generator seed
    // to have a determinist behavior across runs.
    srand(0);

    // Allocate an initialize array.
    array = malloc(length * sizeof(type_t));
    assert(array != NULL);
    initialize_array(array, length);

    if (verbose) {
        printf("Input: ");
        print_array(array, length);
    }

    // Sort array.
    tstart = clock();
    shell_sort(array, length);
    tend = clock();

    // Report time.
    printf("Shell Sort: %2.lf us\n", (tend - tstart) / MICROSECS);

    if (verbose) {
        printf("Output: ");
        print_array(array, length);
    }

    // Check if array is sorted.
    assert(is_sorted(array, length));

    // Release array.
    free(array);
}

// Prints program usage and exits.
static void usage(char *const argv[])
{
    printf("%s - Testing program for shell sort.\n", argv[0]);
    printf("Usage: %s [--verbose] <array length>\n", argv[0]);
    exit(EXIT_FAILURE);
}

// Drives the test function.
int main(int argc, char *const argv[])
{
    size_t length = 0;
    bool verbose = false;

    // Check for missing arguments.
    if ((argc < 2) || (argc > 3)) {
        printf("Error: invalid number of arguments.\n");
        usage(argv);
    }

    // Parse command line arguments.
    if (argc == 2) {
        sscanf(argv[1], "%zu", &length);
    } else if ((argc == 3) && (!strcmp(argv[1], "--verbose"))) {
        sscanf(argv[2], "%zu", &length);
        verbose = true;
    } else {
        printf("Error: invalid arguments.\n");
        usage(argv);
    }

    // Run it!
    test(length, verbose);

    return (EXIT_SUCCESS);
}
