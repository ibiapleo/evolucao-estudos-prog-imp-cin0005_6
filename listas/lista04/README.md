# Lista 04 — Matrizes e Funções

## Conteúdo Abordado

- Declaração e uso de matrizes bidimensionais
- Passagem de vetores e matrizes para funções
- Passagem de parâmetros por valor e por referência (usando ponteiros)
- Escopo de variáveis e recursão básica

## Aprendizados

Nao utilizei IA para resolver nenhuma das questoes que fiz nesta lista.

Depois da lista de vetores, me senti mais confiante para trabalhar com matrizes e, no geral, nao achei dificil.

A questao 01 eu nao fiz (nem tentei), porque ao ler o enunciado achei mais complexa a parte de construir um algoritmo para menor caminho. Como as outras questoes ja somavam os 10 pontos, deixei essa de lado.

Na questao 02, utilizei o conceito de recursao. Tambem estudei como a recursao funciona por tras dos panos, especialmente a pilha de chamadas de funcoes durante a execucao.

Nas questoes 03 e 04, foi bem tranquilo: identificar posicoes na matriz e aplicar as condicoes especificas de atualizacao em cada caso.

## Exercícios

| Arquivo | Descrição |
|---------|-----------|
| q1.c | Nao resolvida. Li o enunciado, mas optei por nao fazer por envolver logica de menor caminho que considerei mais complexa naquele momento. |
| q2.c | Resolvida sem IA para codar. Simula a queda da gota na parede; fiz uma versao com recursao, revisitando o conceito e estudando a pilha de chamadas para entender como o processo ocorre por tras dos panos. |
| q3.c | Resolvida sem IA para codar. Simula os movimentos em uma matriz e encontra a coordenada mais visitada. |
| q4.c | Resolvida sem IA para codar. Localiza postes na matriz e aplica decoracoes nas posicoes vizinhas e diagonais conforme as condicoes. |

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
