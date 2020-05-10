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

#include <stdio.h>
#include <stdlib.h>
#include <utils.h>
#include "list.h"

/**
 * @brief Default length for the list.
 */
#define LIST_LENGTH_DEFAULT (1024*1024)

/**
 * @brief Test-driver for Disjoint-Set data structure.
 */
int main(int argc, char **argv)
{
	int length;
	list_tt headp;
	unsigned long start, end;
	unsigned long t1, t2, t3;

	length = LIST_LENGTH_DEFAULT;

	/* Override default list length.*/
	if (argc > 1)
	{
		sscanf(argv[1], "%d", &length);
		if (length < 0)
			length = LIST_LENGTH_DEFAULT;
	}

	printf("running with length %d...\n", length);

	headp = list_create();

	/*
	 * Run two iterations: one to warmup and 
	 * another one to gather execution statistics.
	 */
	for (int it = 0; it < 2; it++)
	{
		/* Inserts elements in the list. */
		start = clock_read();
			for (int i = 0; i < length; i++)
				list_insert(headp, i);
		end = clock_read();
		t1 = clock_diff(start, end);

		/* Traverse the list. */
		start = clock_read();
		for (list_tt w = list_next(headp); w != headp; w = list_next(w))
			/* noop */;
		end = clock_read();
		t2 = clock_diff(start, end);

		/* Removes elements from the list. */
		start = clock_read();
		for (int i = 0; i < length; i++)
			list_remove(headp);
		end = clock_read();
		t3 = clock_diff(start, end);
	}

	/* Print execution statistics. */
	printf("insert:    %8lu us\n", t1);
	printf("traverse:  %8lu us\n", t2);
	printf("remove:    %8lu us\n", t3);

	/* House keeping. */
	list_destroy(headp);

	return (EXIT_SUCCESS);
}

