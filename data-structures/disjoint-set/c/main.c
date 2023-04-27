// Copyright (C) 2022 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Maximum max_cardinality for a disjoint set.
#define DSET_MAX_CARDINALITY 1024

// A disjoint set.
struct dset {
    unsigned max_cardinality; // Maximum cardinality.
    unsigned cardinality;     // Current cardinality.
    unsigned *sets;           // Sets.
};

// Creates a disjoint set.
static struct dset *dset_create(unsigned max_cardinality)
{
    struct dset *ds = malloc(sizeof(struct dset));
    assert(ds != NULL);

    // Initialize data struct.
    ds->max_cardinality = max_cardinality;
    ds->cardinality = max_cardinality;
    ds->sets = malloc(max_cardinality * sizeof(unsigned));
    assert(ds->sets != NULL);
    for (unsigned i = 0; i < max_cardinality; i++)
        ds->sets[i] = (unsigned)i;

    return (ds);
}

// Destroys a disjoint set.
static void dset_destroy(struct dset *ds)
{
    // Sanity check.
    assert(ds != NULL);

    // Release resources.
    free(ds->sets);
    free(ds);
}

// Searches a disjoint set for an element.
static unsigned dset_find(struct dset *ds, unsigned p)
{
    unsigned i;

    // Sanity check.
    assert(ds != NULL);
    assert(p < ds->max_cardinality);

    // Traverse set.
    for (i = p; i != ds->sets[i]; i = ds->sets[i])
        /* noop */;

    return (i);
}

// Merges two sets of a disjoint set.
static unsigned dset_union(struct dset *ds, unsigned p, unsigned q)
{
    printf("union(%u, %u)\n", p, q);
    // Sanity check.
    assert(ds != NULL);
    assert(p < ds->max_cardinality);
    assert(q < ds->max_cardinality);

    unsigned i = dset_find(ds, p);
    unsigned j = dset_find(ds, q);

    // Nothing to do.
    if (i == j)
        return (-1);

    // Merge sets.
    ds->sets[i] = ds->sets[j];
    ds->cardinality -= 1;

    return (ds->sets[i]);
}

// Prints the contents of a disjoint set.
static void dset_print(const struct dset *ds)
{
    printf("disjoin-set { ");
    printf("max_cardinality: %u, ", ds->max_cardinality);
    printf("cardinality: %u, ", ds->cardinality);
    printf("elements: [");
    printf("elements: [");
    for (size_t i = 0; i < ds->max_cardinality; i++) {
        printf(
            "%d%s", ds->sets[i], ((i + 1) == ds->max_cardinality) ? "" : ", ");
    }
    printf("] }\n");
}

// Tests a disjoint set.
static void test(unsigned max_cardinality, bool verbose)
{
    double tstart = 0.0;
    double tend = 0.0;
    const double MICROSECS = ((CLOCKS_PER_SEC / 1000000.0));
    struct dset *ds = dset_create(max_cardinality);

    if (verbose) {
        dset_print(ds);
    }

    // Merge even sets.
    tstart = clock();
    for (unsigned i = 2; i < max_cardinality; i += 2) {
        dset_union(ds, i, 0);
        if (verbose) {
            dset_print(ds);
        }
    }
    tend = clock();
    if (verbose) {
        dset_print(ds);
    }
    printf("%12s: %2.lf us\n", "dset_union()", (tend - tstart) / MICROSECS);

    // Release disjoint set.
    dset_destroy(ds);
}

// Prints program usage and exits.
static void usage(char *const argv[])
{
    printf("%s - Testing program for queues .\n", argv[0]);
    printf("Usage: %s [--verbose] <maximum cardinality>\n", argv[0]);
    exit(EXIT_FAILURE);
}

// Drives the test function.
int main(int argc, char *const argv[])
{
    unsigned max_cardinality = 0;
    bool verbose = false;

    // Check for missing arguments.
    if ((argc < 2) || (argc > 3)) {
        printf("Error: invalid number of arguments.\n");
        usage(argv);
    }

    // Parse command line arguments.
    if (argc == 2) {
        sscanf(argv[1], "%u", &max_cardinality);
    } else if ((argc == 3) && (!strcmp(argv[1], "--verbose"))) {
        sscanf(argv[2], "%u", &max_cardinality);
        verbose = true;
    } else {
        printf("Error: invalid arguments.\n");
        usage(argv);
    }

    // Run it!
    test(max_cardinality, verbose);

    return (EXIT_SUCCESS);
}
