# Quicksort

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

O _Quicksort_ é um algoritmo de ordenação por comparação criado por Tony Hoare
em 1959. Ele é um algoritmo de Divisão e Conquista que funciona particionando e
reordenando recursivamente um arranjo de acordo com um elemento _pivô_.

O _Quicksort_ apresenta um desempenho marginalmente superior a outros algoritmos
de ordenação por comparação, como o _Merge Sort_ e o _Heap Sort_.

## Algoritmo

1. Caso o arranjo tiver menos que dois elementos, pare a recursão.
2. Selecione um elemento do arranjo e chame-o de elemento _pivô_.
3. Particione e reordene o arranjo em dois sub-arranjos, de forma que os
elementos que forem menor do que o _pivô_ fique antes do ponto de divisão e os
elementos maiores que o _pivô_ fiquem depois do ponto de divisão. Elementos que
forem iguais ao _pivô_ podem ser colocados em quaisquer uma das partições.
4. Recursivamente aplique os Passos 1 -- 3 nos sub-arranjos da esquerda e direita.
5. Quando a recursão parar, o arranjo está ordenado.

## Desempenho

- Melhor Caso: $O(n \log_2 n)$ comparações
- Pior Caso: $O(n^2)$ comparações

## Leitura Complementar

- [Desenvolvendo Software](http://desenvolvendosoftware.com.br/algoritmos/ordenacao/quicksort.html)
- [Wikipédia](https://pt.wikipedia.org/wiki/Quicksort)
