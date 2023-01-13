# Selection Sort

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Read this in other languages: [English](README.md), [Português](README.pt-br.md)_

Selection Sort is a sorting algorithm that works by selecting the smallest
element in the array and placing it in the first position, then selecting the
second smallest element in the array and placing it in the second position, and
so on until the array is sorted.

## Algorithm

1. Partition the input array in two sub-arrays: a sub-array $A$ that is
initially empty and will store all elements in their sorted order; and a
sub-array $B$ with initially all elements from the input array.
2. Select the smallest element from the sub-array $B$ and place it in the last
position of sub-array $A$.
3. If sub-array $B$ is not empty, go to Step 2.
4. Return sub-array $A$, which contains all elements from the original array
sorted.

## Performance

- Best-Case: $O(n^2)$ comparisons, $O(1)$ swaps.
- Worst-Case: $O(n^2)$ comparisons, $O(n)$ swaps.

## Further Reading

- [Desenvolvendo Software](http://desenvolvendosoftware.com.br/algoritmos/ordenacao/selection-sort.html) (Portuguese)
- [Wikipedia](https://en.wikipedia.org/wiki/Selection_sort)
