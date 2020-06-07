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

package sorting

import (
	"fmt"
)

// Length of Array
const arrayLength = 32

// Heap
type Heap struct {
	array  []int
	length int
}

// Swaps two elements in an array.
func swap(array []int, i, j int) {
	tmp := array[i]
	array[i] = array[j]
	array[j] = tmp
}

// Initializes a binary heap.
func (heap *Heap) Init(length int) {
	heap.array = make([]int, length+1)
	heap.length = 0
	heap.array[0] = int(^uint(0) >> 1)
	for i := 1; i < length+1; i++ {
		heap.array[i] = -1
	}
}

// Inserts an element in a binary heap.
func (heap *Heap) Insert(element int) {

	// Insert element.
	heap.length++
	heap.array[heap.length] = element

	current := heap.length
	parent := current / 2

	// Fix heap property.
	for parent >= 1 {

		// Done.
		if heap.array[current] <= heap.array[parent] {
			break
		}

		swap(heap.array, parent, current)

		current = parent
		parent = current / 2
	}
}

// Removes an element from a binary heap.
func (heap *Heap) Remove() int {

	// Remove element.
	element := heap.array[1]
	heap.array[1] = -1
	swap(heap.array, 1, heap.length)
	heap.length--

	current := 1
	child := 2

	// Fix heap property.
	for child < len(heap.array) {
		largest := current

		// Left sub-tree.
		if heap.array[child] > heap.array[largest] {
			largest = child
		}

		// Right sub-tree.
		if child++; child < len(heap.array) {
			if heap.array[child] > heap.array[largest] {
				largest = child
			}
		}

		// Done.
		if largest == current {
			break
		}

		// Swap.
		swap(heap.array, current, largest)
		current = largest
		child = 2 * current
	}

	return element
}

// Sorts an array.
func Heapsort(a []int) {
	var heap Heap

	heap.Init(len(a))

	for i := 0; i < len(a); i++ {
		heap.Insert(a[i])
	}

	for i := 0; i < len(a); i++ {
		a[i] = heap.Remove()
	}
}

// Tests the Heapsort algorithm.
func Test() {
	var array []int

	array = make([]int, arrayLength)

	// Build the input array.
	for i := 0; i < arrayLength; i += 2 {
		array[i] = arrayLength - i
		array[i+1] = i + 1
	}

	fmt.Println(array)

	Heapsort(array)

	fmt.Println(array)
}
