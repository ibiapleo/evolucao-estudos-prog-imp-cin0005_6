# Lista 08 — Unions e Bitfields

## Conteúdo Abordado

- Uso de `union` para acesso direto a um bloco de memória em formatos diferentes.
- Bitfields para mapear campos compactos dentro de bytes/inteiros.
- Combinação de `union` e `struct` para decodificação de mensagens.
- Leitura e escrita de arquivos e processamento de linhas.
- Alocação dinâmica de vetores (`malloc`/`realloc`/`free`).
- Boas práticas de parsing e tratamento de entradas mal formatadas.

## Aprendizados

Nesta lista trabalhei diretamente com representações de baixo nível (bits e bytes) usando `union` e bitfields, aprendi a projetar estruturas que mapeiam campos compactos e a tratar corretamente sinalização de erro e limites. Também pratiquei leitura segura de arquivos, crescimento dinâmico de vetores em C e registro de inconsistências para relatórios.

## Exercícios (resumo, dificuldades e uso de IA)

| Arquivo | Descrição | Dificuldades encontradas | Usei IA? |
|---|---:|---|---:|
| q1.c | Decodificação de um byte com bitfields (error/mode/reading) e impressão dos campos | Entender ordenação e tamanho dos bitfields; garantir leitura segura do valor | Não |
| q2.c | Decodificação de pacotes de 32 bits em campos nomeados (sensorID, status, bateria, temperatura, controle) e impressão formatada | Definir corretamente os tamanhos dos campos e imprimir em hex; gerenciar vetor dinâmico de pacotes | Sim (ajustes no layout dos bitfields e robustez) |
| q3.c | Leitura/parse de CSV (iris), cálculo de médias e moda, reescrita do arquivo com resumo estatístico | Parsing robusto de CSV, crescimento dinâmico do array de linhas e formatação do resumo | Sim (sugestões de parsing e resumo) |
| q4.c | Atualização de estoque a partir de `produtos.txt` e `movimentos.txt`, geração de `estoque_atualizado.txt` e `relatorio.txt` com inconsistências | Tratamento de casos de arquivo ausente, registro de inconsistências e manutenção da ordem do arquivo mestre | Sim (implementação e tratamento de arquivos) |

Observação sobre o uso de IA: marquei acima os exercícios onde utilizei assistência para sugestões e refinamentos. Em todos os casos, revisei e adaptei o código manualmente antes de salvar.

## Exemplos de Entrada e Saída

Exemplo (arquivos):

`produtos.txt`:
```
101 teclado 12 150.00
104 mouse 8 80.00
110 monitor 3 900.00
200 headset 15 250.00
```

`movimentos.txt`:
```
101 S 2
101 S 5
104 E 4
110 S 5
150 E 3
200 S 10
200 S 5
200 S 1
```

Saída esperada — `estoque_atualizado.txt`:
```
101 teclado 5 150.00
104 mouse 12 80.00
110 monitor 3 900.00
200 headset 0 250.00
```

Saída esperada — `relatorio.txt` (resumo):
```
PRODUTOS PROCESSADOS: 4
MOVIMENTOS APLICADOS: 5
SAIDAS RECUSADAS: 2
MOVIMENTOS SEM CADASTRO: 1
ESTOQUE BAIXO:
101 teclado 5
110 monitor 3
200 headset 0
INCONSISTENCIAS:
110 S 5 ESTOQUE_INSUFICIENTE
150 E 3 PRODUTO_INEXISTENTE
200 S 1 ESTOQUE_INSUFICIENTE
```

## Como Compilar

### Linux/MacOS
```bash
gcc -Wall -Wextra -std=c11 q1.c -o q1
gcc -Wall -Wextra -std=c11 q2.c -o q2
gcc -Wall -Wextra -std=c11 q3.c -o q3
gcc -Wall -Wextra -std=c11 q4.c -o q4
./q4
```

### Windows (via gcc MINGW)
```bash
gcc -Wall -Wextra -std=c11 q1.c -o q1.exe
gcc -Wall -Wextra -std=c11 q2.c -o q2.exe
gcc -Wall -Wextra -std=c11 q3.c -o q3.exe
gcc -Wall -Wextra -std=c11 q4.c -o q4.exe
.\q4.exe
```
