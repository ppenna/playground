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

package text

import (
	"fmt"
)

// Length of Alphabet
const alphabetLength = 256

// Searches a pattern in a text.
func BMHSearch(text, pattern string) int {
	var jmptable []int = make([]int, alphabetLength)

	// Initialize table of jumps.
	for i := 0; i < alphabetLength; i++ {
		jmptable[i] = len(pattern) + 1
	}
	for i := 0; i < len(pattern); i++ {
		jmptable[pattern[i]] = len(pattern) - i
	}

	// Iterate on the text.
	p := 0
	for i := 0; (i + len(pattern)) <= len(text); {
		// Iterate on the pattern.
		for j := len(pattern) - 1; j >= 0; j-- {
			// Mismatch, thus reset search.
			if text[i+(len(pattern)-p-1)] != pattern[j] {
				p = 0
				i += jmptable[text[i+len(pattern)]]
				break
			}

			p++
		}

		// Found.
		if p == len(pattern) {
			return i
		}
	}

	// Not found.
	return -1
}

// Tests the BHM Search algorithm.
func Test() {
	text := "hello world"
	pattern := "world"

	fmt.Printf("%d: %s\n", BMHSearch(text, pattern), pattern)
}
