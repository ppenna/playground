# Selection Sort

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é o _Selection Sort_?](#o-quê-é-o-selection-sort)
- [Quais são as características do _Selection Sort_?](#quais-são-as-características-do-selection-sort)
- [Qual é o algoritmo do _Selection Sort_?](#qual-é-o-algoritmo-do-selection-sort)
- [Qual é o desempenho do _Selection Sort_?](#qual-é-o-desempenho-do-selection-sort)
- [Quando usar o _Selection Sort_?](#quando-usar-o-selection-sort)
- [Leitura Complementar](#leitura-complementar)

## O quê é o _Selection Sort_?

O _Selection Sort_ (Ordenação por Seleção) é um algoritmo de ordenação que funciona selecionando o menor elemento de um arranjo e colocando-o na primeira posição, depois selecionando o segundo menor elemento e colocando-o na segunda posição, e assim sucessivamente até que o arranjo esteja ordenado.

## Quais são as características do _Selection Sort_?

- O _Selection Sort_ é um algoritmo iterativo.
- O _Selection Sort_ é um algoritmo de ordenação por comparação.
- O _Selection Sort_ não é um algoritmo de ordenação estável.
- O desempenho do algoritmo _Selection Sort_ não é sensível aos dados de entrada.
- O _Selection Sort_ não necessita de uma estrutura de dados auxiliar para funcionar.

## Qual é o algoritmo do _Selection Sort_?

1. Particione o arranjo de elementos a ser ordenado em dois sub-arranjos: (i) um sub-arranjo `A` inicialmente vazio que contém os elementos já ordenados, e (i) um sub-arranjo `B` com inicialmente todos os elementos do arranjo original.
2. Selecione o menor elemento da sub-arranjo `B` e coloque-o na última posição do sub-arranjo `A`.
3. Se o sub-arranjo `B` não estiver vazio, volte ao Passo 2.
4. Retorne o sub-arranjo `A`, que contém os elementos do arranjo original ordenados de forma ascendente.

## Qual é o desempenho do _Selection Sort_?

### Pior Caso

O pior caso para o algoritmo _Selection Sort_ ocorre quando o arranjo de elementos já está ordenado de forma inversa. Nessa situação, o algoritmo tem um custo quadrático de comparações e um custo linear de trocas, em função do número de elementos a serem ordenados:

- `O(n²)` comparações
- `O(n)` trocas

### Melhor Caso

O melhor caso para o algoritmo _Selection Sort_ ocorre quando o arranjo de elementos já está ordenado. Nessa situação, o algoritmo tem um custo quadrático de comparações e um custo constante de trocas, em função do número de elementos a serem ordenados:

- `O(n²)` comparações
- `O(1)` trocas

## Quando usar o _Selection Sort_?

O _Selection Sort_ se destaca em relação aos outros algoritmos de ordenação em dois pontos: (i) por realizar um número mínimo de trocas, e (ii) não necessitar de uma estrutura de dados auxiliar para funcionar.

Por esses motivos, o _Selection Sort_ é indicado para a ordenação de arranjos quando memória extra disponível para uso é escassa, ou então o custo para trocar-se elementos de posição no arranjo é elevado.

## Leitura Complementar

- [Desenvolvendo Software | Selection Sort](http://desenvolvendosoftware.com.br/algoritmos/ordenacao/selection-sort.html)
