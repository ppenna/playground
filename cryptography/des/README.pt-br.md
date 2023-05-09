# Data Encryption Standard (DES)

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é a _Cifra de César_?](#o-quê-é-a-cifra-de-césar)
- [Quais são as aplicações da _Cifra de César_?](#quais-são-as-aplicações-da-cifra-de-césar)
- [Quais são os passos do algoritmo de _Cifra de César_?](#quais-são-os-passos-do-algoritmo-de-cifra-de-césar)
- [Qual a complexidade do algoritmo de _Cifra de César_?](#qual-a-complexidade-do-algoritmo-de-cifra-de-césar)

## O quê é o _Data Encryption Standard (DES)_?

O _Data Encryption Standard_ (DES) é um algoritmo de criptografia simétrica que foi desenvolvido pela IBM na década de 1970 e adotado como padrão pelo governo dos estados unidos em 1977. O objetivo do DES é proteger a confidencialidade e integridade dos dados transmitidos entre as partes, utilizando um processo de cifragem e decifragem de dados.

O algoritmo DES utiliza uma chave de 56 bits para cifrar os dados e pode ser considerado seguro para aplicações cotidianas não críticas.

## Quais são as aplicações do _Data Encryption Standard (DES)_?

- **Proteção de comunicações** - O DES é frequentemente usado para proteger a comunicação entre dispositivos, como computadores e servidores. Por exemplo, o protocolo SSL/TLS utiliza o DES para proteger a comunicação entre navegadores web e servidores.

- **Proteção de dados em dispositivos de armazenamento** - O DES pode ser usado para criptografar dados em discos rígidos, dispositivos USB, cartões de memória e outros dispositivos de armazenamento. Isso ajuda a evitar que dados sensíveis sejam comprometidos em caso de perda ou roubo do dispositivo.

- **Proteção de senhas** - O DES pode ser usado para armazenar senhas em bancos de dados de forma segura, ajudando a evitar que senhas sejam comprometidas em caso de violação de dados.

- **Proteção de dados confidenciais em trânsito** - O DES pode ser usado para proteger dados confidenciais que estão sendo transmitidos entre sistemas, como arquivos de dados, imagens, documentos, entre outros.

## Quais são os passos do algoritmo de _Data Encryption Standard (DES)_?

1. Permutação inicial (IP): O texto de entrada é submetido a uma permutação inicial, na qual os bits são rearranjados em uma ordem específica.
2. Divisão em blocos: O texto de entrada é dividido em blocos de 64 bits, e cada bloco é submetido a uma série de transformações.
3. Transformação inicial: Cada bloco é submetido a uma permutação inicial, na qual os bits são rearranjados em uma ordem específica.
4. Iterações do algoritmo: Cada bloco é submetido a 16 iterações do algoritmo, que consistem em quatro etapas: expansão, substituição, permutação e XOR com uma chave de 48 bits.
5. Substituição: Na etapa de substituição, o bloco é dividido em oito sub-blocos de 6 bits cada. Cada sub-bloco é substituído por um valor de 4 bits, de acordo com uma tabela pré-definida.
6. Permutação: Na etapa de permutação, os bits são rearranjados em uma ordem específica.
7. XOR com a chave: Na etapa final de cada iteração, o bloco é combinado com uma chave de 48 bits por meio da operação XOR.
8. Troca de blocos: Após as 16 iterações, os blocos são trocados de posição.
9. Permutação final (FP): Cada bloco é submetido a uma permutação final, na qual os bits são rearranjados novamente em uma ordem específica.

## Como quebrar uma criptografia por _Data Encryption Standard (DES)_?

## Qual a complexidade do algoritmo de _Data Encryption Standard (DES)_?
