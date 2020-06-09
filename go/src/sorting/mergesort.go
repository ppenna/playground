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

// Sorts an array.
func mergesort(array []int) {
	aux := make([]int, len(array))
	var sort func(int, int)

	// Rebuild array.
	rebuild := func(l, r int) {
		for i := l; i < r; i++ {
			array[i] = aux[i]
		}
	}

	// Merge
	merge := func(l, m, r int) {
		k := l
		p := l + m
		for i := l; i < r; i++ {
			if (p >= r) || ((k < l+m) && (array[k] < array[p])) {
				aux[i] = array[k]
				k++
			} else {
				aux[i] = array[p]
				p++
			}
		}
	}

	// Sort.
	sort = func(l, r int) {

		// Swap?
		if (r - l) < 2 {
			return
		}

		// Recur.
		m := (r - l) / 2
		sort(l, l+m)
		sort(l+m, r)

		// Build solution.
		merge(l, m, r)
		rebuild(l, r)
	}

	sort(0, len(array))
}
