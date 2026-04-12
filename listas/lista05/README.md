# Lista 05 — Alocacao Dinamica

## Conteudo Abordado

- Alocacao dinamica
- Gerenciamento da heap
- Uso de `malloc` e `free`
- Uso de `realloc` para redimensionar memoria
- Passagem de arrays dinamicos para funcoes
- Manipulacao de ponteiros dentro de funcoes

## Aprendizados

Nesta lista, o foco foi alocacao dinamica de memoria.

Aprendi como declarar arrays dinamicamente e como alocar memoria em tempo de execucao. Tambem pratiquei como passar arrays dinamicos para funcoes e como manipular ponteiros dentro das funcoes sem perder a referencia correta da memoria.

Um aprendizado importante foi o cuidado de sempre liberar a memoria com `free` ao final, para evitar vazamento.

Nos exercicios, tive mais dificuldade na questao 03, principalmente na parte de inserir valores e realocar memoria dinamicamente com `realloc`. No inicio fiquei confuso com a logica, mas usei IA para receber um norte e conseguir estruturar a solucao. As questoes 01 e 02 foram resolvidas sem uso de IA.

## Exercicios

| Arquivo | Descricao |
|---------|-----------|
| q1.c | Resolvida sem uso de IA. Exercitou alocacao dinamica e manipulacao de ponteiros. |
| q2.c | Resolvida sem uso de IA. Reforcou passagem de arrays dinamicos para funcoes e controle de memoria. |
| q3.c | Resolvida com apoio de IA para orientacao inicial na logica de insercao e realocacao dinamica com `realloc`. |

## Como Compilar

**OBS!** Via gcc tanto no windows como no linux/macos

### Linux/MacOS
- Para compilar o codigo:
```bash
gcc questao.c -o ./builds/nome_do_build
```
- Para rodar o codigo:
```bash
./builds/nome_do_build
```

### Windows (via gcc MINGW)
- Para compilar o codigo:
```bash
gcc questao.c -o .\builds\nome_do_build
```
- Para rodar o codigo:
```bash
.\builds\nome_do_build.exe
```
