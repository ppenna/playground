# Matrizes

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é uma Matriz?](#o-quê-é-uma-matriz)
- [Onde Matrizes são usadas?](#onde-matrizes-são-usadas)
- [Qual é a estrutura de uma Matriz?](#qual-é-a-estrutura-de-uma-matriz)
- [Quais são as operações básicas em Matrizes?](#quais-são-as-operações-básicas-em-matrizes)
  - [Operação Adição de Matrizes](#operação-adição-de-matrizes)
  - [Operação Multiplicação por Escalar](#operação-multiplicação-por-escalar)
  - [Operação Transposição](#operação-transposição)
  - [Operação Multiplicação](#operação-multiplicação)


## O quê é uma Matriz?

Matrizes são estruturas matemáticas compostas por uma tabela de números, ou outros objetos matemáticos, organizados em linhas e colunas. Uma matriz é denotada por uma letra maiúscula e seus elementos são referenciados por sua posição na tabela, indicando primeiro a linha e depois a coluna. Por exemplo, A[2, 3] se refere ao elemento localizado na segunda linha e terceira coluna da matriz A.

## Onde Matrizes são usadas?

- **Computação Gráfica** - Matrizes podem ser usadas para representar objetos tridimensionais. As transformações lineares, como rotação, escala e translação, podem ser aplicadas às matrizes para manipular a posição, orientação e tamanho dos objetos na cena.
- **Aprendizado de Máquina** - Matrizes podem ser usadas para representar dados em um formato que pode ser facilmente processado por algoritmos de aprendizado de máquina. Por exemplo, em redes neurais, matrizes podem ser passadas como entrada da rede, cada camada de neurônios realiza operações matemáticas nessa matriz para gerar uma matriz de resposta.
- **Processamento de Imagens** - Matrizes podem ser usadas para representar imagens digitais e aplicar filtros e transformações para processá-las. As matrizes podem ser usadas para representar uma imagem, onde cada elemento de uma matriz representa um pixel.
- **Análise de Dados** - Matrizes podem ser usadas para representar conjuntos de numéricos nos mais variados tipos de análises estatísticas. Por exemplo, uma matriz pode ser usada para representar as pontuações de um teste para um grupo de alunos, onde cada linha representa um aluno e cada coluna representa uma questão.

## Qual é a estrutura de uma Matriz?

Uma Matriz `m` pode ser construída con os seguintes componentes:

- `m.nlinhas`: um inteiro que indica número de linhas na matriz.
- `m.ncolunas`: um inteiro que indica o número de colunas na matriz.
- `m.elementos[]`: uma tabela que armazena os elementos de uma matriz.

## Quais são as operações básicas em Matrizes?

- [`add()` adiciona duas matrizes.](#operação-adição-de-matrizes)
- [`scale()` multiplica uma matriz por um escalar.](#operação-multiplicação-por-escalar)
- [`transpose()` transpõe uma matriz](#operação-transposição)
- [`multiply()` multiplica duas matrizes](#operação-multiplicação)

### Operação Adição de Matrizes

A operação de adição de matrizes envolve a soma de cada elemento correspondente de duas matrizes. Os passos dessa operação são:

1. Verifique se as matrizes de de entrada têm o mesmo tamanho (mesmo número de linhas e colunas).
2. Crie uma nova matriz com o mesmo tamanho das matrizes de entrada.
3. Para cada elemento correspondente das matrizes de entrada, some-os e armazene o resultado na posição correspondente da nova matriz.
4. Quando todos os elementos correspondentes tiverem sido processados, a nova matriz resultante contém a soma das matrizes de entrada.

### Operação Multiplicação por Escalar

A operação de multiplicação de uma matriz por escalar envolve a multiplicação de cada elemento de uma matriz por uma constante (escalar). Os passos dessa operação são:

1. Denote como `A` a matriz de entrada e `c` o escalar usado na multiplicação.
2. Crie uma nova matriz do mesmo tamanho que a matriz `A`.
3. Para cada elemento da matriz `A`, multiplique o valor por `c` e armazene o resultado na posição correspondente da nova matriz.
4. Quanto todos os elementos da matriz `A` tiverem sido processados, a nova matriz resultante contém a matriz original multiplicada por `c`.

### Operação Transposição

A operação de transposição de matrizes envolve a troca de linhas por colunas em uma matriz. Os passos dessa operação são:

1. Denote como `A` a matriz de entrada.
2. Crie uma nova matriz onde o número de linhas na matriz é o número de colunas na matriz `A` e o número de colunas é o número de linhas na matriz `A`.
3. Para cada elemento na matriz `A`, coloque-o na posição correspondente na nova matriz, invertendo a posição da linha e da coluna.
4. Quando todos os elementos da matriz `A` tiverem sido processados, a nova matriz resultante contém a matriz `A` transposta.

### Operação Multiplicação

A operação de multiplicação de matrizes envolve a multiplicação de cada elemento de uma linha da primeira matriz pelos elementos correspondentes da coluna da segunda matriz, e a soma desses produtos para obter o elemento da matriz resultante. Os passos dessa operação são:

1. Verifique se as matrizes podem ser multiplicadas. O número de colunas da primeira matriz deve ser igual ao número de linhas da segunda matriz. Caso contrário, a multiplicação de matrizes não é possível.
2. Cria uma nova matriz com o número de linhas da primeira matriz e o número de colunas na segunda matriz.
3. Para cada elemento da matriz resultado `C`, faça:
   1. Multiplique cada elemento da linha correspondente da matriz `A` pelos elementos correspondentes da coluna da matriz `B`.
   2. Some os produtos calculados no passo anterior para obter o valor do elemento da matriz resultante `C` na posição correspondente.
4. Quando todos os elementos da matriz resultante `C` tiverem sido calculados, ela contém o produto das matrizes de entrada.
