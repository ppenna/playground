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
func linearSearch(array []int, value int) int {
	for i := range array {
		if array[i] == value {
			return i
		}
	}

	return (-1)
}

// Tests the Linear Search algorithm.
func main() {
	array := make([]int, arrayLength)

	// Build the input array.
	for i := 0; i < arrayLength; i += 2 {
		array[i] = arrayLength - i
		array[i+1] = i + 1
	}

	fmt.Println(array)

	idx := linearSearch(array, 19)

	fmt.Println(idx)
}
