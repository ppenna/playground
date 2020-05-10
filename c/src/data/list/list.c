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
#include <stdlib.h>
#include <utils.h>
#include "list.h"

/**
 * @brief Linked list.
 */
struct list
{
	int x;              /**< Element   */
	struct list *nextp; /**< Next Node */
};

/**
 * The list_create() function creates a linked list. A dummy head node
 * for the new list is created and returned.
 */
struct list *list_create(void)
{
	struct list *headp;

	headp = smalloc(sizeof(struct list));

	/* Initialize list. */
	headp->nextp = headp;

	return (headp);
}

/**
 * The list_destroy() function destroys the linked list pointed to by @p
 * listp.
 */
int list_destroy(struct list *listp)
{
	/* Sanity check. */
	assert(listp != NULL);
	assert(listp == listp->nextp);

	/* House keeping. */
	free(listp);

	return (0);
}

/**
 * The list_insert() function inserts the element @p x in the list
 * pointed to by @p listp. A new list node is created to store the
 * element, and this node is inserted after the the node pointed to
 * by @p listp.
 */
int list_insert(struct list *listp, int x)
{
	struct list *nodep;

	/* Sanity check. */
	assert(listp != NULL);

	/* Creates a new list node. */
	nodep = smalloc(sizeof(struct list));

	/* Initialize node. */
	nodep->x = x;

	/* Dequeue node. */
	nodep->nextp = listp->nextp;
	listp->nextp = nodep;

	return (0);
}

/**
 * The list_remove() function removes the next element in the list
 * pointed to by @p listp. The remove element is returned.
 */
int list_remove(struct list *listp)
{
	int x;
	struct list *nodep;

	/* Sanity check. */
	assert(listp != NULL);
	assert(listp->nextp != listp);

	/* Dequeue node. */
	nodep = listp->nextp;
	listp->nextp = nodep->nextp;

	x = nodep->x;

	/* House keeping. */
	free(nodep);

	return (x);
}

/**
 * @brief The list_next() function returns the next node in the list
 * pointed to by @p listp.
 */
struct list *list_next(struct list *listp)
{
	/* Sanity check */
	assert(listp != NULL);
	assert(listp->nextp != NULL);

	return (listp->nextp);
}
