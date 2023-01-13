# Shell Sort

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é o Shell Sort?](#o-quê-é-o-shell-sort)
- [Quando usar o Shell Sort?](#quando-usar-o-shell-sort)
- [Quais as características do Shell Sort?](#quais-as-características-do-shell-sort)
- [Qual o algoritmo de Shell Sort?](#qual-o-algoritmo-de-shell-sort)
- [Qual sequência de intervalos usar no Shell Sort?](#qual-sequência-de-intervalos-usar-no-shell-sort)
- [Qual o desempenho do Shell Sort?](#qual-o-desempenho-do-shell-sort)

## O quê é o Shell Sort?

O Shell Sort é um algoritmo de ordenação por comparação criado por Donald Shell em 1959. O algoritmo é baseado no algoritmo Ordenação por Inserção (_Insertion Sort_) e funciona da seguinte forma.

Inicialmente, a coleção é dividida em vários subgrupos, de forma que todos os elementos de um subgrupo estejam a um mesmo intervalo `h` entre si. Em seguida, cada subgrupo é reordenado, usando o algoritmo de Ordenação por Inserção. Por fim, o valor do intervalo `h` é reduzido, novos subgrupos são criados e o processo repetido até que o tamanho do intervalo `h` seja de `1`.

## Quando usar o Shell Sort?

- O Shell Sort é indicado para ordenar coleções pequenas.
- O Shell Sort é indicado para ordenar coleções que estejam parcialmente ordenadas.
- O Shell Sort pode ser usado quando o espaço de memória auxiliar é inexistente ou limitado.
- O Shell Sort pode ser usado quando uma ordenação estável é necessária.

## Quais as características do Shell Sort?

- O Shell Sort é um algoritmo baseado em comparações.
- O Shell Sort é um algoritmo baseado no algoritmo de Ordenação por Inserção.
- O Shell Sort é _in-place_, ou seja não exige um espaço de memória auxiliar para ordenação a coleção.
- O Shell Sort é estável, ou seja ele mantém a ordem relativa de elementos que tenham valores iguais.
- O desempenho do Shell Sort é bastante impactado pela forma como os elementos estão inicialmente dispostos na coleção de entrada.

## Qual o algoritmo de Shell Sort?

1. Escolha um intervalo inicial `h`.
2. Divida a coleção em vários subgrupos, de forma que elementos em um mesmo subgrupo estão a uma distância `h` entre si.
3. Ordene cada subgrupo usando o algoritmo de Ordenação por Inserção.
4. Diminua o valor do intervalo `h` e repita os Passos 2 e 3 até que o intervalo `h` seja maior que `0`.
5. A coleção está ordenada.

## Qual sequência de intervalos usar no Shell Sort?

- Sequência de Shell -- `h = n/2ᵏ`, onde `n` é o tamanho da coleção e `k` é o passo no algoritmo Shell Sort. Essa sequência faz com o algoritmo tenha um desempenho quadrático `O(n²)` no pior caso.
- Sequência de Hibbard -- `h = 2ᵏ - 1`, onde `k` é o passo no algoritmo Shell Sort. Essa sequência faz com que o algoritmo tenha um desempenho sub-quadrático `O(n³⁄₂)` no pior caso.
- Sequência de Knuth -- `h = (3ᵏ - 1) / 2`, onde `k` é o passo no algoritmo Shell Sort. Essa sequência faz com que o algoritmo tenha um desempenho sub-quadrático `O(n³⁄₂)` no pior caso.

## Qual o desempenho do Shell Sort?

### Melhor Caso

O desempenho no melhor caso para o algoritmo Shell Sort acontece quando a coleção de entrada está parcialmente ordenada. Nesse cenário, o algoritmo tem um custo super-linear de comparações, em função do número de elementos `n` na coleção:

- `O(n log₂ n)` comparações

### Pior Caso

O desempenho no pior caso para o algoritmo Shell Sort acontece quando a coleção de entrada está ordenada de forma inversa. Nesse cenário, o algoritmo tem um custo quadrático de comparações, em função do número de elementos `n` na coleção:

- `O(n²)` comparações
