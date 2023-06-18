// Copyright (C) 2022 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//==============================================================================
// Disjoint Set
//==============================================================================

// A disjoint set.
struct dset {
    unsigned length;    // Number of elements.
    unsigned *elements; // Elements.
    unsigned *weights;  // Weight of elements.
};

// Creates a disjoint set.
static struct dset *dset_create(unsigned length)
{
    struct dset *ds = NULL;

    // Allocate resources.
    assert((ds = malloc(sizeof(struct dset))) != NULL);
    assert((ds->elements = malloc(length * sizeof(ds->elements[0]))) != NULL);
    assert((ds->weights = malloc(length * sizeof(ds->weights[0]))) != NULL);

    // Initialize.
    ds->length = length;
    assert(ds->elements != NULL);
    for (unsigned i = 0; i < length; i++) {
        ds->elements[i] = i;
        ds->weights[i] = 1;
    }

    return (ds);
}

// Destroys a disjoint set.
static void dset_destroy(struct dset *ds)
{
    // Sanity check arguments.
    assert(ds != NULL);

    // Release resources.
    free(ds->weights);
    free(ds->elements);
    free(ds);
}

// Finds the representative element of a set in a disjoint set.
static unsigned dset_find(struct dset *ds, unsigned p)
{
    // Sanity check arguments.
    assert(ds != NULL);
    assert(p < ds->length);

    // Traverse set.
    while (p != ds->elements[p]) {
        // Path compression.
        ds->elements[p] = ds->elements[ds->elements[p]];

        // Move to the next element.
        p = ds->elements[p];
    }

    return (p);
}

// Merges two sets of a disjoint set.
static unsigned dset_union(struct dset *ds, unsigned p, unsigned q)
{
    // Sanity check arguments.
    assert(ds != NULL);
    assert(p < ds->length);
    assert(q < ds->length);

    // Find representative elements of each set.
    unsigned p_set = dset_find(ds, p);
    unsigned q_set = dset_find(ds, q);

    // Merge sets.
    if (p_set != q_set) {
        // Weighted-union heuristic: link the representative element of the
        // smaller set  to the representative element of the larger set.
        if (ds->weights[p_set] > ds->weights[q_set]) {
            unsigned tmp = p_set;
            p_set = q_set;
            q_set = tmp;
        }
        ds->elements[p_set] = q_set;
        ds->weights[q_set] += ds->weights[p_set];
    }

    return (q_set);
}

// Prints the contents of a disjoint set.
static void dset_print(const struct dset *ds)
{
    printf("dset { ");
    printf("elements: [");
    for (unsigned i = 0; i < ds->length; i++) {
        printf("%d%s", ds->elements[i], ((i + 1) == ds->length) ? "" : ", ");
    }
    printf("], ");
    printf("weights: [");
    for (unsigned i = 0; i < ds->length; i++) {
        printf("%d%s", ds->weights[i], ((i + 1) == ds->length) ? "" : ", ");
    }
    printf("] }\n");
}

//==============================================================================
// Test
//==============================================================================

// Drives tests on a disjoint set.
static void test(unsigned length, bool verbose)
{
    double tstart = 0.0;
    double tend = 0.0;
    const double MICROSECS = ((CLOCKS_PER_SEC / 1000000.0));
    struct dset *ds = NULL;

    // Create disjoint set.
    ds = dset_create(length);
    if (verbose) {
        dset_print(ds);
    }

    // Merge even sets.
    tstart = clock();
    for (unsigned i = 2; i < length; i += 2) {
        dset_union(ds, 0, i);
    }
    tend = clock();
    if (verbose) {
        dset_print(ds);
    }
    printf("%12s: %2.lf us\n", "dset_union()", (tend - tstart) / MICROSECS);

    // Sanity check result.
    for (unsigned i = 0; i < length; i += 2) {
        assert(dset_find(ds, 0) == dset_find(ds, i));
    }

    // Merge odd sets.
    tstart = clock();
    for (unsigned i = 1; i < length; i += 2) {
        dset_union(ds, 1, i);
    }
    tend = clock();
    if (verbose) {
        dset_print(ds);
    }
    printf("%12s: %2.lf us\n", "dset_union()", (tend - tstart) / MICROSECS);

    // Sanity check result.
    for (unsigned i = 1; i < length; i += 2) {
        assert(dset_find(ds, 1) == dset_find(ds, i));
    }

    // Merge even and odd set.
    tstart = clock();
    dset_union(ds, 0, 1);
    tend = clock();
    if (verbose) {
        dset_print(ds);
    }

    // Sanity check result.
    for (unsigned i = 0; i < length; i++) {
        assert(dset_find(ds, 0) == dset_find(ds, i));
    }

    // Release disjoint set.
    dset_destroy(ds);
}

//==============================================================================
// Usage
//==============================================================================

// Prints program usage and exits.
static void usage(char *const argv[])
{
    printf("%s - Testing program for disjoint sets.\n", argv[0]);
    printf("Usage: %s [--verbose] <length>\n", argv[0]);
    exit(EXIT_FAILURE);
}

//==============================================================================
// Main
//==============================================================================

// Test program.
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
        printf("Error: invalid argument.\n");
        usage(argv);
    }

    // Run it!
    test(length, verbose);

    return (EXIT_SUCCESS);
}
