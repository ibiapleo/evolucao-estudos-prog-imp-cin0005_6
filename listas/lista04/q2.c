#include <stdio.h>

int m, n;

void simular(int linhaInicial, int colunaInicial, char parede[][n + 1]) {

    // pilha de pontos de queda pendentes
    int pilhaLinha[m * n];
    int pilhaColuna[m * n];
    int topo = 0;

    // empurra o ponto inicial na pilha
    pilhaLinha[topo] = linhaInicial;
    pilhaColuna[topo] = colunaInicial;
    topo++;

    while (topo > 0) {
        // pega o próximo ponto de queda
        topo--;
        int linha = pilhaLinha[topo];
        int coluna = pilhaColuna[topo];

        // desce reto enquanto a célula abaixo for vazia
        while (linha + 1 < m && parede[linha + 1][coluna] == '.') {
            linha++;
            parede[linha][coluna] = 'o';
        }

        // chegou ao fundo ou não tem prateleira abaixo, ignora esse ponto
        if (linha + 1 >= m || parede[linha + 1][coluna] != '#') {
            continue;
        }

        // achou prateleira, descobre seus limites pra esquerda e pra direita
        int esq = coluna;
        while (esq - 1 >= 0 && parede[linha + 1][esq - 1] == '#') {
            esq--;
        }

        int dir = coluna;
        while (dir + 1 < n && parede[linha + 1][dir + 1] == '#') {
            dir++;
        }

        // preenche toda a linha acima da prateleira com água
        for (int j = esq; j <= dir; j++) {
            parede[linha][j] = 'o';
        }

        // empurra as bordas na pilha para cair depois para os dois lados
        if (esq - 1 >= 0) {
            parede[linha][esq - 1] = 'o';
            pilhaLinha[topo] = linha;
            pilhaColuna[topo] = esq - 1;
            topo++;
        }
        if (dir + 1 < n) {
            parede[linha][dir + 1] = 'o';
            pilhaLinha[topo] = linha;
            pilhaColuna[topo] = dir + 1;
            topo++;
        }
    }
}

int main() {
    scanf("%d %d", &m, &n);

    char parede[m][n + 1]; // +1 para o '\0' que o scanf coloca no final de cada string

    for (int i = 0; i < m; i++) {
        scanf("%s", parede[i]);
    }

    // procura a gota inicial na primeira linha
    for (int j = 0; j < n; j++) {
        if (parede[0][j] == 'o') {
            simular(0, j, parede); // coloca o ponto inicial da gota na simulação
            break;
        }
    }

    // exibe a parede final com o trajeto da gota
    for (int i = 0; i < m; i++) {
        printf("%s\n", parede[i]);
    }

    return 0;
}