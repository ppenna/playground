// Copyright (C) 2022 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Initial capacity for a vector.
#define VECTOR_CAPACITY 1024

// Type of elements that are stored in the vector.
typedef int type_t;

// A dynamic array with bound checking.
struct vector {
    type_t *elements; // Elements stored in the vector.
    size_t length;    // Current number of elements that are stored in the vector.
    size_t capacity;  // Max number of elements that can be stored in the vector.
};

// Creates a new vector.
static struct vector *vector_create(void)
{
    struct vector *v = malloc(sizeof(struct vector));
    assert(v != NULL);

    // Initialize data structure.
    v->length = 0;
    v->capacity = VECTOR_CAPACITY;
    v->elements = malloc(v->capacity * sizeof(v->elements[0]));
    assert(v->elements != NULL);

    return (v);
}

// Destroys a vector.
static void vector_destroy(struct vector *v)
{
    free(v->elements);
    free(v);
}

// Expands the capacity of a vector.
static void vector_expand(struct vector *v)
{
    v->capacity *= 2;
    v->elements = realloc(v->elements, v->capacity * sizeof(v->elements[0]));
    assert(v != NULL);
}

// Returns the number of elements that are stored in a vector.
static size_t vector_length(const struct vector *v)
{
    return (v->length);
}

// Inserts an element in a specific position of a vector.
static void vector_insert(struct vector *v, size_t index, type_t element)
{
    // The vector is full, thus expand its capacity.
    if (vector_length(v) == v->capacity) {
        vector_expand(v);
    }

    // Increase the size of the vector.
    v->length += 1;

    // Shift right elements.
    for (size_t i = v->length - 1; i > index; i--) {
        v->elements[i] = v->elements[i - 1];
    }

    // Insert the element in the specified position.
    v->elements[index] = element;
}

// Removes an element from a specific position in a vector.
static type_t vector_remove(struct vector *v, size_t index)
{
    // Out of bounds.
    if (index >= v->length) {
        fprintf(stderr, "Error: %zu is out of bounds of the vector\n", index);
        exit(-1);
    }

    type_t x = v->elements[index];

    // Shift left elements.
    for (size_t i = index; i < v->length - 1; i++) {
        v->elements[i] = v->elements[i + 1];
    }

    // Decrease the size of the vector.
    v->length -= 1;

    return (x);
}

// Gets a read-only pointer to an element in a vector.
static const type_t *vector_index(const struct vector *v, size_t index)
{
    // Out of bounds.
    if (index >= v->length) {
        fprintf(stderr, "Error: %zu is out of bounds of the vector\n", index);
        exit(-1);
    }

    return (&v->elements[index]);
}

// Gets a pointer to an element in a vector.
static type_t *vector_index_mut(struct vector *v, size_t index)
{
    // Out of bounds.
    if (index >= v->length) {
        fprintf(stderr, "Error: %zu is out of bounds of the vector\n", index);
        exit(-1);
    }

    return (&v->elements[index]);
}

// Prints a vector.
static void vector_print(const struct vector *v)
{
    printf("vector { ");
    printf("capacity: %d, ", v->capacity);
    printf("length: %d, ", v->length);
    printf("elements: [");
    for (size_t i = 0; i < v->length; i++) {
        printf("%d%s", v->elements[i], ((i + 1) == v->length) ? "" : ", ");
    }
    printf("] }\n");
}

// Tests Vectors.
static void test(size_t length, bool verbose)
{
    double tstart = 0.0;
    double tend = 0.0;
    const double MICROSECS = ((CLOCKS_PER_SEC / 1000000.0));
    struct vector *v = vector_create();

    assert(vector_length(v) == 0);

    // Inserts elements in the vector.
    tstart = clock();
    for (size_t i = 0; i < length; i++) {
        type_t x = (type_t)(i + 1);
        vector_insert(v, i, x);
    }
    tend = clock();
    if (verbose) {
        vector_print(v);
    }
    printf("%18s: %2.lf us\n", "vector_insert()", (tend - tstart) / MICROSECS);

    assert(vector_length(v) == length);

    // Get all elements in the vector.
    for (size_t i = 0; i < length; i++) {
        assert(*vector_index(v, i) == (type_t)(i + 1));
    }
    if (verbose) {
        vector_print(v);
    }
    printf("%18s: %2.lf us\n", "vector_get()", (tend - tstart) / MICROSECS);

    // Replace all elements in the vector.
    for (size_t i = 0; i < length; i++) {
        *vector_index_mut(v, i) = 0;
    }
    if (verbose) {
        vector_print(v);
    }
    printf("%18s: %2.lf us\n", "vector_index_mut()", (tend - tstart) / MICROSECS);

    // Remove all elements from the vector.
    for (size_t i = 0; i < length; i++) {
        vector_remove(v, 0);
    }
    if (verbose) {
        vector_print(v);
    }
    printf("%18s: %2.lf us\n", "vector_remove()", (tend - tstart) / MICROSECS);

    assert(vector_length(v) == 0);

    // Release vector.
    vector_destroy(v);
}

// Prints program usage and exits.
static void usage(char *const argv[])
{
    printf("%s - Testing program for vectors .\n", argv[0]);
    printf("Usage: %s [--verbose] <vector length>\n", argv[0]);
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
