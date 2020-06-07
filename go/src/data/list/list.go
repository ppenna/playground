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

package list

import (
	"fmt"
)

// List node.
type listNode struct {
	key  int
	next *listNode
}

// List
type list struct {
	length int
	head   listNode
	tail   *listNode
}

// Creates a linked list.
func New() *list {
	l := new(list)

	l.length = 0
	l.head.next = nil
	l.tail = &l.head

	return l
}

// Deletes a linked list.
func (l *list) Delete() {

	// Release all nodes.
	for w := l.head.next; w != nil; {
		p := w
		w = w.next
		p.next = nil
	}

	l.length = 0

	// Release memory
	l.head.next = nil
	l.tail = nil
}

// Returns the length of a linked list.
func (l *list) Length() int {
	return l.length
}

// Returns the head node of a list.
func (l *list) Head() *listNode {
	return &l.head
}

// Returns the tail node of a list.
func (l *list) Tail() *listNode {
	return l.tail
}

// Returns the next node in a list.
func (node *listNode) Next() *listNode {
	return node.next
}

// Inserts a new node to a linked list (after an existing node).
func (l *list) InsertAfter(node, newNode *listNode) {
	newNode.next = node.next
	node.next = newNode
	l.length++
}

// Inserts a new node to a linked list (at the front).
func (l *list) PushFront(node *listNode) {

	node.next = l.head.next
	l.head.next = node

	// Update tail.
	if l.tail == &l.head {
		l.tail = node
	}

	l.length++
}

// Removes a node from a linked list (at the back).
func (l *list) PushBack(node *listNode) {

	node.next = nil
	l.tail.next = node
	l.tail = node

	// Update head.
	if l.head.next == nil {
		l.head.next = node
	}

	l.length++
}

// Removes the next node in a linked list.
func (l *list) RemoveNext(node *listNode) {

	// Update tail
	if node.next == l.tail {
		l.tail = node
	}

	node.next = node.next.next
	l.length--
}

// Prints a list.
func (l *list) Print() {
	for w := l.head.next; w != nil; w = w.next {
		fmt.Print(w.key, "->")
	}
	fmt.Println("nil")
}

// Tests the linked list implementation.
func Test() {
	l := New()

	// Insert some nodes in the list.
	for i := 0; i < 10; i++ {
		node := new(listNode)
		node.key = i
		l.PushFront(node)
	}

	l.Print()

	// Remove some nodes from the list.
	for w := l.Head(); w.Next() != nil; w = w.Next() {
		l.RemoveNext(w)
	}

	l.Print()

	// Insert some nodes in the list.
	for i := 1; i < 10; i += 2 {
		node := new(listNode)
		node.key = i
		l.PushBack(node)
	}

	l.Print()

	// Remove some nodes from the list.
	for w := l.Head(); w.Next() != nil; w = w.Next() {
		l.RemoveNext(w)
	}

	l.Print()

	for i := 0; i < 10; i += 2 {
		node := new(listNode)
		node.key = 20
		l.InsertAfter(l.Head(), node)
	}

	l.Print()
}
