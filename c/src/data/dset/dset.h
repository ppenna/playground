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

#ifndef _DSET_H_
#define _DSET_H_

	/**
	 * @brief Maximum number of sets in a disjoint set.
	 */
	#define DSET_MAX_LENGTH 1000000

	/**
	 * @brief Opaque pointer to a disjoint set.
	 */
	typedef struct dset * dset_tt;

	/**
	 * @brief Creates a disjoint set.
	 *
	 * @param nsets Maximum number of sets.
	 *
	 * @returns Upon successful completion, a pointer to the new
	 * disjoint set is returned.
	 */
	extern struct dset *dset_create(int nsets);

	/**
	 * @brief Destroys a disjoint set.
	 *
	 * @param ds Target disjoint set.
	 *
	 * @returns Zero is always returned.
	 */
	extern int dset_destroy(struct dset *ds);

	/**
	 * @brief Finds the set of an element in a disjoint set.
	 *
	 * @param ds Target disjoint set.
	 * @param p  Target element.
	 *
	 * @returns The set identifier of @p p is returned.
	 */
	extern int dset_find(struct dset *ds, int p);

	/**
	 * @brief Merges two sets in a disjoint set.
	 *
	 * @param ds Target disjoint set.
	 * @param p  Element in the first set.
	 * @param q  Element in the second set.
	 *
	 * @returns The set identifier of the merged set is returned. If no
	 * merge was carried out, a negative number is returned instead.
	 */
	extern int dset_union(struct dset *ds, int p, int q);

#endif /* _DSET_H_ */
