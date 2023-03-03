# _Algoritmo Genético_

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é um _Algoritmo Genético_?](#o-quê-é-um-algoritmo-genético)
- [Quais são as principais características de um _Algoritmo Genético_?](#quais-são-as-principais-características-de-um-algoritmo-genético)
- [Quais as aplicações de um _Algoritmo Genético_?](#quais-as-aplicações-de-um-algoritmo-genético)
- [Quais são os passos de um _Algoritmo Genético_?](#quais-são-os-passos-de-um-algoritmo-genético)
- [Qual a eficiência de um _Algoritmo Genético_?](#qual-a-eficiência-de-um-algoritmo-genético)
- [Qual a complexidade computacional de um _Algoritmo Genético_?](#qual-a-complexidade-computacional-de-um-algoritmo-genético)

## O quê é um _Algoritmo Genético_?

Um_Algoritmo Genético_ é um método de busca heurística inspirado na Teoria da Evolução de Charles Darwin. Esse método foi introduzido por John Holland em 1975 e é usado para encontrar soluções aproximadas para problemas de otimização complexos.

Um _Algoritmo Genético_ se baseia nos fenômenos da seleção natural, reprodução e mutação da seguinte forma. Inicialmente, uma população de soluções é criada aleatoriamente. Cada solução é representada por um cromossomo, que consiste em um conjunto de genes que codificam as características da solução. Os cromossomos são avaliados com base em sua aptidão para resolver o problema em questão.

Os cromossomos mais aptos são selecionados para reprodução, e a reprodução é feita por meio de cruzamento e mutação. O cruzamento envolve a combinação de características de dois cromossomos para produzir um novo cromossomo. A mutação envolve a alteração aleatória de um gene no cromossomo para introduzir variação na população.

O processo de seleção, reprodução, cruzamento e mutação é repetido por várias gerações até que uma solução satisfatória seja encontrada ou até que um critério de parada seja atingido.

## Quais são as principais características de um _Algoritmo Genético_?

- O _Algoritmo Genético_ é um algoritmo de busca heurística.
- O _Algoritmo Genético_ é um algoritmo bioinspirado, isto é se baseia em fenômenos biológicos.
- O desempenho do algoritmo genético depende de vários parâmetros ajustáveis, como o tamanho da população, a taxa de mutação e os métodos de seleção e reprodução.

## Quais as aplicações de um _Algoritmo Genético_?

- **Otimização** -- _Algoritmos Genéticos_ são frequentemente usados para resolver problemas de otimização em áreas como engenharia e finanças. Por exemplo, encontrar a melhor combinação de parâmetros para um modelo de simulação ou minimizar os custos de produção.

- **Planejamento** -- _Algoritmos Genéticos_ são usados para planejar tarefas e horários em várias áreas, como logística, transporte e programação de tarefas.

- **Aprendizado de Máquina** -- _Algoritmos Genéticos_ são usados em conjunto com outras técnicas de aprendizado de máquina para selecionar as melhores características (features) em um conjunto de dados.

- **Design de Produtos** -- _Algoritmos Genéticos_ são usados para otimizar o design de produtos em áreas como arquitetura, design de moda, design de interiores, entre outros.

- **Seleção de Portfólio** - _Algoritmos Genéticos_ são usados para selecionar a melhor combinação de ativos financeiros em um portfólio, maximizando o retorno e minimizando o risco.

## Quais são os passos de um _Algoritmo Genético_?

1. Inicialização -- Criar aleatoriamente uma população de soluções (indivíduos), geralmente com um tamanho fixo.

2. Avaliação da Aptidão -- Avaliar a aptidão de cada indivíduo na população, com base em um critério de aptidão (fitness function). A aptidão é uma medida de quão bem o indivíduo resolve o problema em questão.

3. Seleção -- Selecionar os indivíduos mais aptos para a reprodução, usando um método de seleção como a roleta, torneio ou rank.

4. Reprodução -- Criar uma nova geração de indivíduos a partir dos indivíduos selecionados na etapa anterior. Isso envolve cruzamento e/ou mutação dos genes dos indivíduos selecionados.

5. Avaliação da Aptidão da Nova População -- Avaliar a aptidão da nova população gerada na etapa anterior.

6. Verificação do Critério de Parada -- Verificar se o critério de parada foi atingido, como um número máximo de gerações ou uma aptidão mínima desejada. Se o critério não foi atingido, voltar para a etapa de seleção.

7. Retorno da Solução -- Retornar a solução final, que é o indivíduo mais apto encontrado ao longo de todas as gerações.

## Qual a eficiência de um _Algoritmo Genético_?

A eficiência de um _Algoritmo Genético_ depende de vários parâmetros ajustáveis, como o tamanho da população, a taxa de mutação e os métodos de seleção e reprodução. Em geral, os algoritmos genéticos têm a capacidade de encontrar soluções boas ou mesmo ótimas para uma ampla variedade de problemas de otimização.

## Qual a complexidade computacional de um _Algoritmo Genético_?

A complexidade computacional de um _Algoritmo Genético_ depende do tamanho da população, do número de gerações e dos operadores genéticos selecionados. Em geral, a complexidade computacional do _Algoritmo Genético_ é determinada pelo número de avaliações de aptidão que devem ser realizadas, já que a avaliação de aptidão é geralmente a operação mais custosa computacionalmente.

Assim, se a população tem tamanho `N` e o algoritmo executa `G` gerações, o número total de avaliações de aptidão é N * G. Além disso, o custo computacional dos operadores genéticos depende do tamanho do cromossomo e da taxa de mutação.

Em resumo, a complexidade computacional de um _Algoritmo Genético_ é alta. No entanto, o desempenho pode ser melhorado por meio de técnicas de paralelização e outras otimizações.
