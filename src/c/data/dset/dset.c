/*
 * MIT License
 *
 * Copyright(c) 2020 Pedro Henrique Penna <pedrohenriquepenna@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <assert.h>
#include <stdlib.h>
#include <utils.h>
#include "dset.h"

/**
 * @brief Disjoint Set
 */
struct dset
{
	int nsets; /**< Maximum Number of Sets */
	int *sets; /**< Sets                   */
};

/*============================================================================*
 * dset_create()                                                              *
 *============================================================================*/

/**
 * The dset_create() function creates a disjoint set of sets. The
 * maximum number of sets in this disjoint set is set to @p nsets.
 *
 * @note This algorithm features O(n) running time complexity.
 */
struct dset *dset_create(int nsets)
{
	struct dset *ds;

	/* Sanity check. */
	assert((nsets > 0) && (nsets < DSET_MAX_LENGTH));

	/* Allocate resources. */
	ds = smalloc(sizeof(struct dset));

	/* Initialize data structure*/
	ds->nsets = nsets;
	ds->sets = smalloc(nsets*sizeof(int));
	for (int i = 0; i < nsets; i++)
		ds->sets[i] = i;

	return (ds);
}

/*============================================================================*
 * dset_destroy()                                                             *
 *============================================================================*/

/**
 * the dset_destroy() function destroys the disjoint set of sets pointed
 * to by @p ds.
 *
 * @note This algorithm features O(1) running time complexity.
 */
int dset_destroy(struct dset *ds)
{
	/* Sanity check. */
	assert(ds != NULL);

	/* Release resources. */
	free(ds->sets);
	free(ds);

	return (0);
}

/*============================================================================*
 * dset_find()                                                                *
 *============================================================================*/

/**
 * The dset_find() function searches in the disjoint set of sets pointed
 * to by @p ds the set of the element @p p.
 *
 * @note This algorithm features a O(n) worst-case running time
 * complexity.
 */
int dset_find(struct dset *ds, int p)
{
	int i;

	/* Sanity check. */
	assert(ds != NULL);
	assert((p >= 0) && (p < ds->nsets));

	/* Traverse set. */
	for (i = p; i != ds->sets[i]; i = ds->sets[i])
		/* noop */;

	return (i);
}

/*============================================================================*
 * dset_union()                                                               *
 *============================================================================*/

/**
 * The dset_union() function merges two sets of a disjoint set of sets.
 * The set of the element @p p is merged with the set of element @p q.
 *
 * @note This algorithm features O(n) worst-case running time
 * complexity.
 */
int dset_union(struct dset *ds, int p, int q)
{
	int i, j;

	/* Sanity check. */
	assert(ds != NULL);
	assert((p >= 0) && (p < ds->nsets));
	assert((q >= 0) && (q < ds->nsets));

	i = dset_find(ds, p);
	j = dset_find(ds, q);

	/* Nothing to do. */
	if (i == j)
		return (-1);

	/* Merge sets. */
	ds->sets[i] = ds->sets[j];

	return (ds->sets[i]);
}
