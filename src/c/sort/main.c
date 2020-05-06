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
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>
#include "array.h"

/**
 * @brief Number of iterations.
 */
#define NITERATIONS 30

/**
 * @brief Default array length.
 */
#ifndef NDEBUG
#define DEFAULT_LENGTH (32)
#else
#define DEFAULT_LENGTH (1024*1024)
#endif

/**
 * @brief Sorts an array using Quicksort.
 */
int main(int argc, char *argv[])
{
	size_t len;
	struct array *a;
	double avg;
	unsigned long start, end;

	len = DEFAULT_LENGTH;
	if (argc >= 2)
		len = atoi(argv[1]);

	assert(len > 0);

	printf("sorting %d integers...\n", len);

	/* Setup profiling. */
	clock_setup();

	/* Create and initialize array. */
	a = array_create(len);
	array_init(a);

	avg = 0.0;
	quicksort(a);
	for (int it = 0; it < NITERATIONS; it++)
	{
		array_init(a);

		start = clock_read();
		quicksort(a);
		end = clock_read();
		avg += clock_diff(start, end);
	}
	printf("quicksort:      %.2lf us\n", avg/NITERATIONS);

	/* House keeping. */
	array_destroy(a);

	return (EXIT_SUCCESS);
}
