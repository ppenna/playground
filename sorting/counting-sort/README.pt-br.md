# Counting Sort

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é o _Counting Sort_?](#o-quê-é-o-counting-sort)
- [Quais são as características do _Counting Sort_?](#quais-são-as-características-do-counting-sort)
- [Qual é o algoritmo do _Counting Sort_?](#qual-é-o-algoritmo-do-counting-sort)
- [Qual é o desempenho do _Counting Sort_?](#qual-é-o-desempenho-do-counting-sort)
- [Leitura Complementar](#leitura-complementar)

## O quê é o _Counting Sort_?

O _Counting Sort_ (Ordenação por Contagem) é um algoritmo de ordenação de inteiros criado por Harold Seward em 1954. Ele é um algoritmo de Programação Dinâmica, que funciona construindo um histograma cumulativo das chaves do arranjo de entrada e o usando essa estrutura para construir um arranjo de saída ordenado.

Apesar de possui um desempenho assintótico eficiente, o _Counting Sort_ é
geralmente usado como sub-rotina em outros métodos de ordenação não
comparativos, como o _Radix Sort_ e o _Bucket Sort_.

## Quais são as características do _Counting Sort_?

- O _Counting Sort_ é um algoritmo iterativo.
- O _Counting Sort_ é um algoritmo de ordenação de inteiros.
- O _Counting Sort_ é um algoritmo de ordenação estável.
- O desempenho do algoritmo _Counting Sort_ é pouco sensível aos dados de entrada.
- O _Counting Sort_ necessita de uma estrutura de dados auxiliar para funcionar.

## Qual é o algoritmo do _Counting Sort_?

1. Crie um arranjo auxiliar `H` de tamanho igual à maior chave presente no arranjo original `A`.
2. Conte o número de ocorrências de cada elemento em `A` e armazene essa contagem no arranjo auxiliar `H`. Nesse arranjo auxiliar, a primeira posição dá a frequência de elementos de valor `0` em `A`, a segunda posição dá a frequência de elementos de valor `1` em `A` e assim por diante.
3. Percorra o arranjo auxiliar `H` para criar o histograma cumulativo de cada elemento de `A`. Para tanto, acumule o valor da frequência do elemento `i + 1` com a frequência do elemento `i`.
4. Use o arranjo `H` para construir um arranjo de saída ordenado. Para tanto, se `x` é um elemento no arranjo `A` que possui uma frequência cumulativa `H(x)`, então `x` deve ser colocado no arranjo de saída entre a posição `H(x)` e `H(x + 1)`.

## Qual é o desempenho do _Counting Sort_?

O desempenho do _Counting Sort_ é pouco sensível a entrada. Por esse motivo, o desempenho assintótico do algoritmo é linear tanto para o pior quanto melhor caso. Se `n` é o número de elementos no arranjo de entrada e `k` é o valor da maior chave nesse arranjo, o desempenho do _Counting Sort_ é:

- `O(n + k)` operações inteiras

## Leitura Complementar

- [Desenvolvendo Software | Counting Sort](http://desenvolvendosoftware.com.br/algoritmos/ordenacao/counting-sort.html)
