
#include <stdio.h>
#include <stdlib.h>

// Função para alocar matriz dinamicamente (ponteiro de ponteiro)
int **allocate_matrix(int l, int c) {
    int **mat = (int **)malloc(l * sizeof(int*));
    for (int i = 0; i < l; i++) {
        mat[i] = (int *)malloc(c * sizeof(int));
    }
    return mat;
}

// Função para ler os elementos da matriz
void read_matrix(int **mat, int l, int c) {
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &mat[i][j]);
        }
    }
}

// Função para imprimir a matriz
void print_matrix(int **mat, int l, int c) {
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            printf("%d", mat[i][j]);
            if (j < c - 1) printf(" ");
        }
        printf("\n");
    }
}

// Função para liberar a matriz
void free_matrix(int **mat, int l) {
    for (int i = 0; i < l; i++) {
        free(mat[i]);
    }
    free(mat);
}

// Funções de operação
int double_number(int x) { return 2 * x; }
int square(int x) { return x * x; }
int absolute(int x) { return x < 0 ? -x : x; }

// Função para aplicar operação em todos os elementos
void apply_operation(int **mat, int l, int c, int (*op)(int)) {
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            mat[i][j] = op(mat[i][j]);
        }
    }
}

int main()
{
    int l, c;
    scanf("%d %d", &l, &c);

    int **mat = allocate_matrix(l, c);
    read_matrix(mat, l, c);

    int op;
    scanf("%d", &op);

    int (*f_op)(int) = NULL;
    if (op == 1) f_op = double_number;
    else if (op == 2) f_op = square;
    else if (op == 3) f_op = absolute;

    if (f_op != NULL) {
        apply_operation(mat, l, c, f_op);
    }

    print_matrix(mat, l, c);
    free_matrix(mat, l);
    return 0;
}
