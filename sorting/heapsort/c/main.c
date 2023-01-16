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

// Fixes the max-heap property downwards.
static void fix_down(type_t array[], size_t length, size_t root)
{
    // Traverse the heap from top to bottom.
    do {
        size_t largest = root;
        size_t left = 2 * root + 1;
        size_t right = 2 * root + 2;

        // Done: reached leaf node.
        if (left >= length) {
            break;
        }

        // Check if left element is largest than the root.
        if (array[left] > array[largest]) {
            largest = left;
        }

        // Check if right element is largest than the root.
        if ((right < length) && (array[right] > array[largest])) {
            largest = right;
        }

        // Done: heap property is fixed.
        if (largest == root) {
            break;
        }

        // Swap elements and advance root.
        swap(&array[root], &array[largest]);
        root = largest;
    } while (true);
}

// Creates a heap from an array.
static void heapify(type_t array[], size_t length)
{
    for (size_t i = length / 2; i > 0; i--) {
        fix_down(array, length, i - 1);
    }
}

// Sorts an array using Heapsort.
static void heapsort(type_t array[], size_t length)
{
    // Build a max-heap.
    heapify(array, length);

    // Pop elements from the heap and place them at the end of the array.
    for (size_t i = length; i > 0; i--) {
        swap(&array[0], &array[i - 1]);
        fix_down(array, i - 1, 0);
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

// Tests Heapsort.
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
    heapsort(array, length);
    tend = clock();

    // Report time.
    printf("Heapsort: %2.lf us\n", (tend - tstart) / MICROSECS);

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
    printf("%s - Testing program for selection sort.\n", argv[0]);
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
