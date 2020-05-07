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

#include <sys/time.h>
#include <assert.h>
#include <stdio.h>

/**
 * @brief Residual clock.
 */
static unsigned long delta = 0;

/**
 * The clock_read() function reads the wallclock.
 */
unsigned long clock_read(void)
{
	struct timeval tv;

	gettimeofday(&tv,NULL);

	return (1000000 * tv.tv_sec + tv.tv_usec);
}

/**
 * The clock_diff() function returns t1 - t0. Residual error is filtered
 * out.
 */
unsigned long clock_diff(unsigned long t0, unsigned long t1)
{
	return (t1 - t0 - delta);
}

/**
 * The clock_setup() function initializes the clock module.
 */
void clock_setup(void)
{
	unsigned long t0 = clock_read();
	unsigned long t1 = clock_read();

	delta = t1 - t0;
}
