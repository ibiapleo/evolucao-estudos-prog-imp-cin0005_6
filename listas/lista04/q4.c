#include <stdio.h>

int m, n;

void decorateLampPole(int line, int column, char park[][n + 1]) {
    // Decora os lados se não quebrar o limite da praça
    if (line + 1 < m)
        park[line + 1][column] = '+';
    if (line - 1 >= 0)
        park[line - 1][column] = '+';
    if (column + 1 < n)
        park[line][column + 1] = '+';
    if (column - 1 >= 0)
        park[line][column - 1] = '+';

    // Decora as diagonais se não quebrar o limite da praça
    if (line + 1 < m && column + 1 < n)
        park[line + 1][column + 1] = 'X';
    if (line + 1 < m && column - 1 >= 0)
        park[line + 1][column - 1] = 'X';
    if (line - 1 >= 0 && column + 1 < n)
        park[line - 1][column + 1] = 'X';
    if (line - 1 >= 0 && column - 1 >= 0)
        park[line - 1][column - 1] = 'X';
}

int main() {
    // Lê as dimensões da praça
    scanf("%d %d", &m, &n);

    char park[m][n + 1]; // +1 para o '\0' que o scanf coloca no final de cada string

    // Lê a configuração da praça
    for (int i = 0; i < m; i++) {
        scanf("%s", park[i]);
    }

    // Procura o poste
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (park[i][j] == 'P') {
                decorateLampPole(i, j, park); // Ao achar o poste, coloca as decorações nele
            }
        }
    }

    // Exibe a praça final com o poste decorado
    for (int i = 0; i < m; i++) {
        printf("%s\n", park[i]);
    }

    return 0;
}