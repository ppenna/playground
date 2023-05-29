# Conjuntos Disjuntos

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é um conjunto disjunto?](#o-quê-é-um-conjunto-disjunto)
- [Onde conjuntos disjuntos são usados?](#onde-conjuntos-disjuntos-são-usados)
- [Como implementar um conjunto disjunto?](#como-implementar-um-conjunto-disjunto)
- [Quais são as operações básicas de um conjunto disjunto?](#quais-são-as-operações-básicas-de-um-conjunto-disjunto)

## O quê é um conjunto disjunto?

Um Conjunto Disjunto é uma estrutura de dados que mantém uma coleção elementos, que por sua vez estão particionados em vários conjuntos não sobrepostos. Essa estrutura de dados possibilita que elementos sejam agrupados e particionados em conjuntos de maneira eficiente.

## Onde conjuntos disjuntos são usados?

- Na implementação do Algoritmo de Kruskal, umaa estrutura de dados Conjunto Disjunto é usada para manter controle dos componentes conexos do grafo e para verificar se ao adicionar uma aresta em uma iteração do algoritmo as propriedades da árvore geradora mínima em construção seria violada.
- Em problemas de segmentação de imagem, a estrutura de dados Conjunto Disjunto é usada para manter controle das conexões entre os pixels da imagem, permitindo que esses sejam agrupados em regiões com propriedades similares.
- Em algoritmos de aprendizado de máquina, a estrutura de dados Conjunto Disjunto pode ser usada para agrupar dados em conjuntos com base em suas características e, então, ajudar no processo de treinamento.

## Como implementar um conjunto disjunto?

- **Usando uma coleção de listas encadeadas**, com cada lista representando um conjunto disjunto. Essa implementação é de fácil compreensão e suporta apenas a operação `união` de forma eficiente.
- **Usando uma coleção de árvores**, com cada árvore representando um conjunto disjunto. Essa implementação é de compreensão mais complexa, mas suporta as operações de `união` e `busca` de forma eficiente.

## Quais são as operações básicas de um conjunto disjunto?

- [`união`](#operação-união) (ou `union`) combina dois conjuntos em um único conjunto.
- [`busca`](#operação-busca) (ou `find`) determina a qual conjunto um determinado elemento pertence.

### Operação União

1. Localize o conjunto `X` ao qual o elemento `x` pertence (operação `busca`).
2. Localize o conjunto `Y` ao qual o elemento `y` pertence (operação `busca`).
3. Remova todos os elementos de `Y` e coloque os em `X`.

### Operação Busca

1. Considere inicialmente um conjunto `X` qualquer dentre dos conjuntos disjuntos existentes.
2. Percorra cada um dos elementos em `X` e verifique se aquele elemento é o elemento buscado.
3. Em caso afirmativo, retorne o conjunto `X`.
4. Caso todos os elementos de `X` tenham sido analisados, mas nenhum deles for o elemento buscado, considere um outro conjunto `Y` que ainda não foi analisado, faça `X = Y` e execute novamente os Passos 1 a 4.
5. Caso o elemento buscado não tenha sido encontrado, retorne `"elemento não encontrado"`.
