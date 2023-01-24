# Exponential Search

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Read this in other languages: [English](README.md), [Português](README.pt-br.md)_

- [About](#about)
- [Properties](#properties)
- [Algorithm](#algorithm)
- [Performance](#performance)
- [Further Reading](#further-reading)

## What is Exponential Search?

Exponential Search is a search algorithm created by Jon Bentley and Andrew Chi-Chih Yao in 1976 that is able to search for elements in an unlimited ordered array (an array that has an unknown upper limit). The algorithm consists of a combination of the Sequential Search and Binary Search algorithms, using the first algorithm to restrict the search space and the second algorithm to effectively search for the desired element.

## When to use Exponential Search?

- Exponential Search should be used when you want to search in an unlimited ordered array (the upper limit of the array is unknown).
- Exponential Search should be used when you estimate that the searched element is close to the beginning of the array.

## What are the properties of the Exponential Search?

- Exponential Search is a hybrid algorithm, which combines the Sequential Search and Binary Search.
- Exponential Search works only on ordered arrays.
- Exponential Search works on unlimited arrays.
- The performance of Exponential Search is very sensitive to the searched element.

## What is the Exponential Search algorithm?

1. Define the initial variables `i` as `1` and `n` as the length of the array.
2. While `i` is less than `n` and the element at index `i` is less than the searched element, double the value of `i`.
3. Perform a Binary Search in the range from `i/2` to `min(n, i)`.
4. Return the result of the Binary Search.

### Best-Case

The best case of the Exponential Search algorithm occurs when the searched element is the first considered element. In this scenario, the algorithm has a constant cost of comparisons:

- `O(1)` comparisons

### Worst-Case

The worst case of the Exponential Search algorithm occurs when the searched element is not present in the input array. In this scenario, the algorithm has a logarithmic cost of comparisons, in relation to the number of elements n in the array:

- `O(log₂ n)` comparisons

## Further Reading

- [Wikipedia](https://en.wikipedia.org/wiki/Exponential_search)
