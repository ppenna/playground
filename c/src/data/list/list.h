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

#ifndef _LIST_H_
#define _LIST_H_

	/**
	 * @brief Opaque pointer to a list.
	 */
	typedef struct list * list_tt;

	/**
	 * @brief Creates a list.
	 *
	 * @returns Upon successful completion, a pointer to the head node
	 * new list is returned.
	 */
	extern list_tt list_create(void);

	/**
	 * @brief Destroys a list.
	 *
	 * @param listp Target list.
	 *
	 * @returns Upon successful completion zero is returned.
	 */
	extern int list_destroy(list_tt listp);

	/**
	 * @brief Inserts an element in a list.
	 *
	 * @param listp Target list.
	 * @param x     Element.
	 *
	 * @returns Upon successful completion, zero is returned.
	 */
	extern int list_insert(list_tt listp, int x);

	/**
	 * @brief Removes an element from a list.
	 *
	 * @param listp Target list.
	 *
	 * @returns Upon successful completion, the removed element is
	 * returned.
	 */
	extern int list_remove(list_tt listp);

	/**
	 * @brief Returns the next node in a list.
	 *
	 * @param listp Target list.
	 *
	 * @returns A pointer to the next node in a list.
	 */
	extern list_tt list_next(list_tt listp);

#endif /* _LIST_H_ */
