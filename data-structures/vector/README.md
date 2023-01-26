# Vector

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Read this in other languages: [English](README.md), [Português](README.pt-br.md)_

- [What is a vector?](#what-is-a-vector)
- [Where are vectores used?](#where-are-vectores-used)
- [How to implement a vector?](#how-to-implement-a-vector)
- [What are the basic operations in a vector?](#what-are-the-basic-operations-in-a-vector)

## What is a vector?

A vector is a linear data structure that efficiently supports random access to any of its elements. To do this, the elements of a vector must all have the same type and be stored contiguously in memory. Thus, an element can be uniquely indexed from its relative position in this data structure.

An analogy for vectors are staircases. Several steps of the same size are arranged contiguously and a step can be uniquely identified by its relative position to the first step of the staircase.

## Where are vectores used?

- To implement other data structures, such as Stacks and Queues.

## How to implement a vector?

A vector `v` can be constructed with the following components:

- `v.elements[]`: an array that stores the elements of the vector.
- `v.length`: an integer that indicates the number of elements stored in the vector.
- `v.capacity`: an integer that indicates the maximum number of elements that can be stored in the vector.

## What are the basic operations in a vector?

- [`insert()` inserts an element in a vector.](#insert-operation)
- [`remove()` removes an element from a vector.](#remove-operation)

### Insert Operation

1. If the length of the vector `v.length` is equal to its capacity `v.capacity`, expand the capacity of the vector.
2. Increment the length of the vector `v.length` by one.
3. Shift all elements of the vector `v` that are to the right of the insertion index `i` one position to the right.
4. Store the element `x` at position `i` of the vector `v`.

### Remove Operation

1. If the removal index `i` is greater than the length of the vector `v.length`, return `"invalid index"`.
2. Save in `x` the element stored at position `i` of the vector `v`.
3. Shift all elements of the vector `v` that are to the right of the removal index `i` one position to the left.
4. Decrement the length of the vector `v.length` by one.
5. Return the element `x`.
