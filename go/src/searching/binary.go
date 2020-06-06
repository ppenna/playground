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

package main

import "fmt"

// Length of Array
const arrayLength = 32

// Searches an element in an array.
func binarySearch(array []int, value int) int {
	var search func(int, int) int

	// Search.
	search = func(l, r int) int {
		// End recursion.
		if (r - l) < 0 {
			return -1
		}

		m := (r - l) / 2

		// Found.
		if array[l+m] == value {
			return l + m
		}

		// Recur.
		if value < array[l+m] {
			r = l + m
		} else if value > array[l+m] {
			l += m
		}
		return search(l, r)
	}

	return search(0, len(array))
}

// Tests the Linear Search algorithm.
func main() {
	array := make([]int, arrayLength)

	// Build the input array.
	for i := 0; i < arrayLength; i++ {
		array[i] = i
	}

	fmt.Println(array)

	idx := binarySearch(array, 19)

	fmt.Println(idx)
}
