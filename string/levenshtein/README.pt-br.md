# Algoritmo de Levenshtein

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é o Algoritmo de Levenshtein?](#o-quê-é-o-algoritmo-de-levenshtein)
- [Quais são as características do Algoritmo de Levenshtein?](#quais-são-as-características-do-algoritmo-de-levenshtein)
- [Quais as aplicações do Algoritmo de Levenshtein?](#quais-as-aplicações-do-algoritmo-de-levenshtein)
- [Qual é o Algoritmo de Levenshtein?](#qual-é-o-algoritmo-de-levenshtein)
- [Qual o desempenho do Algoritmo de Levenshtein?](#qual-o-desempenho-do-algoritmo-de-levenshtein)

## O quê é o Algoritmo de Levenshtein?

O Algoritmo de Levenshtein é um algoritmo de programação dinâmica que calcula a distância de Levenshtein entre duas strings -- o número mínimo inserções, exclusões ou substituições necessárias para transformar uma string em outra. O Algoritmo de Levenshtein funciona preenchendo iterativamente uma tabela onde cada célula representa a distância de Levenshtein entre sub-strings das duas strings de entrada. O valor final na célula inferior direita da tabela é a distância de Levenshtein entre as duas strings completas.

## Quais são as características do Algoritmo de Levenshtein?

- O Algoritmo de Levenshtein é um algoritmo de programação dinâmica.
- O Algoritmo de Levenshtein necessita de espaço de memória auxiliar para funcionar.
- O desempenho do Algoritmo de Levenshtein depende somente do comprimento das strings de entrada.

## Quais as aplicações do Algoritmo de Levenshtein?

- **Verificação ortográfica** -- O Algoritmo de Levenshtein pode ser utilizado para sugerir correções para palavras escritas incorretamente.

- **Análise de DNA** -- O Algoritmo de Levenshtein pode ser utilizado para comparar sequências de DNA e determinar sua similaridade.

- **Recuperação de informação** -- O Algoritmo de Levenshtein pode ser utilizado para classificar ou recuperar informações relevantes baseadas em uma consulta de busca.

- **Reconhecimento de fala** -- O Algoritmo de Levenshtein pode ser utilizado para comparar a fala reconhecida com a fala esperada e corrigir possíveis erros.

- **Sistemas de sugestão** -- O Algoritmo de Levenshtein pode ser utilizado para sugerir palavras ou frases semelhantes a uma determinada string de entrada.

## Qual é o Algoritmo de Levenshtein?

1. Inicialize uma tabela de `(n+1)` linhas e `(m+1)` colunas, onde `n` é o comprimento da primeira string e `m` é o comprimento da segunda string.
2. Preencha a primeira linha e a primeira coluna com valores consecutivos, começando em zero.
3. Para cada caractere na primeira string, faça o seguinte:
   1. Para cada caractere na segunda string, faça o seguinte:
   2. Se os caracteres são iguais, armazene o valor diagonal na célula atual.
   3. Caso contrário, armazene o mínimo dos valores adjacentes (esquerda, cima, diagonal) + 1 na célula atual.
4. O valor na célula inferior direita da matriz é a distância de Levenshtein entre as duas strings.

## Qual o desempenho do Algoritmo de Levenshtein?

O desempenho do Algoritmo de Levenshtein é sensível somente ao comprimento `m` e `n` das sequências de entrada. Por esse motivo, no pior e melhor caso, o Algoritmo de Levenshtein possui um desempenho quadrático de comparações:

- `O(mn)` comparações
