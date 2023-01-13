# Selection Sort

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

O _Selection Sort_ (Ordenação por Seleção) é um algoritmo de ordenação que
funciona selecionando o menor elemento de um arranjo e colocando-o na primeira
posição, depois selecionando o segundo menor elemento e colocando-o na segunda
posição, e assim sucessivamente até que o arranjo esteja ordenado.

## Algoritmo

1. Particione o arranjo de elementos a ser ordenada em dois sub-arranjos: (i) um
sub-arranjo $A$ inicialmente vazio que contém os elementos já ordenados, e (ii)
um sub-arranjo $B$ com inicialmente todos os elementos do arranjo original.
2. Selecione o menor elemento da sub-arranjo $B$ e coloque-o na última posição
do sub-arranjo $A$.
3. Se o sub-arranjo $B$ não estiver vazio, volte ao Passo 2.
4. Retorne o sub-arranjo $A$, que contém os elementos do arranjo original
ordenados de forma ascendente.

## Desempenho

- Melhor Caso: $O(n^2)$ comparações, $O(1)$ trocas.
- Pior Caso: $O(n^2)$ comparações, $O(n)$ trocas.

## Leitura Complementar

- [Desenvolvendo Software](http://desenvolvendosoftware.com.br/algoritmos/ordenacao/selection-sort.html)
- [Wikipédia](https://pt.wikipedia.org/wiki/Selection_sort)
