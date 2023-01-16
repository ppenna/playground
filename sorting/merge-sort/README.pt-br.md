# Merge Sort

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é o _Merge Sort_?](#o-quê-é-o-merge-sort)
- [Quando usar o _Merge Sort_?](#quando-usar-o-merge-sort)
- [Quais são as características do _Merge Sort_?](#quais-são-as-características-do-merge-sort)
- [Qual é o algoritmo do _Merge Sort_?](#qual-é-o-algoritmo-do-merge-sort)
- [Qual é o desempenho do _Merge Sort_?](#qual-é-o-desempenho-do-merge-sort)
- [Leitura Complementar](#leitura-complementar)

## O quê é o _Merge Sort_?

O _Merge Sort_ (Ordenação por Mesclagem) é um algoritmo de ordenação por comparação criado por John von Neumann em 1945. O algoritmo funciona dividindo a coleção de elementos em duas sub-coleções, ordenando de forma recursiva cada sub-coleção e, em seguida, combinando as duas subcoleções.

## Quando usar o _Merge Sort_?

- O _Merge Sort_ pode ser usado para ordenar coleções grandes
- O _Merge Sort_ pode ser usado quando uma ordenação estável é necessária.

## Quais são as características do _Merge Sort_?

- O _Merge Sort_ é um algoritmo de Divisão e Conquista.
- O _Merge Sort_ é um algoritmo de ordenação por comparação.
- O _Merge Sort_ é um algoritmo de ordenação estável.
- O _Merge Sort_ pode ser usado para ordenar arranjos e listas.
- O desempenho do merge sort não depende da disposição dos dados na coleção de entrada.

## Qual é o algoritmo do _Merge Sort_?

1. Verifique se a coleção possui apenas um elemento. Em caso afirmativo, retorne.
2. Divida a coleção em duas subcoleções.
3. Ordene recursivamente cada subcoleção.
4. Combine as duas subcoleções ordenadas em uma única.
5. Retorne a coleção ordenada.

## Qual é o desempenho do _Merge Sort_?

O desempenho do algoritmo _Merge Sort_ não é impactado pela disposição dos dados no arranjo de entrada. Assim, o algoritmo apresenta tanto no pior caso quanto melhor caso um custo super-linear de comparações, em função do comprimento `n` do arranjo de entrada:

- `O(n log₂ n)` comparações

## Leitura Complementar

- [Desenvolvendo Software | Merge Sort](http://desenvolvendosoftware.com.br/algoritmos/ordenacao/merge-sort.html)
