# Busca por Interpolação

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O que é a Busca por Interpolação?](#o-que-é-a-busca-por-interpolação)
- [Quando usar a Busca por Interpolação?](#quando-usar-a-busca-por-interpolação)
- [Quais as características da Busca por Interpolação?](#quais-as-características-da-busca-por-interpolação)
- [Qual o algoritmo da Busca por Interpolação?](#qual-o-algoritmo-da-busca-por-interpolação)
- [Qual o desempenho da Busca por Interpolação?](#qual-o-desempenho-da-busca-por-interpolação)

## O que é a Busca por Interpolação?

A Busca por Interpolação (_Interpolation Search_) é um algoritmo de busca criado por William Wesley Peterson em 1957 capaz de procurar um elemento específico em um arranjo ordenado. O algoritmo consiste em uma variação do algoritmo de Busca Binária, usando uma técnica de interpolação para reduzir o número de iterações necessárias para encontrar o elemento desejado. O método de interpolação empregado pode levar em consideração a característica dos dados no arranjo de busca, mas frequentemente um método de interpolação linear é escolhido.

## Quando usar a Busca por Interpolação?

- A Busca por Interpolação é indicada quando sabe-se que existe uma distribuição uniforme dos elementos no arranjo de busca. Nesse caso, o desempenho médio do algoritmo é de `O(log₂ (log₂ n))` onde `n` é o comprimento do arranjo de busca.

## Quais as características da Busca por Interpolação?

- A Busca por Interpolação é uma variação da Busca Binária.
- A Busca por Interpolação funciona apenas em arranjos ordenados.
- O desempenho da Busca por Interpolação é sensível aos elementos no arranjo de busca.

## Qual o algoritmo da Busca por Interpolação?

1. Inicialmente, considere como intervalo de busca todo o arranjo de busca.
2. Caso o intervalo de busca for vazio, pare. O elemento desejado não está no arranjo de busca.
3. Estime a posição do elemento desejado usando um método de interpolação (ex: interpolação linear).
4. Compare o elemento desejado com o elemento na posição interpolada.
5. Se o elemento desejado for o que estiver na posição interpolada, pare. O elemento desejado foi encontrado.
6. Senão, se o elemento desejado for maior do que o elemento na posição interpolada, considere o intervalo à esquerda do elemento na posição interpolada como o novo intervalo de busca e faça uma busca nesse novo intervalo (vá para o Passo 2).
7. Senão, se o elemento desejado for maior do que o elemento na posição interpolada, considere o intervalo à direita do elemento na posição interpolada como o novo intervalo de busca e faça uma busca nesse novo intervalo (vá para o Passo 2).

## Qual o desempenho da Busca por Interpolação?

### Melhor Caso

O melhor caso do algoritmo de Busca por Interpolação ocorre quando o elemento procurado é o primeiro elemento considerado. Nesse cenário, o algoritmo tem um custo constante de comparações:

- `O(1)` comparações

### Pior Caso

O pior caso do algoritmo de Busca por Interpolação ocorre quando o arranjo de busca não possui uma distribuição uniforme dos elementos. Nesse cenário, o algoritmo tem um custo linear de comparações, em função do número elementos `n` no arranjo:

- `O(n)` comparações
