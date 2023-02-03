# Algoritmo LCS

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é o Algoritmo LCS?](#o-quê-é-o-algoritmo-lcs)
- [Quais são as características do Algoritmo LCS?](#quais-são-as-características-do-algoritmo-lcs)
- [Quais as aplicações do Algoritmo LCS?](#quais-as-aplicações-do-algoritmo-lcs)
- [Qual é o Algoritmo LCS?](#qual-é-o-algoritmo-lcs)
- [Qual o desempenho do Algoritmo LCS?](#qual-o-desempenho-do-algoritmo-lcs)

## O quê é o Algoritmo LCS?

O Algoritmo LCS (_Longest Common Subsequence_) é um algoritmo que resolve o problema da Subsequência Comum Mais Longa ou Maior Subsequência Comum -- um problema clássico da ciência da computação que se resume a encontrar a maior subsequência comum entre duas sequências de elementos. Os elementos nesta subsequência não necessariamente devem ser contíguos nas sequências de entradas.

## Quais são as características do Algoritmo LCS?

- O Algoritmo LCS é um algoritmo de programação dinâmica.
- O Algoritmo LCS necessita de espaço de memória auxiliar para funcionar.
- O desempenho do Algoritmo LCS depende somente do comprimento das sequências de entrada.

## Quais as aplicações do Algoritmo LCS?

- **Comparação de Arquivos** -- O Algoritmo LCS é usado para comparar arquivos e identificar as diferenças entre eles. Isso é útil na sincronização de arquivos distribuídos ou na detecção de mudanças em arquivos ao longo do tempo.
- **Detecção de Plágio** -- O Algoritmo LCS é usado para comparar documentos e identificar seções de texto semelhantes ou idênticas. Isso é útil na detecção de cópias não autorizadas ou no controle de qualidade de documentos.
- **Processamento de String** -- O Algoritmo LCS é usado em problemas relacionados a processamento de string, como a identificação de palavras semelhantes ou a geração de sugestões de correção de palavras.
- **Bioinformática** -- O Algoritmo LCS é usado na bioinformática para comparar sequências de DNA e proteínas e identificar regiões semelhantes ou idênticas.
- **Sincronização de Arquivos** -- O Algoritmo LCS é usado para sincronizar arquivos entre diferentes dispositivos ou servidores, identificando as diferenças entre as versões e atualizando as informações de acordo.

## Qual é o Algoritmo LCS?

1. Inicialize uma tabela de  `(n + 1)`  linhas e `(m + 1)` colunas, onde `n` e `m` são os comprimentos das duas sequências de entrada.
2. Preencha a primeira linha e a primeira coluna com zeros.
3. Para cada elemento na primeira sequência, compare-o com cada elemento na segunda sequência.
   - Se os elementos forem iguais, armazene na tabela o valor da célula anterior diagonal mais `1`.
   - Caso contrário, armazene o máximo entre os valores das células acima e à esquerda.
4. O comprimento a subsequência comum mais longa será armazenado na célula na última linha e na última coluna da tabela.
5. Para construir a subsequência comum mais longa em si, comece na célula na última linha e na última coluna da tabela e siga os caminhos de maior valor de volta até a célula na primeira linha e na primeira coluna.

## Qual o desempenho do Algoritmo LCS?

O desempenho do Algoritmo LCS é sensível somente ao comprimento `m` e `n` das sequências de entrada. Por esse motivo, no pior e melhor caso, o Algoritmo LCS possui um desempenho quadrático de comparações:

- `O(mn)` comparações
