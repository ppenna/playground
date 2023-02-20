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

// Assign operator for vectors.
static void vector_assign(struct vector *v1, struct vector *v2)
{
    // Sanity check arguments.
    assert(v1 != NULL);
    assert(v2 != NULL);
    assert(v1->dimension == v2->dimension);

    // Assign elements.
    for (unsigned i = 0; i < v1->dimension; i++) {
        v1->elements[i] = v2->elements[i];
    }
}

// Computes the addition operation for two vectors.
static void vector_add(struct vector *v1, struct vector *v2)
{
    // Sanity check arguments.
    assert(v1 != NULL);
    assert(v2 != NULL);
    assert(v1->dimension == v2->dimension);

    for (unsigned i = 0; i < v1->dimension; i++) {
        v1->elements[i] += v2->elements[i];
    }
}

// Computes the scalar multiplication operation for two vectors.
static void vector_scale(struct vector *v, double scale)
{
    // Sanity check arguments.
    assert(v != NULL);

    for (unsigned i = 0; i < v->dimension; i++) {
        v->elements[i] *= scale;
    }
}

// Computes the squared euclidean distance between two vectors.
static double vector_distance2(struct vector *v1, struct vector *v2)
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
        printf("%.2lf%s", v->elements[i], ((i + 1) == v->dimension) ? "" : ", ");
    }
    printf("] }\n");
}

//==============================================================================
// K-Means Clustering
//==============================================================================

// Initializes K-Means algorithm using Forgy's approach.
static void kmeans_init(struct vector *const *points, unsigned npoints, struct vector **centroids, unsigned ncentroids)
{
    // Choose random points to be initial centroids.
    for (unsigned i = 0; i < ncentroids; i++) {
        struct vector *p = points[rand() % npoints];

        vector_assign(centroids[i], p);
    }
}

// Assign points to nearest clusters.
static bool kmeans_assign(unsigned *clusters, struct vector *const *points, unsigned npoints, struct vector **centroids,
                          unsigned ncentroids)
{
    bool changed = false;

    // Process all points.
    for (unsigned i = 0; i < npoints; i++) {
        unsigned nearest = 0;
        double distance = vector_distance2(points[i], centroids[nearest]);

        // Find nearest centroid.
        for (unsigned j = 1; j < ncentroids; j++) {
            double new_distance = vector_distance2(points[i], centroids[j]);

            // printf(" %lf < %lf ?\n", new_distance, distance);
            // Found.
            if (new_distance < distance) {
                distance = new_distance;
                nearest = j;
            }
        }

        // Assign point to a different cluster.
        if (clusters[i] != nearest) {
            clusters[i] = nearest;
            changed = true;
        }
    }

    return (changed);
}

// Updates centroids.
static void kmeans_update(const unsigned *clusters, struct vector *const *points, unsigned npoints,
                          struct vector **centroids, unsigned ncentroids)
{
    unsigned *count = NULL;
    assert((count = malloc(ncentroids * sizeof(unsigned))) != NULL);

    // Zero centroids.
    for (unsigned i = 0; i < ncentroids; i++) {
        count[i] = 0;
    }

    // Process all points.
    for (unsigned i = 0; i < npoints; i++) {
        if (count[clusters[i]]++ == 0) {
            vector_assign(centroids[clusters[i]], points[i]);

        } else {
            vector_add(centroids[clusters[i]], points[i]);
        }
    }

    // Process all points.
    for (unsigned i = 0; i < ncentroids; i++) {
        if (count[i] > 0) {
            vector_scale(centroids[i], 1.0 / count[i]);
        }
    }

    free(count);
}

// K-Means Clustering.
static void kmeans(unsigned *clusters, struct vector *const *points, unsigned npoints, unsigned nclusters)
{
    bool changed = false;
    struct vector *centroids[nclusters];

    // Allocate centroids.
    for (unsigned i = 0; i < nclusters; i++) {
        centroids[i] = vector_create(points[0]->dimension);
    }

    // Assign initial centroids.
    kmeans_init(points, npoints, centroids, nclusters);

    do {
        // Assign points to clusters.
        changed = kmeans_assign(clusters, points, npoints, centroids, nclusters);

        // Update centroids.
        kmeans_update(clusters, points, npoints, centroids, nclusters);
    } while (changed);

    // Release resources.
    for (unsigned i = 0; i < nclusters; i++) {
        vector_destroy(centroids[i]);
    }
}

//==============================================================================
// Test
//==============================================================================

// Tests K-Means Clustering
static void test(unsigned npoints, unsigned nclusters, unsigned dimension, bool verbose)
{
    double tstart = 0.0;
    double tend = 0.0;
    const double MICROSECS = ((CLOCKS_PER_SEC / 1000000.0));
    struct vector **points = NULL;
    unsigned *clusters = NULL;

    // Fix random number generator seed
    // to have a determinist behavior across runs.
    srand(0);

    // Allocate points
    assert((points = malloc(npoints * sizeof(struct vector *))) != NULL);
    for (unsigned i = 0; i < npoints; i++) {
        points[i] = vector_create(dimension);
        vector_random(points[i]);
    }

    // Allocate clusters
    assert((clusters = malloc(npoints * sizeof(unsigned))) != NULL);

    if (verbose) {
        for (unsigned i = 0; i < npoints; i++) {
            vector_print(points[i]);
        }
    }

    // Cluster data.
    tstart = clock();
    kmeans(clusters, points, npoints, nclusters);
    tend = clock();

    // Report time.
    printf("K-Means Clustering: %2.lf us\n", (tend - tstart) / MICROSECS);

    if (verbose) {
        for (unsigned i = 0; i < npoints; i++) {
            printf("Point %u -> Cluster %u\n", i, clusters[i]);
        }
    }

    // Release resources.
    for (unsigned i = 0; i < npoints; i++) {
        vector_destroy(points[i]);
    }
    free(points);
    free(clusters);
}

//==============================================================================
// Usage
//==============================================================================

// Prints program usage and exits.
static void usage(char *const argv[])
{
    printf("%s - Testing program for k-means clustering.\n", argv[0]);
    printf("Usage: %s [--verbose] <number of points> <number of clusters> <dimension>\n", argv[0]);
    exit(EXIT_FAILURE);
}

//==============================================================================
// Main
//==============================================================================

// Drives the test function.
int main(int argc, char *const argv[])
{
    unsigned npoints = 0;
    unsigned nclusters = 0;
    unsigned dimension = 0;
    bool verbose = false;

    // Check for missing arguments.
    if ((argc < 4) || (argc > 5)) {
        printf("Error: invalid number of arguments.\n");
        usage(argv);
    }

    // Parse command line arguments.
    if (argc == 4) {
        sscanf(argv[1], "%u", &npoints);
        sscanf(argv[2], "%u", &nclusters);
        sscanf(argv[3], "%u", &dimension);
    } else if ((argc == 5) && (!strcmp(argv[1], "--verbose"))) {
        sscanf(argv[2], "%u", &npoints);
        sscanf(argv[3], "%u", &nclusters);
        sscanf(argv[4], "%u", &dimension);
        verbose = true;
    } else {
        printf("Error: invalid arguments.\n");
        usage(argv);
    }

    // Run it!
    test(npoints, nclusters, dimension, verbose);

    return (EXIT_SUCCESS);
}
