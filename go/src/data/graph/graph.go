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

package graph

import (
	"fmt"
)

/*============================================================================*
 * Graph                                                                      *
 *============================================================================*/

// Graph Operations
type Graph interface {
	Init(int)
	Add(int)
	Remove(int)
	Link(int, int)
	Unlink(int, int)
}

// Graph Data
type GraphMatrix struct {
	nvertices int
	neighbors [][]bool
}

/*============================================================================*
 * vertexIsValid()                                                            *
 *============================================================================*/

// Asserts if a vertex number is valid.
func (g *GraphMatrix) vertexIsValid(v int) bool {
	return (v >= 0) && (v < g.nvertices)
}

/*============================================================================*
 * Init()                                                                     *
 *============================================================================*/

// Initializes a graph.
func (g *GraphMatrix) Init(nvertices int) {
	g.nvertices = nvertices
	g.neighbors = make([][]bool, nvertices)
}

/*============================================================================*
 * Add()                                                                      *
 *============================================================================*/

// Adds a vertex to a graph.
func (g *GraphMatrix) Add(v int) {
	g.neighbors[v] = make([]bool, g.nvertices)
}

/*============================================================================*
 * Remove()                                                                   *
 *============================================================================*/

// Removes a vertex from a graph.
func (g *GraphMatrix) Remove(v int) {

	// Unlink this vertex.
	for i := range g.neighbors {

		// Skip invalid vertices.
		if g.neighbors[i] == nil {
			continue
		}

		g.neighbors[i][v] = false
	}

	// Release underlying memory.
	g.neighbors[v] = nil
}

/*============================================================================*
 * Link()                                                                     *
 *============================================================================*/

// Links two vertices in a graph.
func (g *GraphMatrix) Link(u, v int) {
	g.neighbors[u][v] = true
	g.neighbors[v][u] = true
}

/*============================================================================*
 * Unlink()                                                                   *
 *============================================================================*/

// Unlinks two vertices in a graph.
func (g *GraphMatrix) Unlink(u, v int) {
	g.neighbors[u][v] = false
	g.neighbors[v][u] = false
}

/*============================================================================*
 * Print()                                                                    *
 *============================================================================*/

// Unlinks two vertices in a graph.
func (g *GraphMatrix) Print() {
	for i := range g.neighbors {

		// Skip invalid vertices.
		if g.neighbors[i] == nil {
			continue
		}

		fmt.Println(g.neighbors[i])
	}
}

/*============================================================================*
 * Main()                                                                     *
 *============================================================================*/

func Test() {
	var g GraphMatrix

	g.Init(10)

	for i := 0; i < 10; i++ {
		g.Add(i)
	}

	for i := 0; i < 10; i += 2 {
		g.Link(i, i+1)
	}

	g.Print()
}
