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
#include "dset.h"

/**
 * @brief Test-driver for Disjoint-Set data structure.
 */
int main(int argc, char **argv)
{
	int p, q;
	dset_tt ds;

	((void) argc);
	((void) argv);

	ds = dset_create(DSET_MAX_LENGTH);

	/* Reads input data. */
	while (scanf("%d%d", &p, &q) == 2)
	{
		if (dset_union(ds, p, q) < 0)
			continue;

		printf("%d-%d\n", p, q);
	}

	/* House keeping. */
	dset_destroy(ds);

	return (EXIT_SUCCESS);
}
