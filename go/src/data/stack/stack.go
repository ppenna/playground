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

package stack

import (
	"fmt"
	"time"
)

// Node
type Node struct {

	// Stored Value
	Value interface{}

	// Next Element
	next *Node
}

// Stack
type Stack struct {
	// Current Length
	length int

	// Dummy Head
	head Node
}

// Creates an empty stack.
func New() *Stack {
	s := new(Stack)

	// Initialize stack.
	s.head.next = nil
	s.length = 0

	return s
}

// Returns the length of a stack.
func (s *Stack) Length() int {
	return s.length
}

// Asserts if a stack is empty.
func (s *Stack) isEmpty() bool {
	return s.length == 0
}

// Pushes a node on a stack.
func (s *Stack) Push(node *Node) {
	node.next = s.head.next
	s.head.next = node
	s.length++
}

// Pops a node from a stack.
func (s *Stack) Pop() interface{} {
	if s.isEmpty() {
		return nil
	}

	node := s.head.next
	s.head.next = node.next
	s.length--

	return node.Value
}

// Tests the stack implementation
func Test() {
	var t0, t1 time.Time
	const NumNodes = 1024 * 1024

	s := New()

	t0 = time.Now()
	for i := 0; i < NumNodes; i++ {
		s.Push(&Node{Value: i})
	}
	t1 = time.Now()
	fmt.Println("push:", t1.Sub(t0))

	if s.Length() != NumNodes {
		panic("stack: bad length")
	}

	t0 = time.Now()
	for i := NumNodes - 1; i >= 0; i-- {
		if value := s.Pop(); value != i {
			panic("stack: bad pop")
		}
	}
	t1 = time.Now()
	fmt.Println("pop:", t1.Sub(t0))
}
