// Copyright (C) 2022 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//==============================================================================
// Graph Data Structure
//==============================================================================

// Type of elements that are stored in the graph.
typedef int type_t;

// A graph node.
struct node {
    type_t element; // Element.
};

// A graph link.
struct link {
    unsigned weight; // Weight.
};

// A graph.
struct graph {
    size_t nnodes;      // Number of nodes.
    struct node *nodes; // Nodes.
    struct link *links; // Adjacency matrix.
};

// Returns the link between two nodes in a graph.
static struct link *graph_link(const struct graph *g, size_t i, size_t j)
{
    return (&g->links[i * g->nnodes + j]);
}

// Creates a graph.
static struct graph *graph_create(size_t nnodes)
{
    struct graph *g = NULL;

    // Allocate data structure.
    assert((g = malloc(sizeof(struct graph))) != NULL);
    g->nnodes = nnodes;
    assert((g->nodes = malloc(g->nnodes * sizeof(struct node))) != NULL);
    assert((g->links = malloc(g->nnodes * g->nnodes * sizeof(struct link))) != NULL);

    // Initialize data structure.
    for (size_t i = 0; i < g->nnodes; i++) {
        for (size_t j = 0; j < g->nnodes; j++) {
            struct link *l = graph_link(g, i, j);
            l->weight = 0;
        }
    }

    return (g);
}

// Destroys a graph.
static void graph_destroy(struct graph *g)
{
    free(g->links);
    free(g->nodes);
    free(g);
}

// Prints a graph.
static void graph_print(const struct graph *g, FILE *f)
{
    size_t precision = 1;
    for (size_t i = 1; i < g->nnodes; i *= 10) {
        precision += 1;
    }
    fprintf(f, "graph {\n");
    fprintf(f, "nnodes: %d,\n", g->nnodes);
    fprintf(f, "links: \n");
    for (size_t i = 0; i < g->nnodes; i++) {
        fprintf(f, " [ ");
        for (size_t j = 0; j < g->nnodes; j++) {
            const struct link *l = graph_link(g, i, j);
            fprintf(f, "%*u ", precision, l->weight);
        }
        fprintf(f, "]\n");
    }
    fprintf(f, "}\n");
}

//==============================================================================
// Binary Heap Structure
//==============================================================================

// Swaps two elements.
static void swap(size_t *x, size_t *y)
{
    size_t tmp = *x;
    *x = *y;
    *y = tmp;
}

// A heap that can grow dynamically.
struct heap {
    size_t *elements;   // Elements stored in the heap.
    size_t *priorities; // Priorities of elements stored in the heap.
    size_t length;      // Current number of elements that are stored in the heap.
    size_t capacity;    // Max number of elements that can be stored in the heap.
};

// Creates an empty heap.
static struct heap *heap_create(size_t capacity)
{
    struct heap *h = malloc(sizeof(struct heap));
    assert(h != NULL);

    // Initialize data structure.
    h->length = 0;
    h->capacity = capacity;
    assert((h->priorities = malloc(h->capacity * sizeof(h->priorities[0]))) != NULL);
    assert((h->elements = malloc(h->capacity * sizeof(h->elements[0]))) != NULL);

    return (h);
}

// Destroys a heap.
static void heap_destroy(struct heap *h)
{
    free(h->elements);
    free(h->priorities);
    free(h);
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

        if (h->priorities[root] <= h->priorities[node]) {
            break;
        }

        // Swap elements.
        swap(&h->priorities[root], &h->priorities[node]);
        swap(&h->elements[root], &h->elements[node]);
        node = root;
    }
}

// Inserts an element in a heap.
static void heap_push(struct heap *h, size_t element, size_t priority)
{
    // The heap should not be full.
    assert(h->length < h->capacity);

    // Increase the size of the heap.
    h->length += 1;

    // Insert element;
    h->elements[h->length - 1] = element;
    h->priorities[h->length - 1] = priority;
    if (h->length > 1) {
        heap_fix_up(h, h->length - 1);
    }
}

// Fixes the heap property after a deletion on a heap.
static void heap_fix_down(struct heap *h, size_t root)
{
    // Traverse the heap from top to bottom.
    do {
        size_t smallest = root;
        size_t left = 2 * root + 1;
        size_t right = 2 * root + 2;

        // Done: reached leaf node.
        if (left >= h->length) {
            break;
        }

        // Check if left element is largest than the root.
        if (h->priorities[left] < h->priorities[smallest]) {
            smallest = left;
        }

        // Check if right element is largest than the root.
        if ((right < h->length) && (h->priorities[right] < h->priorities[smallest])) {
            smallest = right;
        }

        // Done: heap property is fixed.
        if (smallest == root) {
            break;
        }

        // Swap elements and advance root.
        swap(&h->priorities[root], &h->priorities[smallest]);
        swap(&h->elements[root], &h->elements[smallest]);
        root = smallest;
    } while (true);
}

// Removes an element from a heap.
static size_t heap_pop(struct heap *h)
{
    // Empty heap.
    if (h->length == 0) {
        fprintf(stderr, "Error: cannot pop() an empty heap\n");
        exit(-1);
    }

    size_t x = h->elements[0];

    // Remove element.
    swap(&h->priorities[0], &h->priorities[h->length - 1]);
    swap(&h->elements[0], &h->elements[h->length - 1]);
    h->length -= 1;
    if (h->length > 1) {
        heap_fix_down(h, 0);
    }

    return (x);
}

// Decreases the priority of an element in a heap.
static size_t heap_increase_priority(struct heap *h, size_t element, size_t new_priority)
{
    size_t i = 0;
    size_t old_priority = 0;

    // Empty heap.
    assert(h->length > 0);

    // Search for element.
    for (i = 0; i < h->length; i++) {
        // Found
        if (h->elements[i] == element) {
            assert(h->priorities[i] > new_priority);
            old_priority = h->priorities[i];
            h->priorities[i] = new_priority;
            heap_fix_up(h, i);
            return (old_priority);
        }
    }

    // Should not happen.
    printf("not found %zu\n", element);
    assert(0);

    return (-1);
}

//==============================================================================
// Prim's Algorithm
//==============================================================================

// Performs a Prim's Algorithm in a graph.
static void prim(const struct graph *g, size_t src, struct graph *t)
{
    struct heap *h = NULL;
    size_t from[g->nnodes];
    size_t cost[g->nnodes];

    assert((h = heap_create(g->nnodes)) != NULL);

    // Push initial nodes.
    cost[src] = 0;
    for (size_t i = 0; i < g->nnodes; i++) {
        if (i != src) {
            struct link *l = graph_link(g, src, i);
            // This node is a neighbor.
            if (l->weight > 0) {
                from[i] = src, cost[i] = l->weight;
                heap_push(h, i, cost[i]);
            }
            // This node is not a neighbor.
            else {
                from[i] = g->nnodes, cost[i] = (size_t)(-1);
            }
        }
    }

    // Process all nodes that in the graph.
    while (heap_length(h) != 0) {
        size_t i = heap_pop(h);

        // Add edge to minimum spanning-tree.
        struct link *l1 = graph_link(g, from[i], i);
        struct link *l2 = graph_link(t, from[i], i);
        l2->weight = l1->weight;

        // Process all neighbor nodes.
        for (size_t j = 0; j < g->nnodes; j++) {
            struct link *l = graph_link(g, i, j);

            // This is a neighbor.
            if (l->weight > 0) {
                size_t new_cost = l->weight;

                // This node was visited previously.
                if (from[j] < g->nnodes) {
                    // Update cost.
                    if (new_cost < cost[j]) {
                        from[j] = i, cost[j] = new_cost;
                        heap_increase_priority(h, j, new_cost);
                    }
                }
                // This is the first time we visit this node.
                else {
                    from[j] = i, cost[j] = new_cost;
                    heap_push(h, j, new_cost);
                }
            }
        }
    }

    // Release resources.
    heap_destroy(h);
}

//==============================================================================
// Test
//==============================================================================

// Tests Prim's Algorithm.
static void test(size_t nnodes, bool verbose)
{
    const float p = 0.55;
    const unsigned MAX_WEIGTH = (unsigned)nnodes;
    size_t source = 0;
    size_t dest = nnodes - 1;
    double tstart = 0.0;
    double tend = 0.0;
    const double MICROSECS = ((CLOCKS_PER_SEC / 1000000.0));
    struct graph *g = graph_create(nnodes);
    struct graph *t = graph_create(nnodes);

    // Fix random number generator seed
    // to have a determinist behavior across runs.
    srand(0);

    // Initialize the graph.
    for (size_t i = 0; i < g->nnodes; i++) {
        for (size_t j = 0; j < g->nnodes; j++) {
            float q = (rand() % 100) / 100.0;
            if (q < p) {
                unsigned w = nnodes + (rand() % MAX_WEIGTH);
                struct link *l = graph_link(g, i, j);
                l->weight = w;
            }
        }
    }
    assert(source < dest);
    for (size_t i = source; i < dest; i++) {
        struct link *l = graph_link(g, i, i + 1);
        l->weight = 1;
    }

    if (verbose) {
        graph_print(g, stdout);
    }

    // Search in the array.
    tstart = clock();
    prim(g, source, t);
    tend = clock();

    // Report time.
    printf("Prim's Algorithm: %2.lf us\n", (tend - tstart) / MICROSECS);

    if (verbose) {
        graph_print(t, stdout);
    }

    // Release resources.
    graph_destroy(t);
    graph_destroy(g);
}

//==============================================================================
// Usage
//==============================================================================

// Prints program usage and exits.
static void usage(char *const argv[])
{
    printf("%s - Testing program for Prim's Algorithm.\n", argv[0]);
    printf("Usage: %s [--verbose] <>\num_nodes n", argv[0]);
    exit(EXIT_FAILURE);
}

//==============================================================================
// Main
//==============================================================================

// Drives the test function.
int main(int argc, char *const argv[])
{
    size_t nnodes = 0;
    bool verbose = false;

    // Check for missing arguments.
    if ((argc < 2) || (argc > 3)) {
        printf("Error: invalid number of arguments.\n");
        usage(argv);
    }

    // Parse command line arguments.
    if (argc == 2) {
        sscanf(argv[1], "%zu", &nnodes);
    } else if ((argc == 3) && (!strcmp(argv[1], "--verbose"))) {
        sscanf(argv[2], "%zu", &nnodes);
        verbose = true;
    } else {
        printf("Error: invalid arguments.\n");
        usage(argv);
    }

    // Run it!
    test(nnodes, verbose);

    return (EXIT_SUCCESS);
}
