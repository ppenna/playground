# Counting Sort

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Read this in other languages: [English](README.md), [Português](README.pt-br.md)_

Counting Sort is an integer sorting algorithm devised by Harold Seward in 1954.
It works by building a cumulative histogram of the keys in the input array, and
then using that histogram to construct a sorted output array.

In its classical definition, Counting Sort assumes that keys have non-negative
values and the value of the maximum key is known in advance. Counting Sort is
generally used as a sub-routine for other non-comparison sorting methods such as
Radix Sort and Bucket Sort.

## Algorithm

1. Build the cumulative histogram $h$ of the keys in the input array. In this
auxiliary data structure, the first bin gives the frequency of keys with value
0, the second bin gives the frequency of keys with value 1 plus the value of
stored in the previous bin, and so on.
2. Construct a sorted output array using the cumulative histogram to determine
the right position of elements. For instance, let $x$ bee an arbitrary element
in the input array that has a key $k$, and $h(k)$ be the cumulative frequency
for key $k$. Thus, $x$ should be placed in the output array in the range from
$h(k)$ to $h(k+1)$.

## Performance

- Best-Case:  $O(n + k)$
- Worst-Case: $O(n + k)$

## Further Reading

- [Desenvolvendo Software](http://desenvolvendosoftware.com.br/algoritmos/ordenacao/counting-sort.html) (Portuguese)
- [Wikipedia](https://en.wikipedia.org/wiki/Counting_sort)
