# Trie

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é uma Trie?](#o-quê-é-uma-trie)
- [Onde Tries são usadas?](#onde-tries-são-usadas)
- [Qual é a estrutura de uma Trie?](#qual-é-a-estrutura-de-uma-trie)
- [Quais são as operações básicas de uma Trie?](#quais-são-as-operações-básicas-de-uma-trie)

## O quê é uma Trie?

Uma Trie, também conhecida como árvore digital ou árvore de prefixos, é uma estrutura de dados não-linear especializada, que é utilizada para armazenar um conjunto de palavras ou sequências de caracteres. Essa estrutura foi inventada por Edward Fredkin e Donald Knuth em meados da década de 1950.

Uma Trie é possui uma estrutura de árvore, em que cada nó representa um caractere ou um prefixo de uma palavra. A raiz da árvore representa o caractere vazio ou o prefixo vazio. Cada caminho da raiz até um nó folha representa uma palavra completa. Os nós internos podem ter vários filhos, correspondendo aos caracteres possíveis que podem seguir o prefixo representado pelo nó pai.

Essa estrutura é particularmente útil quando se deseja realizar operações eficientes de busca de palavras ou prefixos em um conjunto grande de dados. Ela permite uma rápida verificação da existência de palavras, bem como a recuperação de todas as palavras que compartilham um determinado prefixo. Isso ocorre porque a Trie mantém a informação de forma hierárquica, explorando as relações de prefixo entre as palavras.

A eficiência da Trie vem do fato de que a complexidade de busca é diretamente proporcional ao tamanho da palavra ou do prefixo sendo buscado, e não ao tamanho total do conjunto de palavras armazenadas. No entanto, uma desvantagem das Tries é que elas podem ocupar um espaço considerável de memória, especialmente quando o conjunto de palavras possui muitos prefixos comuns.

As Tries são frequentemente utilizadas em problemas relacionados a processamento de linguagem natural, correção ortográfica, sugestão de palavras, autocompletar, indexação de palavras-chave em motores de busca e outras aplicações que envolvem manipulação eficiente de palavras e prefixos.

## Onde Tries são usadas?

- **Correção Ortográfica** - Tries poser ser usadas em sistemas de correção ortográfica para verificar se uma palavra está correta ou sugerir palavras alternativas com base em erros de digitação comuns.

- **Autocompletar e Sugestão de Palavras** - Tries podem ser usadas em recursos de autocompletar e sugestão de palavras em teclados de smartphones, mecanismos de busca e aplicativos de processamento de texto. Elas ajudam a prever a palavra que o usuário deseja digitar com base no contexto e nas palavras já digitadas.

- **Indexação de Palavras-Chave** - Tries podem ser usadas em motores de busca para indexar palavras-chave de forma eficiente. Isso permite uma recuperação rápida de documentos ou páginas da web que contenham palavras específicas.

- **Sistemas de Busca de Texto Completo** - Tries podem ser usadas em sistemas que realizam buscas em grandes volumes de texto, como mecanismos de busca na web ou bancos de dados de documentos. Elas permitem uma busca eficiente de palavras ou frases específicas.

- **Compressão de Dados** - Tries podem ser usadas em algoritmos de compressão de dados, como o algoritmo de compressão de texto Lempel-Ziv-Welch (LZW), que é usado no formato de compressão de arquivo GIF.

- **Análise Léxica** - Tries podem ser usadas na análise léxica de compiladores e interpretadores de linguagens de programação. Elas ajudam a identificar palavras-chave, identificadores e outros elementos léxicos em um programa.

## Qual é a estrutura de uma Trie?

Uma Trie `t` pode ser construída recursivamente com os seguintes componentes:

- `t.caractere`: uma célula que armazena o caractere em um nó da trie.
- `t.filhos`: um ponteiro os nós filhos da trie.

## Quais são as operações básicas de uma Trie?

- [`inserir()` adiciona uma nova palavra à Trie.](#operação-inserir)
- [`buscar()` verifica se uma palavra está presente na trie](#operação-buscar).
- [`remover()` remove uma palavra da trie](#operação-remover).

### Operação Inserir

1. Comece na raiz da Trie.
2. Para cada caractere na palavra a ser inserida:
    - Verifique se o caractere atual já está presente como filho do nó atual. Se sim, vá para o próximo caractere.
    - Caso contrário, crie um novo nó para representar o caractere atual e adicione-o como filho do nó atual.

### Operação Buscar

1. Comece na raiz da Trie.
2. Para cada caractere no prefixo a ser buscado faça:
    - Verifique se o caractere atual está presente como filho do nó atual. Se sim, vá para o próximo caractere.
    - Caso contrário, o prefixo não está presente na Trie, e a busca pode ser interrompida.
3. Se todos os caracteres do prefixo forem percorridos, o prefix buscado está presente na Trie.

### Operação Remover

1. Comece na raiz da Trie e procure o nó correspondente ao prefix que será removid0.
2. Se o nó correspondente não for encontrado, significa que o prefixo não está presente na Trie, e a remoção pode ser encerrada.
3. Se o nó correspondente for encontrado e não tiver outros filhos, remova-o e repita o processo com o nó pai.
4. Continue subindo na Trie, removendo os nós que não têm outros filhos, até que um nó com filhos seja encontrado ou até que a raiz da Trie seja alcançada.
