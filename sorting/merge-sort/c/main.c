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

// Merges two arrays.
static void merge(type_t array[], type_t a[], size_t a_length, type_t b[], size_t b_length)
{
    size_t a_index = 0;
    size_t b_index = 0;

    // Merge two sorted arrays into a single one.
    for (size_t i = 0; i < (a_length + b_length); i++) {
        // There are remainder elements on both arrays to be considered.
        if ((a_index < a_length) && (b_index < b_length)) {
            if (a[a_index] < b[b_index]) {
                array[i] = a[a_index];
                a_index++;
            } else {
                array[i] = b[b_index];
                b_index++;
            }
        }
        // There are only elements on the first array to be merged in.
        else if ((a_index < a_length)) {
            array[i] = a[a_index];
            a_index++;
        }
        // There are only elements on the second array to be merged in.
        else {
            array[i] = b[b_index];
            b_index++;
        }
    }
}

// Sorts an array using a top-down recursive Merge Sort approach.
static void _merge_sort(type_t aux_array[], type_t array[], size_t length)
{
    // Single-element array: nothing to do.
    if (length <= 1) {
        return;
    }
    // Two-element array: swap elements if needed.
    else if (length == 2) {
        if (array[0] > array[1]) {
            swap(&array[0], &array[1]);
        }
    }
    // Large arrays: recurse.
    else {
        // Partition array.
        type_t *a = &array[0];
        size_t a_length = length / 2;
        type_t *b = &array[a_length];
        size_t b_length = length - a_length;

        // Sort each sub-array individually and merge result.
        _merge_sort(&aux_array[0], a, a_length);
        _merge_sort(&aux_array[a_length], b, b_length);
        merge(aux_array, a, a_length, b, b_length);
        memcpy(array, aux_array, length * sizeof(type_t));
    }
}

// Sorts an array using Merge Sort.
static void merge_sort(type_t array[], size_t length)
{
    type_t *aux_array = malloc(length * sizeof(type_t));
    assert(aux_array != NULL);

    _merge_sort(aux_array, array, length);

    // Release resources.
    free(aux_array);
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

// Tests Merge Sort.
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
    merge_sort(array, length);
    tend = clock();

    // Report time.
    printf("Merge Sort: %2.lf us\n", (tend - tstart) / MICROSECS);

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
    printf("%s - Testing program for merge sort.\n", argv[0]);
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
