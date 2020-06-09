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

import (
	"fmt"
)

// Matrix
type Matrix struct {
	m, n     int
	elements [][]float64
}

// Creates a matrix.
func New(n, m int) *Matrix {
	matrix := new(Matrix)

	matrix.m = m
	matrix.n = n

	// Allocate data.
	matrix.elements = make([][]float64, m)
	for i := range matrix.elements {
		matrix.elements[i] = make([]float64, n)
	}

	return matrix
}

// Multiplies two matrices.
func Mult(a, b *Matrix) *Matrix {
	c := New(a.m, b.n)
	for i := 0; i < a.m; i++ {
		for j := 0; j < b.n; j++ {
			for k := 0; k < a.n; k++ {
				c.elements[i][j] = a.elements[i][k] * b.elements[k][j]
			}
		}
	}

	return c
}

// Transposes a matrix.
func (a *Matrix) Transpose() *Matrix {
	b := New(a.m, a.n)
	for i := 0; i < a.m; i++ {
		for j := 0; j < a.n; j++ {
			b.elements[i][j] = a.elements[j][i]
		}
	}

	return b
}

// Prints a matrix
func (matrix *Matrix) Print() {
	for i := 0; i < matrix.m; i++ {
		fmt.Println(matrix.elements[i])
	}
}

// Tests Matrix algorithms
func main() {
	a := New(3, 3)
	b := New(3, 3)
	a.Print()
	fmt.Println(a.m, a.n)

	for i := 0; i < a.m; i++ {
		for j := 0; j < a.n; j++ {
			a.elements[i][j] = float64(i)
		}
	}

	a.Print()

	for i := 0; i < b.m; i++ {
		for j := 0; j < b.n; j++ {
			b.elements[i][j] = 1.0
		}
	}

	b.Print()

	c := Mult(a, b)

	c.Print()

	c = a.Transpose()

	c.Print()
}
