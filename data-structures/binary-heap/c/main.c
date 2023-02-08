// Copyright (C) 2022 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Initial capacity for a heap.
#define HEAP_CAPACITY 1024

// Type of elements that are stored in the heap.
typedef int type_t;

// Swaps two elements.
static void swap(type_t *x, type_t *y)
{
    type_t tmp = *x;
    *x = *y;
    *y = tmp;
}

// A heap that can grow dynamically.
struct heap {
    type_t *elements; // Elements stored in the heap.
    size_t length;    // Current number of elements that are stored in the heap.
    size_t capacity;  // Max number of elements that can be stored in the heap.
};

// Creates an empty heap.
static struct heap *heap_create(void)
{
    struct heap *h = malloc(sizeof(struct heap));
    assert(h != NULL);

    // Initialize data structure.
    h->length = 0;
    h->capacity = HEAP_CAPACITY;
    h->elements = malloc(h->capacity * sizeof(h->elements[0]));
    assert(h->elements != NULL);

    return (h);
}

// Destroys a heap.
static void heap_destroy(struct heap *h)
{
    free(h->elements);
    free(h);
}

// Expands the capacity of a heap.
static void heap_expand(struct heap *h)
{
    type_t *elements = NULL;
    h->capacity *= 2;
    elements = realloc(h->elements, h->capacity * sizeof(h->elements[0]));
    assert(elements != NULL);
    h->elements = elements;
}

// Returns the number of elements that are stored in a heap.
static size_t heap_length(const struct heap *h)
{
    return (h->length);
}

// Fixes the heap property after an insertion on a heap.
static void heap_fix_up(struct heap *h, size_t node)
{
    while (node > 0) {
        size_t root = (node - 1) / 2;

        if (h->elements[root] >= h->elements[node]) {
            break;
        }

        // Swap elements.
        swap(&h->elements[root], &h->elements[node]);
        node = root;
    }
}

// Inserts an element in a heap.
static void heap_push(struct heap *h, type_t element)
{
    // The heap is full, thus expand its capacity.
    if (h->length == h->capacity) {
        heap_expand(h);
    }

    // Increase the size of the heap.
    h->length += 1;

    // Insert element;
    h->elements[h->length - 1] = element;
    if (h->length > 1) {
        heap_fix_up(h, h->length - 1);
    }
}

// Fixes the heap property after a deletion on a heap.
static void heap_fix_down(struct heap *h, size_t root)
{
    // Traverse the heap from top to bottom.
    do {
        size_t largest = root;
        size_t left = 2 * root + 1;
        size_t right = 2 * root + 2;

        // Done: reached leaf node.
        if (left >= h->length) {
            break;
        }

        // Check if left element is largest than the root.
        if (h->elements[left] > h->elements[largest]) {
            largest = left;
        }

        // Check if right element is largest than the root.
        if ((right < h->length) && (h->elements[right] > h->elements[largest])) {
            largest = right;
        }

        // Done: heap property is fixed.
        if (largest == root) {
            break;
        }

        // Swap elements and advance root.
        swap(&h->elements[root], &h->elements[largest]);
        root = largest;
    } while (true);
}

// Removes an element from a heap.
static type_t heap_pop(struct heap *h)
{
    // Empty heap.
    if (h->length == 0) {
        fprintf(stderr, "Error: cannot pop() an empty heap\n");
        exit(-1);
    }

    type_t x = h->elements[0];

    // Remove element.
    swap(&h->elements[0], &h->elements[h->length - 1]);
    h->length -= 1;
    if (h->length > 1) {
        heap_fix_down(h, 0);
    }

    return (x);
}

// Prints the contents of a heap.
static void heap_print(const struct heap *h)
{
    printf("heap { ");
    printf("capacity: %d, ", h->capacity);
    printf("length: %d, ", h->length);
    printf("elements: [");
    for (size_t i = 0; i < h->length; i++) {
        printf("%d%s", h->elements[i], ((i + 1) == h->length) ? "" : ", ");
    }
    printf("] }\n");
}

// Tests the Heap implementation.
static void test(size_t length, bool verbose)
{
    double tstart = 0.0;
    double tend = 0.0;
    const double MICROSECS = ((CLOCKS_PER_SEC / 1000000.0));
    struct heap *h = heap_create();

    assert(heap_length(h) == 0);

    // Inserts elements in the heap.
    tstart = clock();
    for (size_t i = 0; i < length; i++) {
        heap_push(h, (type_t)(i + 1));
    }
    tend = clock();
    if (verbose) {
        heap_print(h);
    }
    printf("%12s: %2.lf us\n", "heap_push()", (tend - tstart) / MICROSECS);

    assert(heap_length(h) == length);

    // Remove all elements from the heap.
    for (size_t i = length; i > 0; i--) {
        assert(heap_pop(h) == (type_t)(i));
    }
    if (verbose) {
        heap_print(h);
    }
    printf("%12s: %2.lf us\n", "heap_pop()", (tend - tstart) / MICROSECS);

    assert(heap_length(h) == 0);

    // Release heap.
    heap_destroy(h);
}

// Prints program usage and exits.
static void usage(char *const argv[])
{
    printf("%s - Testing program for heaps.\n", argv[0]);
    printf("Usage: %s [--verbose] <heap length>\n", argv[0]);
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
