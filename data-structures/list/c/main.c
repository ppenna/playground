// Copyright (C) 2022 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Type of elements that are stored in the list.
typedef int type_t;

//==============================================================================
// Usage
//==============================================================================

// A singly linked list node.
struct node {
    type_t x;          // Element.
    struct node *next; // Next node.
};

// A singly linked list.
struct list {
    unsigned length;  // Number of elements in the list.
    struct node head; // Head node.
};

// Creates a linked list.
static struct list *list_create(void)
{
    struct list *list = NULL;

    // Allocate resources.
    assert((list = malloc(sizeof(struct list))) != NULL);

    // Initialize.
    list->length = 0;
    list->head.next = NULL;

    return (list);
}

// Destroys a linked list.
static void list_destroy(struct list *list)
{
    free(list);
}

// Returns the head node of a list.
static struct node *list_head(const struct list *list)
{
    return ((struct node *)&list->head);
}

// Returns the first node in a list.
static struct node *list_first(const struct list *list)
{
    return ((struct node *)list->head.next);
}

// Returns the next node in the list.
static struct node *list_next(const struct node *node)
{
    return ((struct node *)node->next);
}

// Inserts an element in the list.
static void list_insert_after(struct list *list, struct node *p, type_t x)
{
    struct node *new_node = NULL;

    // Create node.
    assert((new_node = malloc(sizeof(struct list))) != NULL);

    // Initialize.
    new_node->next = p->next;
    new_node->x = x;

    // Link node.
    p->next = new_node;
    list->length++;
}

// Removes an element from the list.
static type_t list_remove_next(struct list *list, struct node *p)
{
    type_t x;
    struct node *node = NULL;

    // Unlink node.
    node = p->next;
    p->next = node->next;
    list->length--;

    x = node->x;

    // Destroy node.
    free(node);

    return (x);
}

// Prints the contents of a list.
static void list_print(const struct list *l)
{
    printf("list { ");
    printf("length: %d, ", l->length);
    printf("elements: [");
    for (struct node *w = list_first(l); w != NULL; w = list_next(w)) {
        printf("%d%s", w->x, (list_next(w) == NULL) ? "" : ", ");
    }
    printf("] }\n");
}

//==============================================================================
// Usage
//==============================================================================

// Test driver for the linked list data structure.
static void test(unsigned length, bool verbose)
{
    struct list *l;
    double tstart = 0.0;
    double tend = 0.0;
    const double MICROSECS = ((CLOCKS_PER_SEC / 1000000.0));

    printf("running with length %d...\n", length);

    l = list_create();

    // Insert element sin the list.
    tstart = clock();
    for (unsigned i = 0; i < length; i++) {
        list_insert_after(l, list_head(l), (type_t)i);
    }
    tend = clock();
    printf("%12s: %2.lf us\n", "insert", (tend - tstart) / MICROSECS);
    if (verbose) {
        list_print(l);
    }

    // Traverse the list.
    tstart = clock();
    for (struct node *w = list_head(l); w != NULL; w = list_next(w)) {
        /* noop */;
    }
    tend = clock();
    printf("%12s: %2.lf us\n", "traverse", (tend - tstart) / MICROSECS);

    // Remove elements from the list.
    tstart = clock();
    for (unsigned i = 0; i < length; i++) {
        type_t x = list_remove_next(l, list_head(l));
        assert(x == (type_t)(length - i - 1));
    }
    tend = clock();
    printf("%12s: %2.lf us\n", "remove:", (tend - tstart) / MICROSECS);
    if (verbose) {
        list_print(l);
    }

    list_destroy(l);
}

//==============================================================================
// Usage
//==============================================================================

// Prints program usage and exits.
static void usage(char *const argv[])
{
    printf("%s - Testing program for linked lists.\n", argv[0]);
    printf("Usage: %s [--verbose] <list length>\n", argv[0]);
    exit(EXIT_FAILURE);
}

//==============================================================================
// Main
//==============================================================================

// Testing program for linked lists.
int main(int argc, char *const argv[])
{
    unsigned length = 0;
    bool verbose = false;

    // Check for missing arguments.
    if ((argc < 2) || (argc > 3)) {
        printf("Error: invalid number of arguments.\n");
        usage(argv);
    }

    // Parse command line arguments.
    if (argc == 2) {
        sscanf(argv[1], "%u", &length);
    } else if ((argc == 3) && (!strcmp(argv[1], "--verbose"))) {
        sscanf(argv[2], "%u", &length);
        verbose = true;
    } else {
        printf("Error: invalid arguments.\n");
        usage(argv);
    }

    // Run it!
    test(length, verbose);

    return (EXIT_SUCCESS);
}
