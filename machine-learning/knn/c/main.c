// Copyright (C) 2022 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//==============================================================================
// Vector
//==============================================================================

// A vector.
struct vector {
    unsigned dimension; // Number of elements in the vector.
    double *elements;   // Elements.
};

// Creates a vector.
static struct vector *vector_create(unsigned dimension)
{
    // Sanity check arguments.
    assert(dimension > 0);

    struct vector *v = NULL;
    assert((v = malloc(sizeof(struct vector))) != NULL);
    assert((v->elements = malloc(dimension * sizeof(v->elements[0]))) != NULL);
    v->dimension = dimension;
    for (unsigned i = 0; i < dimension; i++) {
        v->elements[i] = 0.0;
    }
    return (v);
}

// Destroys the target vector.
static void vector_destroy(struct vector *v)
{
    // Sanity check arguments.
    assert(v != NULL);

    free(v->elements);
    free(v);
}

// Initializes a vector with random values.
static void vector_random(struct vector *v)
{
    // Sanity check arguments.
    assert(v != NULL);

    // Generate random elements.
    for (unsigned i = 0; i < v->dimension; i++) {
        v->elements[i] = rand() / (double)RAND_MAX;
    }
}

// Computes the squared euclidean distance between two vectors.
static double vector_distance2(const struct vector *v1, const struct vector *v2)
{
    // Sanity check arguments.
    assert(v1 != NULL);
    assert(v2 != NULL);
    assert(v1->dimension == v2->dimension);

    double distance = 0.0;

    // Compute the squared distance between each element
    for (unsigned i = 0; i < v1->dimension; i++) {
        double x = v1->elements[i] - v2->elements[i];
        distance += x * x;
    }

    return (distance);
}

// Prints a vector.
static void vector_print(const struct vector *v)
{
    printf("vector { ");
    printf("length: %d, ", v->dimension);
    printf("elements: [");
    for (unsigned i = 0; i < v->dimension; i++) {
        printf(
            "%.2lf%s", v->elements[i], ((i + 1) == v->dimension) ? "" : ", ");
    }
    printf("] }\n");
}

//==============================================================================
// K-Nearest Neighbors
//==============================================================================

// Sorts distances in ascending order.
static void sort_distances(double *distances,
                           unsigned *indexes,
                           unsigned npoints)
{
    for (unsigned i = 0; i < npoints; i++) {
        for (unsigned j = i + 1; j < npoints; j++) {
            if (distances[i] > distances[j]) {
                // Swap distances.
                double dst = distances[i];
                distances[i] = distances[j];
                distances[j] = dst;

                // Swap indexes.
                unsigned idx = indexes[i];
                indexes[i] = indexes[j];
                indexes[j] = idx;
            }
        }
    }
}

// K-Nearest Neighbors.
static void knn(struct vector **nearest,
                struct vector *const *points,
                unsigned npoints,
                unsigned k,
                const struct vector *query)
{
    // Distances.
    double distances[npoints];
    unsigned indexes[npoints];

    // Compute distances.
    for (unsigned i = 0; i < npoints; i++) {
        indexes[i] = i;
        distances[i] = vector_distance2(points[i], query);
    }

    // Sort distances.
    sort_distances(distances, indexes, npoints);

    /// Find K-nearest neighbors.
    for (unsigned i = 0; i < k; i++) {
        nearest[i] = points[indexes[i]];
    }
}

//==============================================================================
// Test
//==============================================================================

// Tests K-Nearest Neighbors.
static void test(unsigned npoints, unsigned dimension, bool verbose)
{
    double tstart = 0.0;
    double tend = 0.0;
    const double MICROSECS = ((CLOCKS_PER_SEC / 1000000.0));
    const unsigned K = 3;
    struct vector **points = NULL;
    struct vector *neighbors[K];

    // Fix random number generator seed
    // to have a determinist behavior across runs.
    srand(0);

    // Allocate points
    assert((points = malloc(npoints * sizeof(struct vector *))) != NULL);
    for (unsigned i = 0; i < npoints; i++) {
        points[i] = vector_create(dimension);
        vector_random(points[i]);
    }

    if (verbose) {
        printf("Data Set:\n");
        for (unsigned i = 1; i < npoints; i++) {
            vector_print(points[i]);
        }
        printf("Query:\n");
        vector_print(points[0]);
    }

    // Run.
    tstart = clock();
    knn(neighbors, &points[1], npoints - 1, K, points[0]);
    tend = clock();

    // Report time.
    printf("K-Nearest Neighbors: %2.lf us\n", (tend - tstart) / MICROSECS);

    if (verbose) {
        printf("Neighbors:\n");
        for (unsigned i = 0; i < K; i++) {
            vector_print(neighbors[i]);
        }
    }

    // Release resources.
    for (unsigned i = 0; i < npoints; i++) {
        vector_destroy(points[i]);
    }
    free(points);
}

//==============================================================================
// Usage
//==============================================================================

// Prints program usage and exits.
static void usage(char *const argv[])
{
    printf("%s - Testing program for k-nearest neighbors.\n", argv[0]);
    printf("Usage: %s [--verbose] <number of points> <dimension>\n", argv[0]);
    exit(EXIT_FAILURE);
}

//==============================================================================
// Main
//==============================================================================

// Drives the test function.
int main(int argc, char *const argv[])
{
    unsigned npoints = 0;
    unsigned dimension = 0;
    bool verbose = false;

    // Check for missing arguments.
    if ((argc < 3) || (argc > 4)) {
        printf("Error: invalid number of arguments.\n", argc);
        usage(argv);
    }

    // Parse command line arguments.
    if (argc == 3) {
        sscanf(argv[1], "%u", &npoints);
        sscanf(argv[2], "%u", &dimension);
    } else if ((argc == 4) && (!strcmp(argv[1], "--verbose"))) {
        sscanf(argv[2], "%u", &npoints);
        sscanf(argv[3], "%u", &dimension);
        verbose = true;
    } else {
        printf("Error: invalid arguments.\n");
        usage(argv);
    }

    // Run it!
    test(npoints, dimension, verbose);

    return (EXIT_SUCCESS);
}
