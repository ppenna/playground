# Redes Neurais Artificiais

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

## O quê é uma Rede Neural Artificial?

Uma Rede Neural Artificial (ANN - _Artificial Neural Network_) é um modelo computacional inspirado no funcionamento do cérebro humano que é capaz de aprender e reconhecer padrões.

Redes Neurais Artificiais foram propostas por McCulloch e Pitts em 1943 e são amplamente aplicadas em problemas de classificação e regressão, nas áreas de visão computacional, reconhecimento de fala e mineração de dados.

## Qual é a estrutura de uma Rede Neural?

Uma _Rede Neural Artificial_ é composta por um conjunto de unidades fundamentais denominados neurônios, que se conectam uns aos outros e são organizados em camadas. Cada neurônio realiza uma computação simples em um conjunto de dados, e cada camada de neurônios tem a função de identificar características relevantes do conjunto de dados e processá-las de maneira gradual.

### Qual é a estrutura de um neurônio?

- **Conjunto de Entradas** - Um neurônio recebe um conjunto de valores de entrada. Cada valor consiste em uma representação numérica de uma característica ou atributo associado aos dados de entrada.
- **Conjunto de Pesos** - Cada entrada do neurônio é associada a um peso sináptico. Os pesos determinam e importância relativa de cada entrada para o valor de saída do neurônio. Durante o treinamento da rede neural, os pesos são ajustados para melhorar o desempenho da rede na resolução de um problema específico.
- **Constante de Viés (_Bias_)** - É um parâmetro  constante adicional que representa uma medida de qão facilmente o neurônio é ativado, independente das entradas. O viés permite que o neurônio faça ajustes na função de ativação e é útil para melhorar a flexibilidade e a capacidade de aprendizado da rede neural.
- **Função de Ativação** - A função de ativação é aplicada à soma ponderada das entradas dos pesos do neurônio e o valor de viés, para produzir o valor de saída do neurônio. A função de ativação introduz não-linearidade no neurônio, permitindo que ele aprenda e modele relações complexadas nos dados.

Baseado nesses valors, o valor de saída de um neurônio é calculado da seguinte forma:

`output = f(SUM(x_i * w_i) + bias)`

### Quais são os tipos de camadas de neurônios?

Camada de entrada (_Input Layer_): É a camada que recebe os dados de entrada e passa esses dados diretamente para a próxima camada. Cada neurônio nessa camada representa uma característica ou atributo específico dos dados.

Camadas Ocultas (_Hidden Layers_): São camadas intermediárias entre a camada de entrada e a camada de saída. Essas camadas têm neurônios adicionais que processam as informações recebidas dos neurônios das camadas anteriores. Cada neurônio nas camadas ocultas combina as informações ponderadas de entrada com uma função de ativação não linear para produzir uma saída. Essas camadas são responsáveis pela extração de características e pelo aprendizado de representações mais complexas dos dados.

Camada de Saída (_Output Layer_): É a camada final da rede neural que gera as saídas ou previsões. O número de neurônios nessa camada depende da tarefa em questão. Por exemplo, para classificação binária, pode haver um único neurônio que retorna uma probabilidade ou uma decisão binária. Para classificação multiclasse, o número de neurônios na camada de saída corresponde ao número de classes diferentes. Para problemas de regressão, pode haver um único neurônio que retorna um valor contínuo.


## Quais são os tipos de _Rede Neural_?

- Perceptron: É a forma mais simples de rede neural, composta por um único neurônio. É utilizado principalmente para problemas de classificação binária.

### Rede Neural de Propagação Direta (_Feed-Forward Neural Network_)

Uma Rede Neural de Propagação Direta (FNN -  _Feed-Forward Neural Network_) é uma rede neural na qual a informação flui apenas em uma direção, da camada de entrada para a camada de saída, sem ciclos ou retroalimentação.

Isso resulta em uma estrutura onde cada camada processa informações
independentemente das camadas anteriores. Por esse motivo, redes neurais de propagação direta são frequentemente usadas em problemas de classificação, regressão e reconhecimento de padrões.

As redes de propagação direta são treinadas usando algoritmos de aprendizado supervisionado, onde os pesos das conexões entre os neurônios são ajustados para minimizar a diferença entre as saídas previstas e as saídas desejadas. Isso é feito usando técnicas de otimização, como o gradiente descendente.


### Rede Neural Recorrente (_Recurrent Neural Network_)

Uma Rede Neural Recorrente (RNN - _Recurrent Neural Network_) é uma rede neural que possui conexões retroativas, permitindo que a informação flua em ciclos.

Essa estrutura possibilita que a rede seja capaz de capturar dependências temporais em sequências de dados. Por esse motivo, redes neurais recorrentes são usadas em tarefas que envolvem o processamento de sequências de dados temporais, como em processamento de linguagem natural, tradução automática, análise de sentimentos, reconhecimento de voz, previsão de séries temporais, entre outros.

Embora RNNs possibilitem maior versatilidade no processamento de dados, elas enfrentam desafios de projeto  como o desvanecimento ou explosão do gradiente, que dificultam o aprendizado de dependências de longo prazo. Para lidar com esses problemas, foram desenvolvidas variantes de RNNs, como as Long Short-Term Memory (LSTM) e as Gated Recurrent Unit (GRU), que incorporam mecanismos de memória aprimorados e são mais eficientes na captura de dependências de longo prazo.

## Como treinar uma Rede Neural?

Existem várias técnicas de treinamento utilizadas para treinar redes neurais. Apesar de diferentes, essas técnicas visam ajustar os pesos das conexões da rede para que ela seja capaz de fazer previsões precisas acerca dos dados.

### Gradiente Descendente (Gradiente Descent)

O Gradiente Descendente (Gradiente Descente) é a técnica mais comum para treinar redes neurais. O gradiente descendente ajusta os pesos da rede iterativamente, minimizando uma função de perda ou custo. O processo envolve calcular o gradiente da função de perda em relação aos pesos e atualizar os pesos na direção oposta ao gradiente, com base em uma taxa de aprendizado.

### Mini-Batch Gradiente Descente

É uma variação da técnica Gradiente Descentende, em que em vez de calcular o gradiente e atualizar os pesos para todo o conjunto de treinamento, a técnica de mini-batch gradient descent divide o conjunto de treinamento em pequenos lotes (mini-batches) e atualiza os pesos após cada lote. Isso pode acelerar o treinamento e melhorar a estabilidade.


### Backpropagation

_Backpropagation_ é um algoritmo usado para treinar redes neurais de propagação direta. O algoritmo funciona propagando o erro calculado na camada de saída de volta para as camadas anteriores, ajustando os pesos de cada camada com base no erro atribuído a ela.

### Quais são os passos do algoritmo de _Backpropagation_?

1. **Inicialização dos pesos** - Os pesos das conexões da rede neural são inicializados com valores aleatórios ou usando alguma técnica de inicialização apropriada.

2. **Cálculo da Saída** - Um conjunto de dados de treinamento é fornecido à rede neural, e a saída é calculada propagando os dados de entrada através das camadas da rede, aplicando as operações de multiplicação de pesos e funções de ativação.

3. **Cálculo do Erro**  É calculada uma medida de erro entre as saídas previstas pela rede e as saídas desejadas do conjunto de treinamento. Essa medida de erro pode ser, por exemplo, a diferença entre a saída prevista e a saída desejada (erro quadrático médio para problemas de regressão) ou a função de custo de classificação (como a entropia cruzada) para problemas de classificação.

4. **Cálculo do gradiente**: O gradiente da função de perda em relação aos pesos é calculado usando o algoritmo de backpropagation. O backpropagation propaga o erro da camada de saída para as camadas anteriores, calculando os gradientes parciais em relação aos pesos em cada camada.
5. **Atualização dos pesos**: Os pesos são atualizados usando a regra do gradiente descendente. Cada peso é ajustado subtraindo uma fração do gradiente multiplicada pela taxa de aprendizado. A taxa de aprendizado controla o tamanho do passo de atualização e é um hiperparâmetro definido pelo usuário.
6. **Repetição dos passos 2 a 5**: Os passos 2 a 5 são repetidos para todos os exemplos do conjunto de treinamento, em um processo conhecido como época. O número de épocas é um hiperparâmetro que determina quantas vezes o conjunto de treinamento será percorrido.
7. **Avaliação da convergência**: O processo de treinamento é repetido até que um critério de parada seja atendido. Isso pode ser um número máximo de épocas, um limite de erro aceitável ou outros critérios definidos pelo usuário.
