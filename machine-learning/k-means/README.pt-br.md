# K-Means

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é o _K-Means_?](#o-quê-é-o-k-means)
- [Quais são as características do _K-Means_?](#quais-são-as-características-do-k-means)
- [Quais as aplicações do _K-Means_?](#quais-as-aplicações-do-k-means)
- [Qual é o algoritmo _K-Means_?](#qual-é-o-algoritmo-k-means)
- [Qual o desempenho do _K-Means_?](#qual-o-desempenho-do-k-means)

## O quê é o _K-Means_?

O K-means é um algoritmo de aprendizado de máquina não-supervisionado proposto por Hugo Steinhaus em 1956 que agrupa dados similares em clusters. Ele funciona de forma iterativa, escolhendo `k` centroides, atribuindo cada ponto de dados ao centroide mais próximo e recalculando os centroides até que não haja mais mudanças ou um número máximo de iterações seja atingido.

## Quais são as características do _K-Means_?

- O _K-Means_ é um algoritmo de aprendizado de máquina.
- O _K-Means_ é um algoritmo de agrupamento.
- O _K-Means_ é um algoritmo não-supervisionado.
- O _K-Means_ é um algoritmo iterativo.
- O _K-Means_ converge para uma solução local ótima.
- O _K-Means_ possui desempenho sensível à inicialização e às características dos dados.

## Quais as aplicações do _K-Means_?

- **Segmentação de Clientes** -- O _K-Means_ pode ser usado para agrupar clientes com base em suas características, permitindo que as empresas personalizem suas campanhas de marketing para cada grupo.

- **Agrupamento de Notícias** -- O _K-Means_ pode ser usado para agrupar notícias em categorias com base no seu conteúdo, tornando mais fácil para os usuários encontrar notícias relevantes.

- **Detecção de Fraudes** -- O _K-Means_ pode ser usado para detectar transações suspeitas agrupando transações semelhantes e identificando aquelas que são diferentes do grupo.

- **Análise de Imagens** -- O _K-Means_ pode ser usado para segmentar imagens em regiões com características semelhantes, facilitando a análise de padrões em imagens.

- **Bioinformática**: O _K-Means_ pode ser usado para agrupar proteínas ou genes com base em suas características, permitindo que os cientistas identifiquem novas descobertas na área da biologia molecular.

## Qual é o algoritmo _K-Means_?

1. Escolha um valor `k` para o número de clusters desejados.
2. Inicialize aleatoriamente os centroides dos `k` clusters.
3. Atribua cada ponto de dados ao centroide mais próximo com base na distância euclidiana entre o ponto de dados e os centroides.
4. Recalcule os centroides de cada cluster como a média dos pontos de dados atribuídos a ele.
5. Repita os Passos 3 e 4 até que não haja mais mudanças ou um número máximo de iterações seja atingido.
6. O resultado final é um conjunto de `k` clusters, onde cada ponto de dados pertence a um cluster específico.

## Qual o desempenho do _K-Means_?

 O desempenho do algoritmo _K-Means_ é afetado por diversos fatores, como a escolha do número de clusters `k`, as características do conjunto de dados, a escolha inicial dos centroides e o número de iterações. Em geral, a complexidade do algoritmo é polinomial, em função do número de pontos `n`, dimensão `d` dos dados, do número de clusters `k` e o número de iterações `i`:

- `O(ndki)` operações de ponto flutuante.
