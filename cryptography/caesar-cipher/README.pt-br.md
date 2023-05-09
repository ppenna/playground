# Cifra de César

[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md) [![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](README.pt-br.md)

_Leia isso em outros idiomas: [English](README.md), [Português](README.pt-br.md)_

- [O quê é a _Cifra de César_?](#o-quê-é-a-cifra-de-césar)
- [Quais são as aplicações da _Cifra de César_?](#quais-são-as-aplicações-da-cifra-de-césar)
- [Quais são os passos do algoritmo de _Cifra de César_?](#quais-são-os-passos-do-algoritmo-de-cifra-de-césar)
  - [Cifragem](#cifragem)
  - [Decifragem](#decifragem)
- [Como quebrar uma criptografia por _Cifra de César_?](#como-quebrar-uma-criptografia-por-cifra-de-césar)
- [Qual a complexidade do algoritmo de _Cifra de César_?](#qual-a-complexidade-do-algoritmo-de-cifra-de-césar)

## O quê é a _Cifra de César_?

A _Cifra de César_ é um algoritmo de criptografia que é bastante conhecido por sua simplicidade. O algoritmo leva esse nome em homenagem a Júlio César, que o utilizava para se comunicar com seus generais durante guerras.

A _Cifra de César_ usa uma técnica de substituição em que cada letra do alfabeto é substituída por outra letra que se encontra um número fixo de posições à frente na ordem alfabética. Por exemplo, com um deslocamento de 3 posições a letra "A" seria substituída pela letra "D", a letra "B" seria substituída pela letra "E" e assim por diante.

## Quais são as aplicações da _Cifra de César_?

A _Cifra de César_ não é um algoritmo de criptografia seguro o suficiente para proteger informações confidenciais ou importantes. Apesar disso, o algoritmo como ferramenta de ensino para introduzir o conceito de criptografia.

## Quais são os passos do algoritmo de _Cifra de César_?

Assim como outros algoritmos de criptografia, a _Cifra de César_ funciona em duas etapas:
- Cifragem: nessa etapa o texto original é criptografado.
- Decifragem: nessa etapa o texto criptografado é descriptografado.

### Cifragem

1. **Escolher uma chave**. A chave é um número inteiro que representa o deslocamento que será aplicado a cada letra do texto original. Por exemplo, se a chave for 3, cada letra do texto original será substituída pela letra que está três posições adiante na ordem alfabética.
2. **Converter o texto original em letras maiúsculas**. Isso é importante para garantir que todas as letras sejam codificadas corretamente.
3. **Analisar cada letra do texto original**: Para cada letra do texto original, é necessário aplicar o deslocamento especificado pela chave. A letra resultante será a letra que se encontra um número fixo de posições à frente dela na ordem alfabética.
4. **Gerar o texto cifrado**. O texto cifrado é a sequência de letras resultante após a aplicação do deslocamento. É importante lembrar que cada letra do texto original é substituída pela letra correspondente no texto cifrado.
5. **Enviar o texto cifrado**. O texto cifrado pode ser enviado para o destinatário por meio de um canal de comunicação seguro ou não seguro, dependendo da sensibilidade das informações.

### Decifragem

1. **Receber o texto cifrado**. O destinatário recebe a mensagem cifrada que foi enviada.
2. **Escolher uma chave**. O destinatário precisa saber qual chave foi usada para criptografar a mensagem. Se a chave não for conhecida, é necessário usar técnicas de criptoanálise para tentar descobri-la.
3. **Aplicar o deslocamento inverso**. Uma vez que a chave é conhecida, é necessário aplicar um deslocamento negativo `-n` ao texto cifrado, onde `n` é a chave utilizada na codificação. Esse deslocamento fará com que cada letra do texto cifrado seja substituída pela letra que se encontra `n` posições atrás dela na ordem alfabética.
4. **Gerar o texto decifrado**: O texto decifrado é a sequência de letras resultante após a aplicação do deslocamento inverso. Cada letra do texto cifrado é substituída pela letra correspondente no texto decifrado.
5. **Analisar o texto decifrado**: O destinatário deve analisar o texto decifrado para verificar se ele faz sentido e se a mensagem foi corretamente decodificada.

## Como quebrar uma criptografia por _Cifra de César_?

A _Cifra de César_ é uma técnica de criptografia muito simples e, por isso, facilmente quebrável por diferentes técnicas de criptoanálise. Algumas maneiras de se quebrar uma mensagem criptografada com a _Cifra de César_ são:

- **Ataque de força bruta**. Nesse tipo de ataque, o tenta-se todas as combinações possíveis de deslocamento até encontrar a mensagem original. Para uma chave de 1 a 25, isso significa testar apenas 25 combinações diferentes.
- **Análise de frequência de letras** A análise de frequência de letras é uma técnica de criptoanálise que se baseia no fato de que certas letras aparecem com mais frequência em um idioma do que outras. Por exemplo, a letra "E" é a letra mais comum em palavras em inglês. Usando essa técnica, o pode-se contar a frequência de cada letra no texto cifrado e compará-la com as frequências esperadas para o idioma em que o texto original foi escrito. Com base nessa análise, é possível fazer uma estimativa do deslocamento que foi usado.
- **Conhecimento do contexto**: Às vezes, o contexto em que a mensagem foi escrita pode ajudar a decifrar a mensagem. Por exemplo, se é sabido que a mensagem foi enviada em uma data específica, é possível tentar usar a data como chave. Isso é particularmente útil se a pessoa que criptografou a mensagem usou uma chave que tenha significado pessoal para ela.

## Qual a complexidade do algoritmo de _Cifra de César_?

A complexidade do algoritmo de _Cifra de César_ depende do número de caracteres `n` na mensagem a ser criptografada ou descriptografada:

- Criptografar: `O(n)`
- Descriptografar: `O(n)`
