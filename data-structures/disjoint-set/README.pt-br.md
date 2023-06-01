# Conjuntos Disjuntos

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é um Conjunto Disjunto?](#o-quê-é-um-conjunto-disjunto)
- [Onde Conjuntos Disjuntos são usados?](#onde-conjuntos-disjuntos-são-usados)
- [Quais são as operações básicas de um Conjunto Disjunto?](#quais-são-as-operações-básicas-de-um-conjunto-disjunto)
- [Como implementar um Conjunto Disjunto?](#como-implementar-um-conjunto-disjunto)
- [Como otimizar a implementação de um Conjunto Disjunto?](#como-otimizar-a-implementação-de-um-conjunto-disjunto)
- [Qual o desempenho de um Conjunto Disjunto?](#qual-o-desempenho-de-um-conjunto-disjunto)

## O quê é um Conjunto Disjunto?

Um Conjunto Disjunto (_Disjoint Set_ ou _Union-Find_) é uma estrutura de dados que mantém uma coleção elementos, que por sua vez estão organizados em vários conjuntos não sobrepostos. Essa estrutura de dados possibilita que elementos sejam agrupados de maneira eficiente.

## Onde Conjuntos Disjuntos são usados?

- **Algoritmo de Kruskal** - Um Conjunto Disjunto é usado no algoritmo de Kruskal para manter controle dos componentes conexos do grafo e garantir que, a cada iteração do algoritmo, as propriedades da árvore geradora mínima em construção não são violadas.

- **Segmentação de Imagens** - Conjuntos Disjuntos podem ser usados em alguns algoritmos de segmentação de imagens, permitindo que pixels sejam agrupados em regiões com propriedades similares.

- **Aprendizado de Máquina** - Conjuntos Disjuntos podem ser usados na etapa de treinamento de alguns algoritmos de aprendizado de máquina, para agrupar dados com base em características similares.

## Quais são as operações básicas de um Conjunto Disjunto?

- `busca` (ou `find`) determina a qual conjunto um determinado elemento pertence.
- `união` (ou `union`) combina dois conjuntos em um único conjunto.

## Como implementar um Conjunto Disjunto?

Um Conjunto Disjunto pode ser implementado de forma eficiente usando uma coleção de árvores (floresta), onde cada árvore representa um conjunto disjunto.

#### Operação Busca

```
Função busca(conjunto, elemento):
    // Assumir que o elemento é seu próprio representante.
    representanteEncontrado = elemento

    // Seguir os ponteiros dos nós ancestrais na árvore até chegar à raiz.
    Enquanto conjunto[representanteEncontrado] != NULO:
        representanteEncontrado = conjunto[representanteEncontrado]

    // Retornar a raiz encontrada como resultado da busca.
    Retornar representanteEncontrado
```

#### Operação União

```
Função uniao(conjunto, elemento1, elemento2):
    // Buscar o representante para cada elemento.
    representante1 = busca(conjunto, elemento1)
    representante2 = busca(conjunto, elemento2)

    // Verificar se os representantes são diferentes.
    Se representante1 != representante2:
        // Fazer um representante apontar para o outro.
        conjunto[representante1] = representante2
```

## Como otimizar a implementação de um Conjunto Disjunto?

- **Heurística de União por Tamanho** (_Union-by-Size_ ou _Weighted-Union_). Você pode manter informações sobre o tamanho de cada conjunto. Assim, durante a operação de união, una sempre o conjunto de menor tamanho ao de maior tamanho. Isso ajuda a evitar um desbalanceamento de entre conjuntos e a operação de busca seja mais rápida.

- **Compressão de Caminho** (_Path Compression_). Durante a operação de busca, atualize o pai de cada nó visitado para apontar diretamente para o representante do conjunto. Isso ajuda a reduzir o número de comparações necessárias para determinar o representante de um conjunto em operações futuras de busca.

## Qual o desempenho de um Conjunto Disjunto?

Uma implementação de Conjunto Disjunto usando uma coleção de árvores, heurística de união por tamanho e compressão de caminho possui complexidade de tempo sub-logarítmico para as operações de busca e união, em função do número `n` de elementos na estrutura de dados:

- Operação Busca: `O(log* n)`
- Operação União: `O(log* n)`
