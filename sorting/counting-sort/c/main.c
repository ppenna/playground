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

// Type for element keys.
typedef type_t key_t;

// Retrieves the key associated to an element.
static key_t key(const type_t *x)
{
    return ((key_t)(*x));
}

// Sorts an array using Counting Sort.
static void counting_sort(type_t array[], size_t length)
{
    type_t *aux = NULL;
    size_t *count = NULL;
    size_t countlen = 1;
    key_t max = key(&array[0]);

    // Allocate auxiliary array to
    // store sorted elements temporarily.
    aux = malloc(length * sizeof(*array));
    assert(aux != NULL);

    // Find the largest key in the input array.
    for (size_t i = 1; i < length; i++) {
        if (max < key(&array[i])) {
            max = key(&array[i]);
        }
    }

    // Allocate and initialize count array with an increased
    // length by 1 to enable us to count zero frequencies as well.
    countlen = (size_t)(max + 1);
    count = malloc(countlen * sizeof(*count));
    assert(count != NULL);
    for (size_t i = 0; i < countlen; i++) {
        count[i] = 0;
    }

    // Count frequency of keys.
    for (size_t i = 0; i < length; i++) {
        key_t k = key(&array[i]);
        count[k] += 1;
    }

    // Compute prefix sum.
    for (size_t i = 1; i < countlen; i++) {
        count[i] += count[i - 1];
    }

    // Sort by performing lookups in the prefix sum table.
    // Note that we traverse the input array in reverse
    // order to ensure a stable sort.
    for (size_t i = length; i > 0; i--) {
        key_t k = key(&array[i - 1]);
        count[k] -= 1;
        aux[count[k]] = array[i - 1];
    }

    // Reconstruct original array.
    for (size_t i = 0; i < length; i++) {
        array[i] = aux[i];
    }

    // Release auxiliary data structures.
    free(count);
    free(aux);
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

// Tests Counting Sort.
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
    counting_sort(array, length);
    tend = clock();

    // Report time.
    printf("Counting Sort: %2.lf us\n", (tend - tstart) / MICROSECS);

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
    printf("%s - Testing program for counting sort.\n", argv[0]);
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
