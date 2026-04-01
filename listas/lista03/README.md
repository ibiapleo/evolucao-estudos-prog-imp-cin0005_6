# Lista 03 — Vetores e Strings

## Conteúdo Abordado

- Declaração e inicialização de vetores
- Percorrimento e manipulação de vetores
- Strings como arrays de `char`
- Funções da biblioteca `<string.h>`: `strlen`, `strcpy`, `strcat`, `strcmp`

## Aprendizados

Nesta lista eu senti uma evolucao principalmente em strings.

Com vetores eu ja tinha uma base razoavel, mas strings sempre foram um ponto mais dificil para mim, principalmente em:

- leitura correta da entrada (inclusive com espacos);
- interpretacao de como os caracteres ficam armazenados;
- comparacao de strings e caracteres;
- filtragem de caracteres e normalizacao para comparacoes.

Ao resolver as questoes, consegui tirar varias duvidas praticas sobre esse tema e me senti mais confortavel para manipular strings.

## Exercícios

| Arquivo | Descrição |
|---------|-----------|
| q1.c | Fiz sem uso de IA para escrever o codigo |
| q2.c | Fiz o codigo sem uso de IA; usei IA apenas para guiar meu raciocinio na logica de tempo do enunciado e, com isso, implementei a simulacao dos atendimentos por horario. |
| q3.c | Fiz sem uso de IA para escrever o codigo |
| q4.c | Fiz sem uso de IA para escrever o codigo; resolvi essa questão basicamente debugando e vendo o resultado que dava de acordo com diferentes entradas |

## Como Compilar

**OBS!** Via gcc tanto no windows como no linux/macos

### Linux/MacOS
- Para compilar o código:
```bash
gcc questao.c -o ./builds/nome_do_build
```
- Para rodar o código:
```bash
./builds/nome_do_build
```
### Windows (via gcc MINGW)
- Para compilar o código:
```bash
gcc questao.c -o .\builds\nome_do_build
```
- Para rodar o código:
```bash
.\builds\nome_do_build.exe
```
