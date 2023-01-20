# Vector

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê são vetores?](#o-quê-são-vetores)
- [Onde vetores são usados?](#onde-vetores-são-usados)
- [Qual é a estrutura de um vetor?](#qual-é-a-estrutura-de-um-vetor)
- [Quais são as operações básicas de um vetor?](#quais-são-as-operações-básicas-de-um-vetor)

## O quê são vetores?

Um vetor é uma estrutura de dados linear que suporta de forma eficiente o acesso
aleatório a qualquer um de seus elementos. Para isso, os elementos de um vetor
devem todos possuir o mesmo tipo e serem armazenados de forma contígua em
memória. Assim, um elemento pode ser unicamente indexado a partir de sua posição
relativa nessa estrutura de dados.

Uma analogia para vetores são as escadas. Vários degraus de mesmo tamanho são
dispostos contiguamente e um degrau pode ser unicamente identificado pela sua
posição relativa ao primeiro degrau da escada.

## Onde vetores são usados?

- Na implementação de outras estruturas de dados como Pilhas e Filas.

## Qual é a estrutura de um vetor?

Um vetor `v` pode ser construído com os seguintes componentes:

- `v.elementos[]`: um arranjo que armazena os elementos do vetor.
- `v.comprimento`: um inteiro que indica o número de elementos armazenados no vetor.
- `v.capacidade`: um inteiro que indica o número máximo de elementos que podem ser armazenados no vetor.

## Quais são as operações básicas de um vetor?

- [`inserir()` insere um elemento em um vetor.](#operação-inserir)
- [`remover()` remove um elemento de um vetor.](#operação-remover)

### Operação Inserir

1. Se o comprimento do vetor `v.comprimento` é igual a sua capacidade `v.capacidade`, expanda a capacidade do vetor.
2. Incremente em uma unidade o comprimento do vetor `v.comprimento`.
3. Desloque em uma posição para a direita, todos os elementos do vetor `v` que estão à direita do índice de inserção `i`.
4. Armazene o elemento `x` na posição `i` do vetor `v`.

### Operação Remover

1. Se o índice de remoção `i` é maior que o comprimento do vetor `v.comprimento`, retorne `"índice inválido"`.
2. Salve em `x` o elemento armazenado na posição `i` do vetor `v`.
3. Desloque em uma posição para a esquerda, todos os elementos do vetor `v` que estão à direita do índice de remoção `i`.
4. Decremente em uma unidade o comprimento do vetor `v.comprimento`.
5. Retorne o elemento `x`.
