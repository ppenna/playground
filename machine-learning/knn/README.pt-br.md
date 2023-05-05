# K-Nearest Neighbors

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é o _KNN_?](#o-quê-é-o-knn)
- [Quais são as características do _KNN_?](#quais-são-as-características-do-knn)
- [Quais as aplicações do _KNN_?](#quais-as-aplicações-do-knn)
- [Quais são os passos do algoritmo _KNN_?](#quais-são-os-passos-do-algoritmo-knn)
- [Como melhorar a precisão do algoritmo _KNN_?](#como-melhorar-a-precisão-do-algoritmo-knn)
- [Qual o desempenho do _KNN_?](#qual-o-desempenho-do-knn)

## O quê é o _KNN_?

O _K-Nearest Neighbors_ (KNN), ou K-Vizinhos Mais Próximos, é um algoritmo de aprendizado de máquina supervisionado que pode ser usado tanto para classificação quanto regressão. Esse algoritmo foi introduzido por Evelyn Fix e Joseph Hodges em 1951 e revisitado por Thomas Cover, em 1967.

No caso da classificação, o _KNN_ determina a classe de um ponto de dados desconhecido com base nas classes dos pontos de dados conhecidos mais próximos a ele. No caso da regressão, o _KNN_ determina o valor de uma variável de destino para um ponto de dados desconhecido com base nos valores dessa variável nos pontos de dados conhecidos mais próximos a ele.

## Quais são as características do _KNN_?

- O _KNN_ é um algoritmo de máquina supervisionado.
- O _KNN_ é um algoritmo que pode ser usado para classificação e regressão.
- O _KNN_ é um algoritmo não-paramétrico, ele não faz suposições sobre a distribuições de dados subadjacentes.
- O _KNN_ é sensível à escolha da métrica de distância usada.
- O _KNN_ é sensível ao parâmetro _K_, que representa o número de vizinhos mais próximos a serem considerados.

## Quais as aplicações do _KNN_?

- **Classificação de Texto** - O _KNN_ pode ser usado para classificar documentos de texto em diferentes categorias com base no conteúdo do documento.
- **Recomendações de Produtos** - O _KNN_ pode ser usado para recomendar produtos com base nas preferências do usuário e nas compras anteriores.
- **Análise de Sentimentos** - O _KNN_ pode ser usado para classificar opiniões de usuários em positivas, negativas ou neutras com base no texto da opinião.
- **Reconhecimento de Imagem** - O _KNN_ pode ser usado para reconhecer images com base em características específicas da imagem, como forma, cor e textura.
- **Previsão de Valores** - O _KNN_ pode ser usado para prever valores numéricos, como o preço de uma casa, ou o valor de uma ação na bolsa de valores com base em dados históricos.

## Quais são os passos do algoritmo _KNN_?

1. Carregar o conjunto de treinamento. O conjunto de treinamento contém os dados de entrada e as respectivas classes ou valores de saída.
2. Escolher um valor para _K_. O valor de _K_ representa o que representa o número de vizinhos mais próximos que serão considerados aou classificar ou prever um ponto de dados desconhecido.
3. Calcular a distância. Calcular a distância entre o ponto de dados desconhecido e todos os pontos de dados conhecidos no conjunto de treinamento. Existem várias métricas de distância que pode ser usadas, como a distância euclidiana e a distância de Manhattan.
4. Selecionar os _K_ vizinhos mais próximos. Selecionar os _K_ vizinhos mais próximos com base nas distâncias calculas no passo anterior.
5. Calcular a classe ou valor médio. Se o _KNN_ for usado para classificação, a classe mais comum entre os _K_ vizinhos mais próximos é atribuída ao ponto de dados desconhecido. Se o _KNN_ for usado para regressão, o valor médio dos _K_ vizinhos mais próximos é atribuído ao ponto de dados desconhecido.
6. Retornar a classe ou valor do ponto de dados desconhecido como predição final do modelo.

## Como melhorar a precisão do algoritmo _KNN_?

- **Normalização de Dados** - A normalização dos dados pode ajudar a reduzir o impacto de características com escalas muito diferentes nos cálculos de distância. Existem várias técnicas de normalização de dados, como a normalização min-max e a normalização z-score.
- **Seleção de Características** - A seleção de características, ou redução de dimensionalidade, envolve a escolha das características mais relevantes par ao modelo e a exclusão das características menos importantes. Isso pode ajudar a reduzir o ruído nos dados e melhorar a precisão do modelo.
- **Ajuste de Parâmetros**. O valor de _K_ é um parâmetro que pode ser ajustado para melhorar a precisão do modelo. Isso envolve testar diferentes valores de _K_ e selecionar aquele que produz melhor precisão.
- **_KNN_ Ponderado** - O _KNN_ ponderado leva em consideração a distância dos vizinhos mais próximos ao fazer a predição final. Vizinhos mais próximos recebem um peso maior na predição final do que os vizinhos mais distantes.
- **Remoção de Outliers** - Outliers são valores extremos que podem afetar negativamente a precisão do modelo. A remoção de outliers pode melhorar a precisão do modelo, eliminando pontos de dados que não são representativos do conjunto de dados como um todo.
- **Ajuste de Distância** - O _KNN_ pode ser ajustado para usar diferentes métricas de distância, como a distância euclidiana e a distância de Manhattan. Testar diferentes métricas de distância pode ajudar a determinar qual métrica produz a melhor precisão para o conjunto de dados específico.

## Qual o desempenho do _KNN_?

O desempenho do algoritmo _KNN_ depende do número de pontos de dados no conjunto de treinamento, do número de características dos pontos de dados e do valor de _K_.

Para classificar ou prever um único ponto de dados desconhecido, o algoritmo _KNN_ precisa calcular a distância entre o ponto desconhecido e todos os pontos de dados conhecidos no conjunto de treinamento, o que resulta em uma complexidade computacional de `O(nd)`, onde `n` é o número de pontos de dados no conjunto de treinamento e `d` é o número de características de um ponto de dados.

O algoritmo também precisa selecionar os `K` vizinhos mais próximos com base nas distâncias calculadas, o que pode ser feito usando uma estrutura de dados como uma fila de prioridade ou uma árvore de busca binária. Usando uma estrutura de dados eficiente, a complexidade computacional para selecionar os `K` vizinhos mais próximos é  `O(K log N)`.
