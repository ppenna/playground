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

// Swaps two elements in an array.
func swap(a []int, i, j int) {
	tmp := a[i]
	a[i] = a[j]
	a[j] = tmp
}

// Tests the Selection Sort algorithm.
func selectionSortTest() {
	var array []int

	array = make([]int, arrayLength)

	// Build the input array.
	for i := 0; i < arrayLength; i += 2 {
		array[i] = arrayLength - i
		array[i+1] = i + 1
	}

	fmt.Println(array)

	selectionSort(array)

	fmt.Println(array)
}

// Tests the Insertion Sort algorithm.
func insertionSortTest() {

	array := make([]int, arrayLength)

	// Build the input array.
	for i := 0; i < arrayLength; i += 2 {
		array[i] = arrayLength - i
		array[i+1] = i + 1
	}

	fmt.Println(array)

	insertionSort(array)

	fmt.Println(array)
}

// Tests the Heapsort algorithm.
func heapsortTest() {
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

// Tests the Counting Sort algorithm.
func countingSortTest() {
	var array []int

	array = make([]int, arrayLength)

	// Build the input array.
	for i := 0; i < arrayLength; i += 2 {
		array[i] = arrayLength - i
		array[i+1] = i + 1
	}

	fmt.Println(array)

	countingSort(array)

	fmt.Println(array)
}

// Tests the Mergesort algorithm.
func mergesortTest() {
	var array []int

	array = make([]int, arrayLength)

	// Build the input array.
	for i := 0; i < arrayLength; i += 2 {
		array[i] = arrayLength - i
		array[i+1] = i + 1
	}

	fmt.Println(array)

	mergesort(array)

	fmt.Println(array)
}

func Test() {
	countingSortTest()
	heapsortTest()
	insertionSortTest()
	mergesortTest()
	selectionSortTest()
}
