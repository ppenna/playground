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

#ifndef ARRAY_H_
#define ARRAY_H_

	#include <stddef.h>
	#include <stdbool.h>

	/**
	 * @brief An array of integers.
	 */
	struct array
	{
		size_t length; /**< Length of the array.   */
		int *elements; /**< Elements in the array. */
	};

	/**
	 * @brief Swaps two elements.
	 */
	static inline void swap(int *a, int i, int j)
	{
		int tmp;

		tmp = a[i];
		a[i] = a[j];
		a[j] = tmp;
	}

	/**
	 * @brief Sorts an array using Quicksort.
	 *
	 * @param a Target array.
	 */
	extern void quicksort(struct array *a);

	/**
	 * @brief Creates a array.
	 *
	 * @param len The length of the array.
	 *
	 * @returns A new array.
	 */
	extern struct array *array_create(size_t len);

	/**
	 * @brief Destroys an array.
	 *
	 * @param a Target array.
	 */
	extern void array_destroy(struct array *a);

	/**
	 * @brief Initializes an array.
	 *
	 * @param a Target array.
	 */
	extern void array_init(struct array *a);

	/**
	 * @brief Asserts if an array is sorted.
	 *
	 * @para a Target array.
	 *
	 * @returns True if the array is sorted and false otherwise.
	 */
	extern bool array_is_sorted(const struct array *a);

#endif /* ARRAY_H_ */
