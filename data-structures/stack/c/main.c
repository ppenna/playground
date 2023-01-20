// Copyright (C) 2022 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Initial capacity for a stack.
#define STACK_CAPACITY 1024

// Type of elements that are stored in the stack.
typedef int type_t;

// A stack that can grow dynamically.
struct stack {
    type_t *elements; // Elements stored in the stack.
    size_t length;    // Current number of elements that are stored in the stack.
    size_t capacity;  // Max number of elements that can be stored in the stack.
};

// Creates a new stack.
static struct stack *stack_create(void)
{
    struct stack *s = malloc(sizeof(struct stack));
    assert(s != NULL);

    // Initialize data structure.
    s->length = 0;
    s->capacity = STACK_CAPACITY;
    s->elements = malloc(s->capacity * sizeof(s->elements[0]));
    assert(s->elements != NULL);

    return (s);
}

// Destroys a stack.
static void stack_destroy(struct stack *s)
{
    free(s->elements);
    free(s);
}

// Expands the capacity of a stack.
static void stack_expand(struct stack *s)
{
    s->capacity *= 2;
    s->elements = realloc(s->elements, s->capacity * sizeof(s->elements[0]));
    assert(s != NULL);
}

// Returns the number of elements that are stored in a stack.
static size_t stack_length(const struct stack *s)
{
    return (s->length);
}

// Gets a read-only pointer to the top element of a stack.
static const type_t *stack_top(const struct stack *s)
{
    // Empty stack.
    if (s->length == 0) {
        fprintf(stderr, "Error: cannot top() an empty stack\n");
        exit(-1);
    }

    return (&s->elements[s->length - 1]);
}

// Gets a pointer to the top element of a stack.
static type_t *stack_top_mut(struct stack *s)
{
    // Empty stack.
    if (s->length == 0) {
        fprintf(stderr, "Error: cannot top_mut() an empty stack\n");
        exit(-1);
    }

    return (&s->elements[s->length - 1]);
}

// Inserts an element in a stack.
static void stack_push(struct stack *s, type_t element)
{
    // The stack is full, thus expand its capacity.
    if (s->length == s->capacity) {
        stack_expand(s);
    }

    // Increase the size of the stack.
    s->length += 1;

    // Insert element.
    *stack_top_mut(s) = element;
}

// Removes an element from a stack.
static type_t stack_pop(struct stack *s)
{
    // Empty stack.
    if (s->length == 0) {
        fprintf(stderr, "Error: cannot pop() an empty stack\n");
        exit(-1);
    }

    // Remove element.
    type_t x = *stack_top(s);

    // Decrease the size of the stack.
    s->length -= 1;

    return (x);
}

// Prints the contents of a stack.
static void stack_print(const struct stack *s)
{
    printf("stack { ");
    printf("capacity: %d, ", s->capacity);
    printf("length: %d, ", s->length);
    printf("elements: [");
    for (size_t i = 0; i < s->length; i++) {
        printf("%d%s", s->elements[i], ((i + 1) == s->length) ? "" : ", ");
    }
    printf("] }\n");
}

// Tests Stacks.
static void test(size_t length, bool verbose)
{
    double tstart = 0.0;
    double tend = 0.0;
    const double MICROSECS = ((CLOCKS_PER_SEC / 1000000.0));
    struct stack *s = stack_create();

    assert(stack_length(s) == 0);

    // Inserts elements in the stack.
    tstart = clock();
    for (size_t i = 0; i < length; i++) {
        stack_push(s, (type_t)(i + 1));
    }
    tend = clock();
    if (verbose) {
        stack_print(s);
    }
    printf("%12s: %2.lf us\n", "stack_push()", (tend - tstart) / MICROSECS);

    assert(stack_length(s) == length);

    // Remove all elements from the stack.
    for (size_t i = length; i > 0; i--) {
        assert(stack_pop(s) == (type_t)(i));
    }
    if (verbose) {
        stack_print(s);
    }
    printf("%12s: %2.lf us\n", "stack_pop()", (tend - tstart) / MICROSECS);

    assert(stack_length(s) == 0);

    // Release stack.
    stack_destroy(s);
}

// Prints program usage and exits.
static void usage(char *const argv[])
{
    printf("%s - Testing program for stacks .\n", argv[0]);
    printf("Usage: %s [--verbose] <stack length>\n", argv[0]);
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
