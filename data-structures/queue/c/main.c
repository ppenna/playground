// Copyright (C) 2022 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Initial capacity for a queue.
#define QUEUE_CAPACITY 1024

// Type of elements that are stored in the queue.
typedef int type_t;

// A queue that can grow dynamically
struct queue {
    type_t *elements; // Elements stored in the queue.
    size_t length;    // Current number of elements that are stored in the queue.
    size_t capacity;  // Max number of elements that can be stored in the queue.
    size_t front;     // Indexes front element in the queue.
    size_t back;      // Indexes back position in the queue.
};

// Creates a new queue.
static struct queue *queue_create(size_t capacity)
{
    struct queue *q = malloc(sizeof(struct queue));
    assert(q != NULL);

    // Initialize data structure.
    q->length = 0;
    q->front = 0;
    q->back = 0;
    q->capacity = capacity;
    q->elements = malloc(q->capacity * sizeof(q->elements[0]));
    assert(q->elements != NULL);

    return (q);
}

// Destroys a queue.
static void queue_destroy(struct queue *q)
{
    free(q->elements);
    free(q);
}

// Expands the capacity of a queue.
static void queue_expand(struct queue *q)
{
    q->capacity *= 2;
    q->elements = realloc(q->elements, q->capacity * sizeof(q->elements[0]));
    assert(q != NULL);
}

// Returns the number of elements that are stored in a queue.
static size_t queue_length(const struct queue *q)
{
    return (q->length);
}

// Inserts an element at the end of a queue.
static void queue_push_back(struct queue *q, type_t element)
{
    // The queue is full, thus expand its capacity.
    if (q->length == (q->capacity - 1)) {
        queue_expand(q);
    }

    // Insert element.
    q->elements[q->back] = element;
    q->back = (q->back + 1) % q->capacity;

    // Increase the length of the queue.
    q->length += 1;
}

// Removes the first element of a queue.
static type_t queue_pop_front(struct queue *q)
{
    // Empty queue.
    if (q->length == 0) {
        fprintf(stderr, "Error: the queue is empty\n");
        exit(-1);
    }

    // Remove element.
    type_t x = q->elements[q->front];
    q->front = (q->front + 1) % q->capacity;

    // Decrease the length of the queue.
    q->length -= 1;

    return (x);
}

// Prints the contents of a queue.
static void queue_print(const struct queue *q)
{
    printf("queue { ");
    printf("capacity: %d, ", q->capacity);
    printf("length: %d, ", q->length);
    printf("elements: [");
    for (size_t i = 0; i < q->length; i++) {
        printf("%d%s", q->elements[i], ((i + 1) == q->length) ? "" : ", ");
    }
    printf("] }\n");
}

// Tests Queues.
static void test(size_t length, bool verbose)
{
    double tstart = 0.0;
    double tend = 0.0;
    const double MICROSECS = ((CLOCKS_PER_SEC / 1000000.0));
    struct queue *q = queue_create(QUEUE_CAPACITY);

    assert(queue_length(q) == 0);

    // Inserts elements in the queue.
    tstart = clock();
    for (size_t i = 0; i < length; i++) {
        queue_push_back(q, (type_t)(i + 1));
    }
    tend = clock();
    if (verbose) {
        queue_print(q);
    }
    printf("%12s: %2.lf us\n", "queue_push_back()", (tend - tstart) / MICROSECS);

    assert(queue_length(q) == length);

    // Remove all elements from the queue.
    for (size_t i = 0; i < length; i++) {
        assert(queue_pop_front(q) == (type_t)(i + 1));
    }
    if (verbose) {
        queue_print(q);
    }
    printf("%12s: %2.lf us\n", "queue_pop_front()", (tend - tstart) / MICROSECS);

    assert(queue_length(q) == 0);

    // Release queue.
    queue_destroy(q);
}

// Prints program usage and exits.
static void usage(char *const argv[])
{
    printf("%s - Testing program for queues .\n", argv[0]);
    printf("Usage: %s [--verbose] <queue length>\n", argv[0]);
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
