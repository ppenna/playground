/*
 * Copyright(c) 2020 Pedro Henrique Penna <pedrohenriquepenna@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

package queue

import (
	"fmt"
)

// Queue Node
type queueNode struct {
	key  int
	next *queueNode
}

// Queue
type Queue struct {
	length int
	head   queueNode
	tail   *queueNode
}

// Creates an empty queue.
func New() *Queue {
	q := new(Queue)

	// Initialize underlying data.
	q.length = 0
	q.head.next = nil
	q.tail = &q.head

	return q
}

// Returns the length of a queue.
func (q *Queue) Length() int {
	return q.length
}

// Enqueues an element in a queue.
func (q *Queue) Enqueue(element int) {
	node := new(queueNode)

	// Initialize node.
	node.key = element
	node.next = nil

	// Update tail.
	q.tail.next = node
	q.tail = node
	q.length++

	// Update head.
	if q.head.next == nil {
		q.head.next = node
	}
}

// Dequeues an element from a queue.
func (q *Queue) Dequeue() int {
	node := q.head.next

	q.head.next = node.next

	// Update tail.
	if q.head.next == nil {
		q.tail = &q.head
	}

	q.length--

	return node.key
}

// Prints a queue.
func (q *Queue) Print() {
	for w := q.head.next; w != nil; w = w.next {
		fmt.Print(w.key, "->")
	}
	fmt.Println("nil")
}

// Tests the linked list implementation.
func Test() {
	q := New()

	for i := 0; i < 10; i++ {
		q.Enqueue(i)
	}

	q.Print()

	for q.Length() > 0 {
		q.Dequeue()
		q.Print()
	}
}
