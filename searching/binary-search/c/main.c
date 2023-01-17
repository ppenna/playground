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

// Compares two elements.
static int cmp(const void *x, const void *y)
{
    return (*((const type_t *)x) - *((const type_t *)y));
}

// Searches for an element in a sorted array using Binary Search.
static size_t binary_search(const type_t array[], size_t length, type_t element)
{
    size_t low = 0;
    size_t high = length;

    while (low < high) {
        size_t mid = low + (high - low) / 2;

        // Found.
        if (array[mid] == element) {
            return mid;
        }

        // Search on the left sub-array.
        else if (element < array[mid]) {
            high = mid;
        }
        // Search on the right sub-array.
        else {
            low = mid + 1;
        }
    }

    // Not found.
    return ((size_t)-1);
}

// Initializes an array.
static void initialize_array(type_t array[], size_t length)
{
    for (size_t i = 0; i < length; i++) {
        array[i] = (type_t)(rand() % length);
    }
}

// Tests Binary Search.
static void test(size_t length, bool verbose)
{
    double tstart = 0.0;
    double tend = 0.0;
    type_t *array = NULL;
    const double MICROSECS = ((CLOCKS_PER_SEC / 1000000.0));
    size_t found_key = (size_t)-1;
    size_t search_key = 1;

    // Fix random number generator seed
    // to have a determinist behavior across runs.
    srand(0);

    // Allocate an initialize array.
    array = malloc(length * sizeof(type_t));
    assert(array != NULL);
    initialize_array(array, length);
    qsort(array, length, sizeof(type_t), cmp);

    // Pickup a key within the range.
    search_key = (size_t)rand() % length;

    if (verbose) {
        printf("Search: key = %d, value = %d\n", search_key, array[search_key]);
    }

    // Search in the array.
    tstart = clock();
    found_key = binary_search(array, length, array[search_key]);
    tend = clock();

    // Report time.
    printf("Binary Search: %2.lf us\n", (tend - tstart) / MICROSECS);

    // Check if we found the given key.
    assert(found_key != (size_t)-1);

    if (verbose) {
        printf("Output: %s\n", (found_key != (size_t)-1) ? "found" : "not found");
    }

    // Release array.
    free(array);
}

// Prints program usage and exits.
static void usage(char *const argv[])
{
    printf("%s - Testing program for binary search.\n", argv[0]);
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
