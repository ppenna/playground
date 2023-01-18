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

// Swaps two elements in an array.
static void swap(type_t *x, type_t *y)
{
    type_t tmp = *x;
    *x = *y;
    *y = tmp;
}

// Finds a Quicksort partition.
static size_t partition(type_t array[], size_t left, size_t right)
{
    size_t i = left + 1;
    size_t j = right;
    type_t mid = left + (right - left) / 2;

    // Make the pivot element a sentinel.
    swap(&array[left], &array[mid]);

    // Find partition and swap elements that are out of order.
    while (true) {
        // Skip elements that are smaller than *or* equal the pivot.
        while ((i < right) && (array[i] <= array[left])) {
            i += 1;
        }

        // Skip elements that are *only* greater than the pivot.
        // Note that we don't need to perform a bound check here, because
        // At the leftmost position we placed the pivot element as sentinel.
        while (array[j] > array[left]) {
            j -= 1;
        }

        // Partition found.
        if (i >= j) {
            break;
        }

        // Swap elements.
        swap(&array[i], &array[j]);
    }

    // Place pivot element in its final position.
    swap(&array[left], &array[j]);

    return (j);
}

// Recursive Quicksort routine.
static void _quicksort(type_t array[], size_t left, size_t right)
{
    if (right > left) {
        size_t p = partition(array, left, right);

        // Overflow protection: recurse only if there is a left-hand partition.
        if (p > 0) {
            _quicksort(array, left, p - 1);
        }

        // There is always a right-hand partition.
        _quicksort(array, p + 1, right);
    }
}

// Sorts an array using Quicksort.
static void quicksort(type_t array[], size_t length)
{
    _quicksort(array, 0, length - 1);
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

// Tests Quicksort.
static void test(size_t length, bool verbose)
{
    double tstart = 0.0;
    double tend = 0.0;
    type_t *array = NULL;
    const double MICROSECS = ((CLOCKS_PER_SEC / 1000000.0));

    // Fix random number generator seed so that we have
    // a deterministic behavior across runs.
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
    quicksort(array, length);
    tend = clock();

    // Report time.
    printf("Quicksort: %2.lf us\n", (tend - tstart) / MICROSECS);

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
    printf("%s - Testing program for quicksort.\n", argv[0]);
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
