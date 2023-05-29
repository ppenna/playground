# Árvore Binária de Busca

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é uma Árvore Binária de Busca?](#o-quê-é-uma-árvore-binária-de-busca)
- [Onde Árvores Binárias de Busca são usadas?](#onde-árvores-binárias-de-busca-são-usadas)
- [Qual é a estrutura de uma Árvore Binária de Busca?](#qual-é-a-estrutura-de-uma-árvore-binária-de-busca)
- [Quais são as operações básicas de uma Árvore Binária de Busca?](#quais-são-as-operações-básicas-de-uma-árvore-binária-de-busca)
- [Operação Remover](#operação-remover)

## O quê é uma Árvore Binária de Busca?

Uma Árvore Binária de Busca (BST - _Binary Search Tree_) é uma estrutura de dados não linear em forma de árvore e na qual seus elementos são organizados de forma hierárquica. Nessa estrutura, cada nó possui no máximo dois filhos (esquerda e direta) e respeita a propriedade fundamental de hierarquia: para um dado no `v`, todos os elementos na subárvore da esquerda são menores que o elemento armazenado em `v`, e todos os elementos na subárvore da direita são maiores.

## Onde Árvores Binárias de Busca são usadas?

- **Bancos de Dados** - Árvores Binárias de Busca podem usadas na implementação de índices em bancos de dados, permitindo uma busca rápida e eficiente pelos registros.

- **Sistemas de Busca** - Árvores Binárias de Busca podem ser usadas para organizar e buscar informações de maneira eficiente, em motores de busca e sistemas de indexação.

- **Sistemas de Arquivos** - Árvores Binárias de Busca podem ser usadas para indexar e localizar arquivos de maneira eficiente, em sistemas de arquivos que exigem rápida busca e recuperação de informações.

## Qual é a estrutura de uma Árvore Binária de Busca?

Uma Árvore Binária de Busca `t` pode ser construída recursivamente com os seguintes componentes:

- `t.elemento`: uma célula que armazena o elemento em um nó da árvore.
- `t.esquerda`: um ponteiro para a subárvore da esquerda.
- `t.direita`: um ponteiro para a subárvore da direita.

## Quais são as operações básicas de uma Árvore Binária de Busca?

- [`inserir()` insere um novo elemento em uma Árvore Binária de Busca.](#operação-inserir)
- [`remover()` remove um elemento de uma Árvore Binária de Busca.](#operação-remover)
- [`buscar()` procura um elemento específico em uma Árvore Binária de Busca.](#operação-buscar)

### Operação Inserir

1. Comece pela raiz da árvore. Se a árvore estiver vazia, o novo nó será inserido como raiz.

2. Compare o valor do nó que está sendo inserido com o valor do nó atual.

3. Se o valor do nó que está sendo inserido for menor que o valor do nó atual, vá para a subárvore esquerda. Se a subárvore esquerda estiver vazia, insira o novo nó como filho esquerdo do nó atual. Caso contrário, continue percorrendo a subárvore esquerda recursivamente, repetindo os passos 2 e 3 até encontrar um local adequado para a inserção.

4. Se o valor do nó que está sendo inserido for maior que o valor do nó atual, vá para a subárvore direita. Se a subárvore direita estiver vazia, insira o novo nó como filho direito do nó atual. Caso contrário, continue percorrendo a subárvore direita recursivamente, repetindo os passos 2 e 4 até encontrar um local adequado para a inserção.

5. Uma vez encontrado o local adequado, insira o novo nó na posição correta como filho esquerdo ou direito do nó atual, dependendo da comparação dos valores.

## Operação Remover

1. Comece pela raiz da árvore e encontre o nó que deseja remover. Se a árvore estiver vazia ou o nó não existir na árvore, a remoção não é possível.

2. Se o nó que deseja remover for uma folha (nó sem filhos), basta removê-lo diretamente da árvore, ajustando os ponteiros dos nós adjacentes.

3. Se o nó que deseja remover tiver apenas um filho, substitua o nó a ser removido pelo seu filho. Ajuste os ponteiros dos nós adjacentes para que o nó seja removido corretamente da árvore.

4. Se o nó que deseja remover tiver dois filhos, encontre o sucessor do nó a ser removido. O sucessor é o nó com o menor valor na subárvore direita do nó a ser removido ou o predecessor, que é o nó com o maior valor na subárvore esquerda. O sucessor (ou predecessor) será um nó que pode ter, no máximo, um filho.

5. Mova o valor do sucessor (ou predecessor) para o nó que deseja remover.

### Operação Buscar

1. Comece pela raiz da árvore.
2. Compare a chave do nó atual com a chave que está sendo buscada.
3. Se a chave do nó atual for igual à chave buscada, o nó foi encontrado e a busca é concluída.
4. Se a chave buscada for menor que a chave do nó atual, vá para a subárvore esquerda e repita o passo 2.
5. Se a chave buscada for maior que a chave do nó atual, vá para a subárvore direita e repita o passo 2.
6. Se não houver mais nós para explorar (chegar a uma folha) e a chave buscada não for encontrada, a busca é concluída e a chave não está presente na árvore.
