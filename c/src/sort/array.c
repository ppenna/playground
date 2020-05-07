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
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "array.h"

/**
 * The array_create() function creates an array of @p len elements.
 */
struct array *array_create(size_t len)
{
	struct array *a;

	/* Sanity check. */
	assert(len > 0);

	a = malloc(sizeof(struct array));

	a->length = len;
	a->elements = calloc(len, sizeof(int));
	assert(a->elements != NULL); 

	return (a);
}

/**
 * The array_destroy() function releases the underlying resources
 * allocated for the array pointed to by @p a.
 */
void array_destroy(struct array *a)
{
	/* Sanity check. */
	assert(a != NULL);

	free(a->elements);
	free(a);
}

/**
 * The array_inti() function initializes the array pointed to by @p a
 * with random numbers.
 */
void array_init(struct array *a)
{
	/* Sanity check. */
	assert(a != NULL);

	srand(13);

	for (size_t i = 0; i < a->length; i++)
		a->elements[i] = rand();
}

/**
 * The array_is_sorted() function asserts if the array pointed to by @p a
 * is sorted.
 */
bool array_is_sorted(const struct array *a)
{
	/* Sanity check. */
	assert(a != NULL);

	for (size_t i = 0; i < a->length - 1; i++)
	{
		if (a->elements[i] > a->elements[i + 1])
			return (false);
	}

	return (true);
}
