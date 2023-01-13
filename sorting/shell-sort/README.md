# Shell`s Sort

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Read this in other languages: [English](README.md), [Português](README.pt-br.md)_

- [What is Shell Sort?](#what-is-shell-sort)
- [When to use Shell Sort?](#when-to-use-shell-sort)
- [What are the features of Shell Sort?](#what-are-the-features-of-shell-sort)
- [What is the Shell Sort algorithm?](#what-is-the-shell-sort-algorithm)
- [What interval sequence to use in Shell Sort?](#what-interval-sequence-to-use-in-shell-sort)
- [What is the performance of Shell Sort?](#what-is-the-performance-of-shell-sort)

## What is Shell Sort?

Shell Sort is a comparison-based sorting algorithm created by Donald Shell in 1959. The algorithm is based on the Insertion Sort algorithm and works as follows.

Initially, the collection is divided into several subgroups, such that all elements of a subgroup are at the same interval `h` from each other. Then, each subgroup is reordered using the Insertion Sort algorithm. Finally, the value of interval `h` is reduced, new subgroups are created and the process is repeated until the size of interval `h` is `1`.

## When to use Shell Sort?

- Shell Sort is suitable for sorting small collections.
- Shell Sort is suitable for sorting collections that are partially sorted.
- Shell Sort can be used when auxiliary memory space is non-existent or limited.
- Shell Sort can be used when a stable sorting is required.

## What are the features of Shell Sort?

- Shell Sort is a comparison-based algorithm.
- Shell Sort is based on the Insertion Sort algorithm.
- Shell Sort is in-place, meaning it does not require auxiliary memory space to sort the collection.
- Shell Sort is stable, meaning it maintains the relative order of elements that have equal values.
- The performance of Shell Sort is greatly impacted by how the elements are initially arranged in the input collection.

## What is the Shell Sort algorithm?

1. Choose an initial interval `h`.
2. Divide the collection into several subgroups, such that elements in the same subgroup are a distance `h` apart from each other.
3. Sort each subgroup using the Insertion Sort algorithm.
4. Decrease the value of interval `h` and repeat Steps 2 and 3 until the interval `h` is greater than `0`.
5. The collection is sorted.

## What interval sequence to use in Shell Sort?

- Shell sequence -- `h = n/2ᵏ`, where `n` is the size of the collection and `k` is the step in the Shell Sort algorithm. This sequence makes the algorithm have a quadratic performance `O(n²)` in the worst case.
- Hibbard sequence -- `h = 2ᵏ - 1`, where `k` is the step in the Shell Sort algorithm. This sequence makes the algorithm have a sub-quadratic performance `O(n³⁄₂)` in the worst case.
- Knuth sequence -- `h = (3ᵏ - 1) / 2`, where `k` is the step in the Shell Sort algorithm. This sequence makes the algorithm have a sub-quadratic performance `O(n³⁄₂)` in the worst case.

## What is the performance of Shell Sort?

### Best-Case

The performance in the best case for the Shell Sort algorithm occurs when the input collection is partially sorted. In this scenario, the algorithm has a super-linear cost of comparisons, based on the number of elements `n` in the collection:

- `O(n log₂ n)` comparisons

### Worst-Case

The worst-case performance of the Shell Sort algorithm occurs when the input collection is sorted in reverse order. In this scenario, the algorithm has a quadratic cost of comparisons, based on the number of elements n in the collection:

- `O(n²)` comparisons
