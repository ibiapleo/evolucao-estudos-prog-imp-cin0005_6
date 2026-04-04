#include <stdio.h>

void decorateLampPole(int line, int column, int m, int n, char park[][n + 1]) {
    // Decora os lados se não quebrar o limite da praça
    if (line + 1 < m)
        if (park[line + 1][column] == '-' || park[line + 1][column] == 'x') park[line + 1][column] = '+'; // verifica a condição de poder colocar o enfeite + (se for - ou x, enfeita pois tem prioridade sobre o x, se for + ou P, não faz nada).
    if (line - 1 >= 0)
        if (park[line - 1][column] == '-' || park[line - 1][column] == 'x') park[line - 1][column] = '+';
    if (column + 1 < n)
        if (park[line][column + 1] == '-' || park[line][column + 1] == 'x') park[line][column + 1] = '+';
    if (column - 1 >= 0)
        if (park[line][column - 1] == '-' || park[line][column - 1] == 'x') park[line][column - 1] = '+';

    // Decora as diagonais se não quebrar o limite da praça
    if (line + 1 < m && column + 1 < n)
        if (park[line + 1][column + 1] == '-') park[line + 1][column + 1] = 'x'; // verifica a condição de poder colocar o enfeite na diagonal (só pode colocar se for -, visto que o + tem prioridade e o P é intocável)
    if (line + 1 < m && column - 1 >= 0)
        if (park[line + 1][column - 1] == '-') park[line + 1][column - 1] = 'x';
    if (line - 1 >= 0 && column + 1 < n)
        if (park[line - 1][column + 1] == '-') park[line - 1][column + 1] = 'x';
    if (line - 1 >= 0 && column - 1 >= 0)
        if (park[line - 1][column - 1] == '-') park[line - 1][column - 1] = 'x';
}

int main() {
    // Lê as dimensões da praça
    int m, n; // m e n são respetivamente, o número de linhas e colunas da praça
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
                decorateLampPole(i, j, m, n, park); // Ao achar o poste, coloca as decorações nele
            }
        }
    }

    // Exibe a praça final com o poste decorado
    for (int i = 0; i < m; i++) {
        printf("%s\n", park[i]);
    }

    return 0;
}