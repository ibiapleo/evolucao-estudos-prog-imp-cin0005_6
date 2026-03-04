# Evolução de Estudos — Programação Imperativa (CIN0005/6)

## Descrição da Disciplina

Esta disciplina aborda os fundamentos da programação imperativa utilizando a linguagem C, com transição para C++ ao final do curso. São trabalhados conceitos como tipos de dados, estruturas de controle, funções, vetores, ponteiros, alocação dinâmica de memória, structs, arquivos e estruturas de dados (pilhas, filas, listas encadeadas e árvores).

## Objetivo do Repositório

Documentar a evolução dos estudos ao longo do semestre, armazenando listas de exercícios resolvidas, anotações semanais e exemplos organizados por conteúdo. O repositório serve como portfólio de aprendizagem e facilita o envio de links como comprovação de evolução ao professor.

## Estrutura de Pastas

```
/
├── README.md               # Este arquivo — visão geral do repositório
├── cronograma.md           # Cronograma por data, associando aulas às listas
├── listas/                 # Listas de exercícios organizadas por tema
│   ├── lista01_io_condicionais/
│   ├── lista02_repeticao/
│   ├── lista03_vetores_strings/
│   ├── lista04_matrizes_funcoes/
│   ├── lista05_ponteiros/
│   ├── lista06_alocacao_dinamica/
│   ├── lista07_matrizes_dinamicas/
│   ├── lista08_structs/
│   ├── lista09_unions_bitfields/
│   ├── lista10_arquivos/
│   ├── lista11_pilhas_filas/
│   ├── lista12_listas_encadeadas/
│   └── lista13_arvores/
├── progresso/              # Diário de estudos semana a semana
│   ├── semana01.md
│   ├── semana02.md
│   └── ...
├── tests/                  # Scripts e casos de teste
├── notebooks/              # Anotações exploratórias (Jupyter ou Markdown)
└── docs/                   # Documentação adicional e referências
```

Cada pasta dentro de `listas/` segue o padrão:
```
lista0X_tema/
├── README.md   # Explicação do conteúdo, aprendizados e exemplos de E/S
└── *.c         # Soluções dos exercícios em C (ou .cpp para C++)
```

## Como Compilar Código C

Certifique-se de ter o **GCC** instalado (`gcc --version`).

**Compilar um arquivo único:**
```bash
gcc -Wall -Wextra -o programa exercicio01.c
./programa
```

**Compilar com múltiplos arquivos:**
```bash
gcc -Wall -Wextra -o programa main.c funcoes.c
./programa
```

**Compilar arquivo C++:**
```bash
g++ -Wall -Wextra -std=c++17 -o programa exercicio.cpp
./programa
```

**Flags úteis:**
| Flag | Descrição |
|------|-----------|
| `-Wall` | Ativa avisos comuns |
| `-Wextra` | Ativa avisos extras |
| `-g` | Inclui informações de depuração (para usar com `gdb`) |
| `-std=c11` | Define o padrão C11 |
| `-std=c++17` | Define o padrão C++17 |

## Como Rodar os Testes

Os testes ficam na pasta `/tests/`. Para executar um teste de entrada/saída:

```bash
# Compilar o programa
gcc -Wall -o prog listas/lista01_io_condicionais/exercicio01.c

# Redirecionar entrada de arquivo e comparar saída
./prog < tests/entrada01.txt > saida_obtida.txt
diff tests/saida_esperada01.txt saida_obtida.txt
```

Se o comando `diff` não produzir saída, o programa está correto.

## Progresso Semanal

Acompanhe a evolução semana a semana na pasta [`/progresso`](./progresso/). Cada arquivo descreve o que foi estudado, as dificuldades encontradas, os aprendizados e as melhorias realizadas.

## Referências

- Linguagem C — K&R: *The C Programming Language* (Kernighan & Ritchie)
- [cppreference.com](https://en.cppreference.com/)
- Slides e materiais fornecidos na disciplina
