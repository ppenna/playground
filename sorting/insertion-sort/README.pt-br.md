# Insertion Sort

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é o _Insertion Sort_?](#o-quê-é-o-insertion-sort)
- [Quais são as características do _Insertion Sort_?](#quais-são-as-características-do-insertion-sort)
- [Qual é o algoritmo de _Insertion Sort_?](#qual-é-o-algoritmo-de-insertion-sort)
- [Qual é o desempenho do _Insertion Sort_?](#qual-é-o-desempenho-do-insertion-sort)
- [Leitura Complementar](#leitura-complementar)

## O quê é o _Insertion Sort_?

O _Insertion Sort_ (Ordenação por Inserção) é um algoritmo de ordenação que funciona de forma similar ao modo como algumas pessoas ordenam cartas de um baralho, quando estão jogando. Ao adicionar uma nova carta a uma mão de cartas ordenadas, o jogador compara a nova carta com todas as demais cartas em sua mão, para determinar o ponto de inserção adequado.

## Quais são as características do _Insertion Sort_?

- O _Insertion Sort_ é um algoritmo iterativo.
- O _Insertion Sort_ é um algoritmo de ordenação por comparação.
- O _Insertion Sort_ é um algoritmo de ordenação estável.
- O desempenho do algoritmo _Insertion Sort_ é muito sensível aos dados de entrada.
- O _Insertion Sort_ necessita de uma estrutura de dados auxiliar para funcionar.

## Qual é o algoritmo de _Insertion Sort_?

1. Particione o arranjo de entrada em dois:
   - Um sub-arranjo `A` que inicialmente contém apenas o primeiro elemento do arranjo original.
   - Um sub-arranjo `B` que inicialmente contém todos os demais elementos.
2. Considere o primeiro elemento do sub-arranjo `B`. Denote este elemento `x`.
3. Procure no sub-arranjo `A` o ponto onde `x` deve ser inserido, da direita para a esquerda.
4. Desloque uma posição para a direita, todos os elementos no sub-arranjo `A` que estão à direita do ponto de inserção.
5. Insira o elemento `x` na posição de inserção encontrada no sub-arranjo `A`.
6. Se o sub-arranjo `B` não estiver vazio, volte ao Passo 2.
7. Retorne o sub-arranjo `A`, que contém os elementos da arranjo original ordenados.

## Qual é o desempenho do _Insertion Sort_?

### Pior Caso

O pior caso para o algoritmo _Insertion Sort_ ocorre quando a lista de elementos está ordenada de forma inversa. Nessa situação, o algoritmo te um custo quadrático de comparações e de trocas, em função do número de elementos `n` a serem ordenados:

- `O(n²)` comparações
- `O(n²)` trocas

### Melhor Caso

O melhor caso para o algoritmo _Insertion Sort_ ocorre quando a lista de elementos já está ordenada. Nessa situação, o algoritmo tem um custo linear de comparações e um custo constante de trocas, em função do número de elementos `n` a serem ordenados:

- `O(n)` comparações
- `O(1)` trocas

## Leitura Complementar

- [Desenvolvendo Software | Insertion Sort](http://desenvolvendosoftware.com.br/algoritmos/ordenacao/insertion-sort.html)
