# Queue

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Read this in other languages: [English](README.md), [Português](README.pt-br.md)_

## What is a Disjoint Set?

A Disjoint Set is a data structure that maintains a collection of elements, which are partitioned into multiple non-overlapping sets. This data structure enables elements to be grouped and partitioned into sets efficiently.

## What are the applications for a Disjoint Set?

- In Kruskal's algorithm, a Disjoint Set may be used to keep track of the connected components of the graph, and to check whether or not adding an edge in an iteration of the algorithm would violate the properties of the minimal spawning tree under construction.
- In image segmentation problems, a Disjoint Set may be used to keep track of the connections between the pixels of an image, as well as allowing pixels to be grouped into regions with similar properties.
- In machine learning algorithms, a Disjoint Set may be used to group data into sets based on its characteristics and then aid in the training process.

## Who to implement a Disjoint Set?

- **Using a collection of chained lists**, with linked each list representing a disjoint set. This implementation is easy to understand and only supports the `union` operation efficiently.
- **Using a collection of trees**, with each tree representing a disjoint set. This implementation is more complex to understand, but supports 'join' and 'union' operations efficiently.

## What are the main operations of a Disjoint Set?

- `union` merges two sets into a single one.
- `find` identifies to which set a given element belongs.

### Union Operation

1. Find the set `X` to which element `x` belongs (`find` operation).
2. Find the set `Y` to which element `y` belongs (`find` operation).
3. Remove all elements from `Y` and place them into `X`.

### Find Operation

1. Pick up an arbitrary set `X` in the disjoint set.
2. Traverse all elements of `X` and check if any of them is the element being searched for.
3. If the searched element is found, return `X`.
4. If all elements of `X` were inspected, but none matches the element being searched, take another set `Y` which has not yet being considered, make `X = Y`, and repeat Steps 1 to 4.
5. If the searched element was not found, return `"element not found"`.
