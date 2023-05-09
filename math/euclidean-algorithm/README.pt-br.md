# Algoritmo de Euclides

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é o _Algoritmo de Euclides_?](#o-quê-é-o-algoritmo-de-euclides)
- [Quais são as aplicações do _Algoritmo de Euclides_?](#quais-são-as-aplicações-do-algoritmo-de-euclides)
- [Quais são os passos do _Algoritmo de Euclides_?](#quais-são-os-passos-do-algoritmo-de-euclides)
- [Qual a complexidade do _Algoritmo de Euclides_?](#qual-a-complexidade-do-algoritmo-de-euclides)

## O quê é o _Algoritmo de Euclides_?

O _Algoritmo de Euclides_ é um método para encontrar o maior divisor comum (MDC) entre dois números inteiros. Esse método foi descritor pelo matemático grego Euclides em seu livro "Elementos".

O _Algoritmo de Euclides_ é baseado na observação de que, se o resto da divisão de um número `a` por um número `b` é `r`, então o MDC entre `a` e `b` é o mesmo que o MDC entre `b` e `r`.

## Quais são as aplicações do _Algoritmo de Euclides_?

- **Simplificação de Frações** - O algoritmo de Euclides é frequentemente usado para simplificar frações. O MDC entre o numerador e o denominador de uma fração pode ser calculado usando o algoritmo de Euclides, e em seguida a fração pode ser simplificada dividindo ambos os termos pelo MDC.
- **Cálculo de Congruências Lineares** - O algoritmo de Euclides é usado para resolver equações de congruência linear, que são importantes na teoria dos números e na criptografia.
- **Criptografia** - O algoritmo de Euclides é usado em criptografia de chave pública para calcular chaves de criptografia e assinaturas digitais.

## Quais são os passos do _Algoritmo de Euclides_?

1. Denote como `a` e `b` dois números inteiros.
2. Se `b` for igual a `0` retorno `a`.
3. Caso contrário, calcule o resto da divisão de `a` por `b`.
4. Substitua `a` por `b` e `b` por `r`.
5. Retorne ao Passo 1.

## Qual a complexidade do _Algoritmo de Euclides_?

A complexidade do algoritmo de Euclides depende do tamanho dos números de entrada. Para dois números inteiros `a` e `b`, a complexidade do Algoritmo de Euclides é `O(log(min(a, b)))`, onde `log` representa o logaritmo na base 2 e `min(a, b)` é o menor dos dois números `a` e `b`.
