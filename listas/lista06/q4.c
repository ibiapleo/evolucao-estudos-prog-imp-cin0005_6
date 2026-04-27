#include <stdio.h>
#include <stdlib.h>

// Operações
void calibration(int **mat, int l, int c) { 
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            mat[i][j] = mat[i][j] + 5; // calibração adiciona 5 a cada elemento
        }
    }
}
void saturation(int **mat, int l, int c) { 
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            mat[i][j] = mat[i][j] > 80 ? 80 : mat[i][j]; // saturação limita os valores a 80
        }
    }
}
void amplification(int **mat, int l, int c) {
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            mat[i][j] = mat[i][j] * 2; // amplificação dobra os valores
        }
    }
}
void pipeline(int **mat, int l, int c) {
    int k; // quantidade de filtros
    scanf("%d", &k);
    int filters[k]; // array para armazenar os filtros a serem aplicados
    for (int i = 0; i < k; i++) scanf("%d", &filters[i]); // leitura dos filtros
    for (int i = 0; i < k; i++) { // aplicação dos filtros na ordem lida
        if (filters[i] == 1) {
            calibration(mat, l, c);
        } else if (filters[i] == 2) {
            saturation(mat, l, c);
        } else if (filters[i] == 3) {
            amplification(mat, l, c);
        }
    }
}

// Função para alocar matriz dinamicamente (ponteiro de ponteiro)
int **allocate_matrix(int l, int c) {
    int **mat = (int **)malloc(l * sizeof(int*));

    if (mat == NULL) {
        printf("Erro ao alocar memória para a matriz.\n");
        exit(1);
    }

    for (int i = 0; i < l; i++) {
        mat[i] = (int *)malloc(c * sizeof(int));
        if (mat[i] == NULL) {
            printf("Erro ao alocar memória para a coluna %d.\n", i);
            exit(1);
        }
    }

    return mat;
}


// Função para liberar a matriz
void free_matrix(int **mat, int l) {
    for (int i = 0; i < l; i++) {
        free(mat[i]);
    }
    free(mat);
}

// Função para ler os elementos da matriz
void read_matrix(int **mat, int l, int c) {
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &mat[i][j]);
        }
    }
}

// Função para imprimir o resultado final
void print_matrix(int **mat, int l, int c) {
    printf("Matriz processada:\n");
    int critical_value = 0;
    int critical_posx = 0, critical_posy = 0;
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            printf("%d ", mat[i][j]);
            if (mat[i][j] > critical_value) {
                critical_value = mat[i][j];
                critical_posx = i;
                critical_posy = j;
            }
        }
        printf("\n");
    }
    printf("\nSensor critico: %d\n", critical_value);
    printf("Posicao: (%d,%d)\n", critical_posx, critical_posy);
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m); // leitura do número de linhas (n) e colunas (m) da matriz

    int **mat = allocate_matrix(n, m); // alocação dinâmica da matriz

    read_matrix(mat, n, m); // leitura dos elementos da matriz

    int command; // comando para escolher a operação a ser aplicada
    do {
        scanf("%d", &command);
        switch (command) { // aplicação da operação escolhida
            case 1:
                calibration(mat, n, m);
                break;
            case 2:
                saturation(mat, n, m);
                break;
            case 3:
                amplification(mat, n, m);
                break;
            case 4:
                pipeline(mat, n, m);
                break;
            default:
                break;
        } 
    } while (command != 0); // o loop continua até que o comando 0 seja lido, indicando o fim das operações

    print_matrix(mat, n, m); // impressão do resultado final
    free_matrix(mat, n); // liberação da memória alocada para a matriz
    return 0;
}
