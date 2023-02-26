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
// Stack Data Structure
//==============================================================================

// A stack that can grow dynamically.
struct stack {
    size_t *elements; // Elements stored in the stack.
    size_t length;    // Current number of elements that are stored in the stack.
    size_t capacity;  // Max number of elements that can be stored in the stack.
};

// Creates a new stack.
static struct stack *stack_create(size_t capacity)
{
    struct stack *s = malloc(sizeof(struct stack));
    assert(s != NULL);

    // Initialize data structure.
    s->length = 0;
    s->capacity = capacity;
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
static const size_t *stack_top(const struct stack *s)
{
    // Empty stack.
    if (s->length == 0) {
        fprintf(stderr, "Error: cannot top() an empty stack\n");
        exit(-1);
    }

    return (&s->elements[s->length - 1]);
}

// Gets a pointer to the top element of a stack.
static size_t *stack_top_mut(struct stack *s)
{
    // Empty stack.
    if (s->length == 0) {
        fprintf(stderr, "Error: cannot top_mut() an empty stack\n");
        exit(-1);
    }

    return (&s->elements[s->length - 1]);
}

// Inserts an element in a stack.
static void stack_push(struct stack *s, size_t element)
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
static size_t stack_pop(struct stack *s)
{
    // Empty stack.
    if (s->length == 0) {
        fprintf(stderr, "Error: cannot pop() an empty stack\n");
        exit(-1);
    }

    // Remove element.
    size_t x = *stack_top(s);

    // Decrease the size of the stack.
    s->length -= 1;

    return (x);
}

//==============================================================================
// Depth-First Search
//==============================================================================

// Performs a depth-first search in a graph.
static size_t dfs(const struct graph *g, size_t source, size_t *path)
{
    size_t path_length = 0;
    struct stack *q = NULL;
    bool visited[g->nnodes];

    assert((q = stack_create(g->nnodes)) != NULL);

    // Initial set all nodes as not vised.
    for (size_t i = 0; i < g->nnodes; i++) {
        visited[i] = false;
    }

    // Push source node.
    stack_push(q, source);
    visited[source] = true;

    // Process all nodes that in the stack.
    while (stack_length(q) != 0) {
        size_t i = stack_pop(q);

        // Add this node to the path.
        path[path_length++] = i;

        // Push all non-visited neighbor nodes.
        for (size_t j = 0; j < g->nnodes; j++) {
            struct link *l = graph_link(g, i, j);

            // This is not a neighbor.
            if (l->weight == 0) {
                continue;
            }

            // This neighbor was visited.
            if (visited[j]) {
                continue;
            }

            // Push this node for later
            // processing and mark it as visited.
            stack_push(q, j);
            visited[j] = true;
        }
    }

    // Release resources.
    stack_destroy(q);

    return (path_length);
}

//==============================================================================
// Test
//==============================================================================

// Tests Binary Search.
static void test(size_t nnodes, bool verbose)
{
    const float p = 0.65;
    const unsigned MAX_WEIGTH = (unsigned)nnodes;
    size_t path_length = 0;
    size_t path[nnodes];
    double tstart = 0.0;
    double tend = 0.0;
    const double MICROSECS = ((CLOCKS_PER_SEC / 1000000.0));
    struct graph *g = graph_create(nnodes);

    // Fix random number generator seed
    // to have a determinist behavior across runs.
    srand(0);

    // Initialize the graph.
    for (size_t i = 0; i < g->nnodes; i++) {
        for (size_t j = 0; j < g->nnodes; j++) {
            float q = (rand() % 100) / 100.0;
            if (q < p) {
                unsigned w = rand() % MAX_WEIGTH;
                struct link *l = graph_link(g, i, j);
                l->weight = w;
            }
        }
    }

    if (verbose) {
        graph_print(g, stdout);
    }

    // Search in the array.
    tstart = clock();
    path_length = dfs(g, 0, path);
    tend = clock();

    // Report time.
    printf("Depth-First Search: %2.lf us\n", (tend - tstart) / MICROSECS);

    if (verbose) {
        for (size_t i = 0; i < path_length; i++) {
            printf("%zu -> ", path[i]);
        }
        printf("NULL\n");
    }

    // Release graph.
    graph_destroy(g);
}

//==============================================================================
// Usage
//==============================================================================

// Prints program usage and exits.
static void usage(char *const argv[])
{
    printf("%s - Testing program for depth-first search.\n", argv[0]);
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
