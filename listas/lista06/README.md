# Lista 06 — Alocação Dinâmica de Memória

## Conteúdo Abordado

- Funções `malloc`, `calloc`, `realloc` e `free`
- Diferença entre memória estática e dinâmica
- Vetores de tamanho variável alocados em tempo de execução
- Boas práticas: verificar retorno de `malloc` e liberar memória

## Aprendizados

Nesta lista, aprofundei o uso de alocação dinâmica de memória em C, especialmente com matrizes (ponteiro de ponteiro) e funções que manipulam estruturas dinâmicas. Aprendi a criar funções genéricas para alocar, liberar, ler e imprimir matrizes, além de aplicar operações usando ponteiros para função. Também pratiquei o uso de realloc, enumerações e structs aninhadas em problemas mais complexos, como o gerenciamento de treinadores e pokémons.

## Exercícios

| Arquivo | Descrição |
|---------|-----------|
| q1.c | Resolvida sem uso de IA. Alocação dinâmica de matriz, ponteiro para função e operações matemáticas em todos os elementos |
| q2.c | Resolvida com IA. Simulação de ataques em área (AoE) em matriz dinâmica, ponteiro para função e cópia de matriz |
| q3.c | Resolvida com IA. Sistema de gerenciamento de treinadores e pokémons com structs, realloc e ordenação dinâmica |
| q4.c | Resolvida sem uso de IA. Implementação de pipeline de filtros em matriz dinâmica, modificando a matriz in-place |


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
