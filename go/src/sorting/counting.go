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

// Maximum Number for an Integer
const maxInt = int(^uint(0) >> 1)
const minInt = -maxInt - 1

// Finds the smallest and biggest elements of an array.
func findMinMax(array []int) (int, int) {

	min := maxInt
	max := minInt

	// Search the smallest element.
	for i := range array {

		// Smallest element found.
		if array[i] < min {
			min = array[i]
		}

		// Biggest element found.
		if array[i] > max {
			max = array[i]
		}
	}

	return min, max
}

// Sorts an array.
func countingSort(array []int) {

	min, max := findMinMax(array)

	sortedArray := make([]int, max-min+1)

	// Count numbers.
	for i := range array {
		sortedArray[array[i]-min]++
	}

	// Rebuild array.
	k := 0
	for i := range sortedArray {
		for j := 0; j < sortedArray[i]; j++ {
			array[k] = min + i
			k++
		}
	}
}
