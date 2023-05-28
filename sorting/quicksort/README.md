# Quicksort

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Read this in other languages: [English](README.md), [Português](README.pt-br.md)_

Quicksort is an efficient comparison sort algorithm devised by Tony Hoare in
1959. It features a Divide and Conquer design, and works by recursively
partitioning and reordering the input array according to a _pivot_ element.

Quicksort presents a slightly better performance than other comparison sort
algorithms such as Merge Sort and Heapsort.

Quicksort presents quadratic complexity when dealing with an array filled with
duplicate keys. It can be modified by using a 3 way partitioning algorithm,
making this case linear instead.

## Algorithm

1. If the array is shorter than two elements, stop recursing.
2. Select an element in the array and call it the _pivot_ element.
3. Partition and reorder the array into two sub-arrays, such that the elements
that are less than the _pivot_ come before the division point and elements
greater than the _pivot_ come after it. Elements that equal the _pivot_ can be
placed on either of the partitions.
4. Recursively apply Steps 1 -- 3 in the the left and right sub-arrays.
5. When the recursion ends, the array is sorted.

For dealing with duplicate keys, step 3 uses 3 sub-arrays instead, such that the
elements that are less than the _pivot_ are placed in the first sub-array, the
duplicate keys are palced in the second sub-array, and the elements greater than
the _pivot_ are placed in the third sub-array.

## Performance

- Best-Case: $O(n \log_2 n)$ comparisons
- Worst-Case: $O(n^2)$ comparisons

## Further Reading

- [Desenvolvendo Software](http://desenvolvendosoftware.com.br/algoritmos/ordenacao/quicksort.html) (Portuguese)
- [Wikipedia](https://en.wikipedia.org/wiki/Quicksort)
