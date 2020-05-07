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
#include <stdbool.h>
#include <stddef.h>
#include "array.h"

/**
 * @brief Naive partitioning method for Quicksort.
 *
 * @param a Target array.
 * @param l Left-most position in the array.
 * @param r Right-mist position in the array.
 */
static int partition(struct array *a, int l, int r)
{
	int v, i, j;

	/* Sanity check. */
	assert(a != NULL);
	assert(l >= 0);
	assert(r >= 0);

	i = l;
	j = r + 1;
	v = a->elements[l];

	while (true)
	{
		while (a->elements[++i] < v)
		{
			if (i == r)
				break;
		}

		while (v < a->elements[--j])
		{
			if (j == l)
				break;
		}

		if (i >= j)
			break;

		swap(a->elements, i, j);
	}

	swap(a->elements, l, j);

	return (j);
}

/**
 * @brief Sorts an array using Quicksort.
 *
 * @param a Target array.
 * @param l Left-most position in the array.
 * @param r Right-mist position in the array.
 */
static void _quicksort(struct array *a, int l, int r)
{
	int v;

	/* Sorted. */
	if (r <= l)
		return;

	/* Sanity check. */
	assert(a != NULL);
	assert(l >= 0);
	assert(r >= 0);

	v = partition(a, l, r);
	_quicksort(a, l, v - 1);
	_quicksort(a, v + 1, r);
}

/**
 * See _quicksort() for a more detailed description.
 */
void quicksort(struct array *a)
{
	/* Sanity check. */
	assert(a);

	_quicksort(a, 0, a->length - 1);

	assert(array_is_sorted(a));
}
