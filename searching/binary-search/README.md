# Binary Search

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Read this in other languages: [English](README.md), [Português](README.pt-br.md)_

- [About](#about)
- [Properties](#properties)
- [Algorithm](#algorithm)
- [Performance](#performance)
- [Further Reading](#further-reading)

## About

Binary Search is a search algorithm that looks for a particular element in a sorted array. It works by repeatedly dividing the search interval in half and checking if the target element is in the middle of the current interval. If the desired element is smaller than the middle one, a recursive search is performed on the lower half of the array. If the desired element is greater than the element in the middle, a recursive search is performed on the upper half of the array. This process continues until the desired element is found, or there are no more elements to search.

## Properties

- It is a Divide and Conquer algorithm.
- It works only on sorted arrays.

## Algorithm

1. Consider as the initial search range, the full length of the input array.
2. If the search range is empty, stop. The target element is not in the input array.
3. Compare the target element with the element in the middle of the search range.
4. If the target element matches with the mid element, stop. The target element was found.
5. Else if the the target element is smaller than the mid element, take the sub-range to the left of the mid element as the new search range and go to Step 2.
6. Else if the target element is greater than the mid element, take the sub-range to the right of the mid element as the new search range and go to Step 2.

## Performance

### Best-Case

The best-case scenario for the Binary Search algorithm occurs when the desired element is the first element considered. In this scenario, the algorithm has a constant cost of comparisons, in respect to the number of elements `n` in the array:

- `O(1)` comparisons

### Worst-Case

The worst case scenario for the Binary Search algorithm occurs when the desired element is not present in the input array. In this scenario, the algorithm has a logarithmic cost of comparisons, in respect to the number of elements `n` in the array:

- `O(log₂ n)` comparisons

## Further Reading

- [Wikipedia](https://en.wikipedia.org/wiki/Binary_search_algorithm)
