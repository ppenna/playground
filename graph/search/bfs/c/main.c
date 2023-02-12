
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
// Queue Data Structure
//==============================================================================

// A static circular queue.
struct queue {
    size_t *elements; // Elements stored in the queue.
    size_t length;    // Current number of elements that are stored in the queue.
    size_t capacity;  // Max number of elements that can be stored in the queue.
    size_t front;     // Indexes front element in the queue.
    size_t back;      // Indexes back position in the queue.
};

// Creates a new queue.
static struct queue *queue_create(size_t capacity)
{
    struct queue *q = NULL;
    assert((q = malloc(sizeof(struct queue))) != NULL);

    // Initialize data structure.
    q->length = 0;
    q->front = 0;
    q->back = 0;
    q->capacity = capacity + 1;
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

// Returns the number of elements that are stored in a queue.
static size_t queue_length(const struct queue *q)
{
    return (q->length);
}

// Inserts an element at the end of a queue.
static void queue_push_back(struct queue *q, size_t element)
{
    // The queue is full, thus expand its capacity.
    assert(q->length < (q->capacity - 1));

    // Insert element.
    q->elements[q->back] = element;
    q->back = (q->back + 1) % q->capacity;

    // Increase the length of the queue.
    q->length += 1;
}

// Removes the first element of a queue.
static size_t queue_pop_front(struct queue *q)
{
    // Empty queue.
    assert(q->length != 0);

    // Remove element.
    type_t x = q->elements[q->front];
    q->front = (q->front + 1) % q->capacity;

    // Decrease the length of the queue.
    q->length -= 1;

    return (x);
}

//==============================================================================
// Breadth-First Search
//==============================================================================

// Performs a breadth-first search in a graph.
static size_t bfs(const struct graph *g, size_t source, size_t *path)
{
    size_t path_length = 0;
    struct queue *q = NULL;
    bool visited[g->nnodes];

    assert((q = queue_create(g->nnodes)) != NULL);

    // Initial set all nodes as not vised.
    for (size_t i = 0; i < g->nnodes; i++) {
        visited[i] = false;
    }

    // Push source node.
    queue_push_back(q, source);
    visited[source] = true;

    // Process all nodes that in the queue.
    while (queue_length(q) != 0) {
        size_t i = queue_pop_front(q);

        // Add this node to the path.
        path[path_length++] = i;

        // Enqueue all non-visited neighbor nodes.
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

            // Enqueue this node for later
            // processing and mark it as visited.
            queue_push_back(q, j);
            visited[j] = true;
        }
    }

    // Release resources.
    queue_destroy(q);

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
    path_length = bfs(g, 0, path);
    tend = clock();

    // Report time.
    printf("Breadth-First Search: %2.lf us\n", (tend - tstart) / MICROSECS);

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
    printf("%s - Testing program for breadth-first search.\n", argv[0]);
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
