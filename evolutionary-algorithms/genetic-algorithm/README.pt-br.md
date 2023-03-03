# Algoritmo Genético

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é o Algoritmo Genético?](#o-quê-é-o-algoritmo-genético)
- [Quais são as características de o Algoritmo Genético?](#quais-são-as-características-de-o-algoritmo-genético)
- [Quais as aplicações do Algoritmo Genético?](#quais-as-aplicações-do-algoritmo-genético)
- [Qual é o Algoritmo Genético?](#qual-é-o-algoritmo-genético)
- [Qual o desempenho do Algoritmo Genético?](#qual-o-desempenho-do-algoritmo-genético)

## O quê é o Algoritmo Genético?

O Algoritmo Genético é um algoritmo de busca heurística inspirado na Teoria da Evolução de Charles Darwin. Esse algoritmo é tipicamente empregado para resolver problemas de otimização e se baseia nos fenômenos da seleção natural, reprodução e mutação.

Em um algoritmo genético, uma população de soluções é criada aleatoriamente. Cada solução é representada por um cromossomo, que consiste em um conjunto de genes que codificam as características da solução. Os cromossomos são avaliados com base em sua aptidão para resolver o problema em questão. Os cromossomos mais aptos são selecionados para reprodução, e a reprodução é feita por meio de cruzamento e mutação.

O cruzamento envolve a combinação de características de dois cromossomos para produzir um novo cromossomo. A mutação envolve a alteração aleatória de um gene no cromossomo para introduzir variação na população.

O processo de seleção, reprodução, cruzamento e mutação é repetido por várias gerações até que uma solução satisfatória seja encontrada ou até que um critério de parada seja atingido. O algoritmo genético é uma técnica poderosa que pode ser usada para resolver uma ampla variedade de problemas de otimização, como encontrar a melhor solução para um problema de programação linear ou a melhor estratégia para um jogo.

## Quais são as características de o Algoritmo Genético?

- O Algoritmo Genético é um algoritmo de busca heurística.
- O Algoritmo Genético é um algoritmo bioinspirado, isto é se baseia em fenômenos biológicos.
- O desempenho do algoritmo genético depende de vários parâmetros ajustáveis, como o tamanho da população, a taxa de mutação e os métodos de seleção e reprodução.

## Quais as aplicações do Algoritmo Genético?

- **Otimização** -- Algoritmos genéticos são frequentemente usados para resolver problemas de otimização em áreas como engenharia e finanças. Por exemplo, encontrar a melhor combinação de parâmetros para um modelo de simulação ou minimizar os custos de produção.

- **Planejamento** -- Algoritmos genéticos são usados para planejar tarefas e horários em várias áreas, como logística, transporte e programação de tarefas.

- **Aprendizado de Máquina** -- Algoritmos genéticos são usados em conjunto com outras técnicas de aprendizado de máquina para selecionar as melhores características (features) em um conjunto de dados.

- **Design de Produtos** -- Algoritmos genéticos são usados para otimizar o design de produtos em áreas como arquitetura, design de moda, design de interiores, entre outros.

- **Seleção de Portfólio** - Algoritmos genéticos são usados para selecionar a melhor combinação de ativos financeiros em um portfólio, maximizando o retorno e minimizando o risco.

## Qual é o Algoritmo Genético?

1. Inicialização -- Criar aleatoriamente uma população de soluções (indivíduos), geralmente com um tamanho fixo.

2. Avaliação da Aptidão -- Avaliar a aptidão de cada indivíduo na população, com base em um critério de aptidão (fitness function). A aptidão é uma medida de quão bem o indivíduo resolve o problema em questão.

3. Seleção -- Selecionar os indivíduos mais aptos para a reprodução, usando um método de seleção como a roleta, torneio ou rank.

4. Reprodução -- Criar uma nova geração de indivíduos a partir dos indivíduos selecionados na etapa anterior. Isso envolve cruzamento e/ou mutação dos genes dos indivíduos selecionados.

5. Avaliação da Aptidão da Nova População -- Avaliar a aptidão da nova população gerada na etapa anterior.

6. Verificação do Critério de Parada -- Verificar se o critério de parada foi atingido, como um número máximo de gerações ou uma aptidão mínima desejada. Se o critério não foi atingido, voltar para a etapa de seleção.

7. Retorno da Solução -- Retornar a solução final, que é o indivíduo mais apto encontrado ao longo de todas as gerações.

## Qual o desempenho do Algoritmo Genético?

O desempenho do algoritmo genético pode variar dependendo do problema em questão e da configuração dos parâmetros do algoritmo. Em geral, o algoritmo genético tem algumas vantagens em relação a outras técnicas de otimização:

- Exploração eficiente do espaço de soluções: a população de soluções mantida pelo algoritmo genético permite que o algoritmo explore o espaço de soluções de forma mais ampla do que outras técnicas que trabalham com apenas uma solução.

- Capaz de encontrar soluções ótimas globais: o algoritmo genético é capaz de escapar de mínimos locais e encontrar soluções ótimas globais, graças à variação aleatória introduzida pela mutação dos genes dos indivíduos.

- Adaptabilidade: o algoritmo genético pode ser facilmente adaptado a diferentes tipos de problemas, através da escolha adequada de métodos de seleção, reprodução e mutação.

- Robustez: o algoritmo genético é geralmente robusto em relação a problemas com ruído, falhas de modelo e outras formas de incerteza.

No entanto, o desempenho do algoritmo genético também pode ser afetado por algumas limitações, tais como:

- Convergência lenta: o algoritmo genético pode convergir lentamente para a solução ótima, especialmente em problemas com espaço de solução muito grande.

- Sensibilidade a parâmetros: a performance do algoritmo genético pode ser sensível à configuração dos parâmetros, o que requer ajuste cuidadoso.

- Custo computacional elevado: o algoritmo genético pode ser computacionalmente caro, especialmente quando a função de aptidão é complexa ou quando é necessário lidar com grandes populações de indivíduos.

- Dificuldade em problemas de otimização multimodal: o algoritmo genético pode ter dificuldades em encontrar soluções ótimas para problemas de otimização multimodal, ou seja, problemas em que existem múltiplos ótimos locais. Nesses casos, outras técnicas de otimização, como algoritmos evolutivos multiobjetivo, podem ser mais adequadas.

Em resumo, o desempenho do algoritmo genético é geralmente bom em muitos tipos de problemas de otimização, mas é importante avaliar cuidadosamente seu desempenho em cada caso específico.
