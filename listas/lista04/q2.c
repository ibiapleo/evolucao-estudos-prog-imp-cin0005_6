#include <stdio.h>

void simulate(int line, int col, int m, int n, char wall[m][n + 1]) {
    // desce reto enquanto a célula abaixo for vazia
    while (line + 1 < m && wall[line + 1][col] == '.') {
        line++;
        wall[line][col] = 'o';
    }

    // chegou ao fundo ou não tem prateleira abaixo
    if (line + 1 >= m || wall[line + 1][col] != '#') {
        return;
    }

    // achou prateleira, descobre seus limites pra esquerda e pra direita
    int left = col;
    while (left - 1 >= 0 && wall[line + 1][left - 1] == '#') {
        left--;
    }

    int dir = col;
    while (dir + 1 < n && wall[line + 1][dir + 1] == '#') {
        dir++;
    }

    // preenche toda a line acima da prateleira com água
    for (int j = left; j <= dir; j++) {
        wall[line][j] = 'o';
    }

    // tenta derramar para os lados de forma recursiva
    if (left - 1 >= 0 && wall[line][left - 1] == '.') {
        wall[line][left - 1] = 'o';
        simulate(line, left - 1, m, n, wall);
    }

    if (dir + 1 < n && wall[line][dir + 1] == '.') {
        wall[line][dir + 1] = 'o';
        simulate(line, dir + 1, m, n, wall);
    }
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    char wall[m][n + 1]; // +1 para o '\0' que o scanf coloca no final de cada string

    for (int i = 0; i < m; i++) {
        scanf("%s", wall[i]);
    }

    // procura a gota inicial na primeira line
    for (int j = 0; j < n; j++) {
        if (wall[0][j] == 'o') {
            simulate(0, j, m, n, wall); // coloca o ponto inicial da gota na simulação
            break;
        }
    }

    // exibe a wall final com o trajeto da gota
    for (int i = 0; i < m; i++) {
        printf("%s\n", wall[i]);
    }

    return 0;
}