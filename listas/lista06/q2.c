#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ── Alocação e cópia de matriz ───────────────────────────────────────

// Aloca uma matriz M x N de inteiros inicializada com zeros
int **alloc_matrix(int rows, int cols) {
    int **mat = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
        mat[i] = (int *)calloc(cols, sizeof(int)); // cada linha zerada
    return mat;
}

// Libera toda a memória de uma matriz alocada dinamicamente
void free_matrix(int **mat, int rows) {
    for (int i = 0; i < rows; i++)
        free(mat[i]); // libera cada linha
    free(mat);        // libera o vetor de ponteiros
}

// Cria e retorna uma cópia independente da matriz de origem
int **copy_matrix(int **src, int rows, int cols) {
    int **dst = alloc_matrix(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            dst[i][j] = src[i][j]; // copia célula a célula
    return dst;
}

// Imprime a matriz no formato esperado pela saída padrão
void print_matrix(int **mat, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j) printf(" "); // espaço entre colunas, mas não antes da primeira
            printf("%d", mat[i][j]);
        }
        printf("\n");
    }
}

// ── Cálculo das camadas de AoE ───────────────────────────────────────

// Retorna uma matriz onde:
//   layer[i][j] == 1  -> camada 1 (centro + ortogonais)
//   layer[i][j] == 2  -> camada 2 (vizinhança da camada 1, excluindo a própria camada 1)
//   layer[i][j] == 0  -> fora da área de efeito
int **compute_layers(int rows, int cols, int cx, int cy) {
    int **layer = alloc_matrix(rows, cols);

    // Deslocamentos para o centro + 4 vizinhos ortogonais (camada 1)
    int row_offset_l1[] = { 0, -1, 1,  0, 0};
    int col_offset_l1[] = { 0,  0, 0, -1, 1};

    // Marca as células da camada 1, ignorando posições fora da matriz
    for (int k = 0; k < 5; k++) {
        int nr = cx + row_offset_l1[k];
        int nc = cy + col_offset_l1[k];
        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols)
            layer[nr][nc] = 1;
    }

    // Deslocamentos para as 8 direções (vizinhança completa)
    int row_offset8[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int col_offset8[] = {-1,  0,  1,-1, 1,-1, 0, 1};

    // Para cada célula da camada 1, marca seus vizinhos como camada 2
    // (somente se ainda não foram marcados como camada 1 ou 2)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (layer[i][j] == 1) {
                for (int k = 0; k < 8; k++) {
                    int nr = i + row_offset8[k];
                    int nc = j + col_offset8[k];
                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && layer[nr][nc] == 0)
                        layer[nr][nc] = 2;
                }
            }
        }
    }
    return layer;
}

// ── Explosão Arcana ──────────────────────────────────────────────────

// Aplica o ataque de explosão arcana e retorna a nova matriz resultante
// Camada 1 recebe 50 de dano; camada 2 recebe 25 de dano
int **arcane_explosion(int **grid, int rows, int cols, int cx, int cy) {
    int **layer  = compute_layers(rows, cols, cx, cy);
    int **result = copy_matrix(grid, rows, cols); // nunca modifica a matriz original

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int damage = 0;
            if      (layer[i][j] == 1) damage = 50; // dano total no centro
            else if (layer[i][j] == 2) damage = 25; // dano reduzido na borda
            if (damage > 0)
                // HP nunca fica negativo
                result[i][j] = (result[i][j] - damage > 0) ? result[i][j] - damage : 0;
        }
    }
    free_matrix(layer, rows);
    return result;
}

// ── Nuvem Venenosa ───────────────────────────────────────────────────

// Conta quantos vizinhos (8 direções) de uma célula possuem HP > 0
int count_living_neighbors(int **grid, int rows, int cols, int row, int col) {
    int row_offset[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int col_offset[] = {-1,  0,  1,-1, 1,-1, 0, 1};
    int count = 0;
    for (int k = 0; k < 8; k++) {
        int nr = row + row_offset[k];
        int nc = col + col_offset[k];
        // verifica limites e se o vizinho ainda está vivo
        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] > 0)
            count++;
    }
    return count;
}

// Aplica um único turno da nuvem venenosa e retorna a nova matriz
// O dano de cada célula depende dos vizinhos vivos no estado atual (antes do turno)
int **poison_cloud_turn(int **grid, int rows, int cols, int cx, int cy) {
    int **layer  = compute_layers(rows, cols, cx, cy);
    int **result = copy_matrix(grid, rows, cols); // cópia para não contaminar os cálculos do turno

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // só aplica dano em células dentro da área e que ainda estejam vivas
            if (layer[i][j] > 0 && grid[i][j] > 0) {
                int neighbors = count_living_neighbors(grid, rows, cols, i, j);
                int damage    = 5 + (8 * neighbors); // fórmula do enunciado
                // HP nunca fica negativo
                result[i][j] = (grid[i][j] - damage > 0) ? grid[i][j] - damage : 0;
            }
        }
    }
    free_matrix(layer, rows);
    return result;
}

// ── Condição de parada ───────────────────────────────────────────────

// Retorna 1 se todas as unidades dentro da área de efeito chegaram a 0 HP
int all_dead_in_area(int **grid, int **layer, int rows, int cols) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (layer[i][j] > 0 && grid[i][j] > 0)
                return 0; // ainda há alguma unidade viva na área
    return 1;
}

// ── Main ─────────────────────────────────────────────────────────────

int main(void) {
    int rows, cols;
    scanf("%d %d", &rows, &cols);

    // Lê o mapa inicial de HP dos jogadores
    int **grid = alloc_matrix(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            scanf("%d", &grid[i][j]);

    // Lê as coordenadas do centro do ataque
    int cx, cy;
    scanf("%d %d", &cx, &cy);

    // Lê o tipo de ataque escolhido
    char attack_type[32];
    scanf("%s", attack_type);

    // Imprime o estado inicial antes de qualquer modificação
    printf("Estado inicial do mapa:\n");
    print_matrix(grid, rows, cols);
    printf("\n");

    if (strcmp(attack_type, "EXPLOSAO_ARCANA") == 0) {
        // Declara o ponteiro para função sem typedef: retorna int**, recebe (int**, int, int, int, int)
        int **(*execute_attack)(int **, int, int, int, int) = arcane_explosion;
        int **result = execute_attack(grid, rows, cols, cx, cy);

        printf("Estado do mapa após usar a Explosão Arcana:\n");
        print_matrix(result, rows, cols);

        free_matrix(result, rows);

    } else if (strcmp(attack_type, "NUVEM_VENENOSA") == 0) {
        // Mesmo padrão de ponteiro para função, agora apontando para poison_cloud_turn
        int **(*execute_attack)(int **, int, int, int, int) = poison_cloud_turn;

        printf("Estado do mapa, por turno, após usar a Nuvem Venenosa:\n");

        // Cópia de trabalho do mapa; será atualizada a cada turno
        int **current = copy_matrix(grid, rows, cols);

        // Calcula as camadas uma única vez (não mudam entre turnos)
        int **layer = compute_layers(rows, cols, cx, cy);

        for (int turn = 1; turn <= 3; turn++) {
            // Aplica o turno e obtém o novo estado
            int **next = execute_attack(current, rows, cols, cx, cy);
            print_matrix(next, rows, cols);

            free_matrix(current, rows); // descarta o estado anterior
            current = next;             // avança para o novo estado

            // Interrompe se todas as unidades na área morreram
            if (all_dead_in_area(current, layer, rows, cols))
                break;

            if (turn < 3)
                printf("\n"); // separa os turnos na saída
        }

        free_matrix(current, rows);
        free_matrix(layer, rows);
    }

    free_matrix(grid, rows);
    return 0;
}