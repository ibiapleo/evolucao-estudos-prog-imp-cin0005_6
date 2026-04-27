#include <stdio.h>
#include <stdlib.h>

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

void calibration(int **mat, int l, int c) { 
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            mat[i][j] = mat[i][j] + 5;
        }
    }
}

void saturation(int **mat, int l, int c) { 
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            mat[i][j] = mat[i][j] > 80 ? 80 : mat[i][j];
        }
    }
}

void amplification(int **mat, int l, int c) {
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            mat[i][j] = mat[i][j] * 2;
        }
    }
}

void pipeline(int **mat, int l, int c) {
    int k; // quantidade de filtros
    scanf("%d", &k);
    int filters[k];
    for (int i = 0; i < k; i++) scanf("%d", &filters[i]);
    for (int i = 0; i < k; i++) {
        if (filters[i] == 1) {
            calibration(mat, l, c);
        } else if (filters[i] == 2) {
            saturation(mat, l, c);
        } else if (filters[i] == 3) {
            amplification(mat, l, c);
        }
    }
}

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
    printf("Posicao: (%d, %d)\n", critical_posx, critical_posy);
}

void free_matrix(int **mat, int l) {
    for (int i = 0; i < l; i++) {
        free(mat[i]);
    }
    free(mat);
}

void read_matrix(int **mat, int l, int c) {
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &mat[i][j]);
        }
    }
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    int **mat = allocate_matrix(n, m);

    read_matrix(mat, n, m);

    int command;
    do {
        scanf("%d", &command);
        switch (command) {
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
    } while (command != 0);

    print_matrix(mat, n, m);
    free_matrix(mat, n);
    return 0;
}
