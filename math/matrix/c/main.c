// Copyright (C) 2022 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//==============================================================================
// Matrix
//==============================================================================

// A matrix.
struct matrix {
    unsigned nlines;  // Number of lines.
    unsigned ncols;   // Number of columns.
    double *elements; // Elements.
};

// Creates a matrix.
static struct matrix *matrix_create(unsigned nlines, unsigned ncols)
{
    struct matrix *m = malloc(sizeof(struct matrix));
    assert(m != NULL);

    m->nlines = nlines;
    m->ncols = ncols;
    m->elements = malloc(nlines * ncols * sizeof(double));
    assert(m->elements != NULL);

    return (m);
}

// Destroys a matrix.
static void matrix_destroy(struct matrix *m)
{
    assert(m != NULL);
    free(m->elements);
    free(m);
}

// Adds two matrices.
static void matrix_add(const struct matrix *c,
                       const struct matrix *a,
                       struct matrix *b)
{
    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);
    assert(a->nlines == b->nlines);
    assert(a->ncols == b->ncols);
    assert(a->nlines == c->nlines);
    assert(a->ncols == c->ncols);

    for (size_t i = 0; i < a->nlines; i++) {
        for (size_t j = 0; j < a->ncols; j++) {
            c->elements[i * c->ncols + j] =
                a->elements[i * a->ncols + j] + b->elements[i * b->ncols + j];
        }
    }
}

// Multiples a matrix by a scalar.
static void matrix_scale(const struct matrix *c,
                         const struct matrix *a,
                         double scalar)
{
    assert(a != NULL);
    assert(c != NULL);
    assert(a->nlines == c->nlines);
    assert(a->ncols == c->ncols);

    for (size_t i = 0; i < a->nlines; i++) {
        for (size_t j = 0; j < a->ncols; j++) {
            c->elements[i * c->ncols + j] =
                a->elements[i * a->ncols + j] * scalar;
        }
    }
}

// Transposes a matrix.
static void matrix_transpose(const struct matrix *c, const struct matrix *a)
{
    assert(a != NULL);
    assert(c != NULL);
    assert(a->nlines == c->ncols);
    assert(a->ncols == c->nlines);

    for (size_t i = 0; i < a->nlines; i++) {
        for (size_t j = 0; j < a->ncols; j++) {
            c->elements[i * c->ncols + j] = a->elements[j * a->ncols + i];
        }
    }
}

// Multiplies two matrices.
static void matrix_multiply(const struct matrix *c,
                            const struct matrix *a,
                            const struct matrix *b)
{
    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);
    assert(a->ncols == b->nlines);
    assert(a->nlines == c->nlines);
    assert(b->ncols == c->ncols);

    for (size_t i = 0; i < a->nlines; i++) {
        for (size_t j = 0; j < b->ncols; j++) {
            double sum = 0.0;
            for (size_t k = 0; k < a->ncols; k++) {
                sum += a->elements[i * a->ncols + k] *
                       b->elements[k * b->ncols + j];
            }
            c->elements[i * c->ncols + j] = sum;
        }
    }
}

// Fills a matrix with random values.
static void matrix_fill(struct matrix *m)
{
    assert(m != NULL);

    for (size_t i = 0; i < m->nlines; i++) {
        for (size_t j = 0; j < m->ncols; j++) {
            m->elements[i * m->ncols + j] = (double)rand() / RAND_MAX;
        }
    }
}

// Prints the contents of a matrix.
static void matrix_print(const struct matrix *m)
{
    assert(m != NULL);

    printf("matrix {\n  ");
    printf("nlines: %u,\n  ", m->nlines);
    printf("ncols: %u,\n  ", m->ncols);
    printf("elements: [\n");
    for (size_t i = 0; i < m->nlines; i++) {
        printf("    ");
        for (size_t j = 0; j < m->ncols; j++) {
            printf("%f.4%s",
                   m->elements[i * m->ncols + j],
                   ((j + 1) == m->ncols) ? "" : ", ");
        }
        printf("\n");
    }
    printf("  ]\n}\n");
}

//==============================================================================
// Test
//==============================================================================

// Tests matrices.
static void test(unsigned n, bool verbose)
{
    double tstart = 0.0;
    double tend = 0.0;
    const double MICROSECS = ((CLOCKS_PER_SEC / 1000000.0));
    struct matrix *a = matrix_create(n, n);
    struct matrix *b = matrix_create(n, n);
    struct matrix *c = matrix_create(n, n);

    matrix_fill(a);
    matrix_fill(b);

    if (verbose) {
        matrix_print(a);
        matrix_print(b);
    }

    // Add.
    tstart = clock();
    matrix_add(c, a, b);
    tend = clock();
    if (verbose) {
        matrix_print(c);
    }
    printf("%12s: %2.lf us\n", "matrix_add()", (tend - tstart) / MICROSECS);

    // Scale.
    tstart = clock();
    matrix_scale(c, a, 2.0);
    tend = clock();
    if (verbose) {
        matrix_print(c);
    }
    printf("%12s: %2.lf us\n", "matrix_scale()", (tend - tstart) / MICROSECS);

    // Transpose.
    tstart = clock();
    matrix_transpose(c, a);
    tend = clock();
    if (verbose) {
        matrix_print(c);
    }
    printf(
        "%12s: %2.lf us\n", "matrix_transpose()", (tend - tstart) / MICROSECS);

    // Multiply.
    tstart = clock();
    matrix_multiply(c, a, b);
    tend = clock();
    if (verbose) {
        matrix_print(c);
    }
    printf(
        "%12s: %2.lf us\n", "matrix_multiply()", (tend - tstart) / MICROSECS);

    // Release resources.
    matrix_destroy(a);
    matrix_destroy(b);
}

//==============================================================================
// Usage
//==============================================================================

// Prints program usage and exits.
static void usage(char *const argv[])
{
    printf("%s - Testing program for matrices.\n", argv[0]);
    printf("Usage: %s [--verbose] <matrix size>\n", argv[0]);
    exit(EXIT_FAILURE);
}

//==============================================================================
// Main
//==============================================================================

// Drives the test function.
int main(int argc, char *const argv[])
{
    unsigned n = 0;
    bool verbose = false;

    // Check for missing arguments.
    if ((argc < 2) || (argc > 3)) {
        printf("Error: invalid number of arguments.\n");
        usage(argv);
    }

    // Parse command line arguments.
    if (argc == 2) {
        sscanf(argv[1], "%u", &n);
    } else if ((argc == 3) && (!strcmp(argv[1], "--verbose"))) {
        sscanf(argv[2], "%u", &n);
        verbose = true;
    } else {
        printf("Error: invalid arguments.\n");
        usage(argv);
    }

    // Run it!
    test(n, verbose);

    return (EXIT_SUCCESS);
}
