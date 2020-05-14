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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utils.h>

/**
 * @brief Default size for a matrix.
 */
#define DEFAULT_SIZE 512

/**
 * @brief Number of iterations.
 */
#define NITERATIONS 30

/**
 * @brief Returns the element [i][j] of a matrix.
 */
#define MATRIX(m, i, j) m[(i)*n + (j)]

/*============================================================================*
 * Cache-Unware Matrix Multiplication                                         *
 *============================================================================*/

/**
 * @brief Performs a matrix multiplication (outer for).
 *
 * @param c Resulting matrix.
 * @param a First operand matrix.
 * @param b Second operand matrix.
 * @param n Matrix size.
 */
static void matrix_mult1(double *restrict c, const double *restrict a, const double *restrict b, int n)
{
	for (int j = 0; j < n; j++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int k = 0; k < n; k++)
				MATRIX(c, i, j) += MATRIX(a, i, k)*MATRIX(b, k, j);
		}
	}
}

/*============================================================================*
 * Cache-Aware Matrix Multiplication                                          *
 *============================================================================*/

/**
 * @brief Performs a matrix multiplication (inner for).
 *
 * @param c Resulting matrix.
 * @param a First operand matrix.
 * @param b Second operand matrix.
 * @param n Matrix size.
 */
static void matrix_mult2(double *restrict c, const double *restrict a, const double *restrict b, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
				MATRIX(c, i, j) += MATRIX(a, i, k)*MATRIX(b, k, j);
		}
	}
}

/*============================================================================*
 * Cache-Oblivious Matrix Multiplication                                      *
 *============================================================================*/

/**
 * @brief Size of a cache block.
 */
#define BLOCK_SIZE 16

/**
 * @brief Performs a cache-oblivious matrix multiplication.
 *
 * @param c Resulting matrix.
 * @param a First operand matrix.
 * @param b Second operand matrix.
 * @param n Matrix size.
 */
static void matrix_mult3(double *restrict c, const double *restrict a, const double *restrict b, int n)
{
	for (int bi=0; bi < n; bi += BLOCK_SIZE)
	{
		for (int bj=0; bj < n; bj += BLOCK_SIZE)
		{
			for (int bk=0; bk < n; bk += BLOCK_SIZE)
			{
				for (int i=0; i < BLOCK_SIZE; i++)
				{
					for (int j=0; j < BLOCK_SIZE; j++)
					{
						for (int k=0; k < BLOCK_SIZE; k++)
						{
							MATRIX(c, bi + i, bj + j) +=
								MATRIX(a, bi + i, bk + k)*MATRIX(b, bk + k, bj + j);
						}
					}
				}
			}
		}
	}
}

/*============================================================================*
 * Cache-Oblivious Matrix Multiplication                                      *
 *============================================================================*/

/**
 * @brief Size of a cache block.
 */
#define BLOCK_SIZE 16

/**
 * @brief Performs a cache-oblivious matrix multiplication.
 *
 * @param c Resulting matrix.
 * @param a First operand matrix.
 * @param b Second operand matrix.
 * @param n Matrix size.
 */
static void matrix_mult4(double *restrict c, const double *restrict a, const double *restrict b, int n)
{
	for (int bi=0; bi < n; bi += BLOCK_SIZE)
	{
		for (int bj=0; bj < n; bj += BLOCK_SIZE)
		{
			for (int bk=0; bk < n; bk += BLOCK_SIZE)
			{
				for (int i=0; i < BLOCK_SIZE; i++)
				{
					for (int j=0; j < BLOCK_SIZE; j++)
					{
							MATRIX(c, bi + i, bj + j) += MATRIX(a, bi + i, bk + 0)*MATRIX(b, bk + 0, bj + j);
							MATRIX(c, bi + i, bj + j) += MATRIX(a, bi + i, bk + 1)*MATRIX(b, bk + 1, bj + j);
							MATRIX(c, bi + i, bj + j) += MATRIX(a, bi + i, bk + 2)*MATRIX(b, bk + 2, bj + j);
							MATRIX(c, bi + i, bj + j) += MATRIX(a, bi + i, bk + 3)*MATRIX(b, bk + 3, bj + j);
							MATRIX(c, bi + i, bj + j) += MATRIX(a, bi + i, bk + 4)*MATRIX(b, bk + 4, bj + j);
							MATRIX(c, bi + i, bj + j) += MATRIX(a, bi + i, bk + 5)*MATRIX(b, bk + 5, bj + j);
							MATRIX(c, bi + i, bj + j) += MATRIX(a, bi + i, bk + 6)*MATRIX(b, bk + 6, bj + j);
							MATRIX(c, bi + i, bj + j) += MATRIX(a, bi + i, bk + 7)*MATRIX(b, bk + 7, bj + j);
							MATRIX(c, bi + i, bj + j) += MATRIX(a, bi + i, bk + 8)*MATRIX(b, bk + 8, bj + j);
							MATRIX(c, bi + i, bj + j) += MATRIX(a, bi + i, bk + 9)*MATRIX(b, bk + 9, bj + j);
							MATRIX(c, bi + i, bj + j) += MATRIX(a, bi + i, bk + 10)*MATRIX(b, bk + 10, bj + j);
							MATRIX(c, bi + i, bj + j) += MATRIX(a, bi + i, bk + 11)*MATRIX(b, bk + 11, bj + j);
							MATRIX(c, bi + i, bj + j) += MATRIX(a, bi + i, bk + 12)*MATRIX(b, bk + 12, bj + j);
							MATRIX(c, bi + i, bj + j) += MATRIX(a, bi + i, bk + 13)*MATRIX(b, bk + 13, bj + j);
							MATRIX(c, bi + i, bj + j) += MATRIX(a, bi + i, bk + 14)*MATRIX(b, bk + 14, bj + j);
							MATRIX(c, bi + i, bj + j) += MATRIX(a, bi + i, bk + 15)*MATRIX(b, bk + 15, bj + j);
					}
				}
			}
		}
	}
}

/*============================================================================*/

/**
 * @brief Creates a matrix.
 *
 * @param m Target matrix.
 */
static double *matrix_create(int n)
{
	double *m;

	m = malloc(n*n*sizeof(double));
	assert(m != NULL);

	memset(m, 0, n*n*sizeof(double));

	return (m);
}

static void matrix_init(double *m, int n)
{
	srand(13);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			MATRIX(m, i, j) = rand()/10.0;
	}
}

/**
 * @brief A simple matrix multiplication benchmark.
 */
int main(int argc, char **argv)
{
	int n;
	double *a, *b;
	double *c1, *c2, *c3;
	double avg;
	unsigned long start, end;

	((void) argc);
	((void) argv);

	n = DEFAULT_SIZE;

	if (argc >= 2)
		assert((n = atoi(argv[1])) > 0);

	printf("running with %dx%d matrices...\n", n, n);

	/* Setup profiling. */
	clock_setup();

	a = matrix_create(n); matrix_init(a, n);
	b  = matrix_create(n); matrix_init(b, n);
	c1 = matrix_create(n); matrix_init(c1, n);
	c2 = matrix_create(n); matrix_init(c2, n);
	c3 = matrix_create(n); matrix_init(c3, n);

	/* Benchmark 1. */
	avg = 0.0;
	matrix_mult1(c1, a, b, n);
	for (int it = 0; it < NITERATIONS; it++)
	{
		start = clock_read();
		matrix_mult1(c1, a, b, n);
		end = clock_read();
		avg += clock_diff(start, end);
	}
	printf("cache-unaware:      %.2lf us\n", avg/NITERATIONS);

	/* Benchmark 2. */
	avg = 0.0;
	matrix_mult2(c2, a, b, n);
	for (int it = 0; it < NITERATIONS; it++)
	{
		start = clock_read();
		matrix_mult2(c2, a, b, n);
		end = clock_read();
		avg += clock_diff(start, end);
	}
	printf("cache-aware:        %.2lf us\n", avg/NITERATIONS);

	/* Benchmark 2. */
	avg = 0.0;
	matrix_mult2(c3, a, b, n);
	for (int it = 0; it < NITERATIONS; it++)
	{
		start = clock_read();
		matrix_mult3(c3, a, b, n);
		end = clock_read();
		avg += clock_diff(start, end);
	}
	printf("cache-oblivious:   %.2lf us\n", avg/NITERATIONS);

	/* Benchmark 2. */
	avg = 0.0;
	matrix_mult2(c3, a, b, n);
	for (int it = 0; it < NITERATIONS; it++)
	{
		start = clock_read();
		matrix_mult4(c3, a, b, n);
		end = clock_read();
		avg += clock_diff(start, end);
	}
	printf("cache-oblivious unroll:   %.2lf us\n", avg/NITERATIONS);

	/* House keeping. */
	free(a);
	free(b);
	free(c1);
	free(c2);
	free(c3);

	return (EXIT_FAILURE);
}
