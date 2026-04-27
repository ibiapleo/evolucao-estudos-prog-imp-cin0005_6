#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **alocar_matriz(int m, int n) {
	int **mat = malloc(m * sizeof(int*));
	for (int i = 0; i < m; i++)
		mat[i] = malloc(n * sizeof(int));
	return mat;
}

void liberar_matriz(int **mat, int m) {
	for (int i = 0; i < m; i++)
		free(mat[i]);
	free(mat);
}

void ler_matriz(int **mat, int m, int n) {
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &mat[i][j]);
}

void imprimir_matriz(int **mat, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d", mat[i][j]);
			if (j < n-1) printf(" ");
		}
		printf("\n");
	}
}

int **copiar_matriz(int **mat, int m, int n) {
	int **nova = alocar_matriz(m, n);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			nova[i][j] = mat[i][j];
	return nova;
}

// Função para Explosão Arcana
int **explosao_arcana(int **mat, int m, int n, int x, int y) {
	int **res = copiar_matriz(mat, m, n);
	int dx1[] = {0, -1, 1, 0, 0};
	int dy1[] = {0, 0, 0, -1, 1};
	// Camada 1
	for (int d = 0; d < 5; d++) {
		int nx = x + dx1[d];
		int ny = y + dy1[d];
		if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
			int dano = 50;
			res[nx][ny] = res[nx][ny] - dano;
			if (res[nx][ny] < 0) res[nx][ny] = 0;
		}
	}
	// Camada 2
	int dx2[] = {-1,-1,-1,0,0,1,1,1};
	int dy2[] = {-1,0,1,-1,1,-1,0,1};
	for (int d = 0; d < 8; d++) {
		int cx = x + dx2[d];
		int cy = y + dy2[d];
		// Se já está na camada 1, ignora
		int camada1 = 0;
		for (int k = 0; k < 5; k++) {
			if (cx == x + dx1[k] && cy == y + dy1[k]) camada1 = 1;
		}
		if (!camada1 && cx >= 0 && cx < m && cy >= 0 && cy < n) {
			int dano = 25;
			res[cx][cy] = res[cx][cy] - dano;
			if (res[cx][cy] < 0) res[cx][cy] = 0;
		}
	}
	return res;
}

// Função auxiliar para contar vizinhos vivos
int contar_vizinhos_vivos(int **mat, int m, int n, int i, int j) {
	int vivos = 0;
	for (int di = -1; di <= 1; di++) {
		for (int dj = -1; dj <= 1; dj++) {
			if (di == 0 && dj == 0) continue;
			int ni = i + di;
			int nj = j + dj;
			if (ni >= 0 && ni < m && nj >= 0 && nj < n && mat[ni][nj] > 0)
				vivos++;
		}
	}
	return vivos;
}

// Função para Nuvem Venenosa
// Retorna vetor de matrizes, e coloca em *turnos o número de turnos executados
int ***nuvem_venenosa(int **mat, int m, int n, int x, int y, int *turnos) {
	int ***resultados = malloc(3 * sizeof(int**));
	int **atual = copiar_matriz(mat, m, n);
	int dx1[] = {0, -1, 1, 0, 0};
	int dy1[] = {0, 0, 0, -1, 1};
	int dx2[] = {-1,-1,-1,0,0,1,1,1};
	int dy2[] = {-1,0,1,-1,1,-1,0,1};
	// Montar máscara da área de efeito
	int **mask = alocar_matriz(m, n);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			mask[i][j] = 0;
	// Camada 1
	for (int d = 0; d < 5; d++) {
		int nx = x + dx1[d];
		int ny = y + dy1[d];
		if (nx >= 0 && nx < m && ny >= 0 && ny < n)
			mask[nx][ny] = 1;
	}
	// Camada 2
	for (int d = 0; d < 8; d++) {
		int cx = x + dx2[d];
		int cy = y + dy2[d];
		int camada1 = 0;
		for (int k = 0; k < 5; k++) {
			if (cx == x + dx1[k] && cy == y + dy1[k]) camada1 = 1;
		}
		if (!camada1 && cx >= 0 && cx < m && cy >= 0 && cy < n)
			mask[cx][cy] = 1;
	}
	*turnos = 0;
	for (int t = 0; t < 3; t++) {
		int **prox = copiar_matriz(atual, m, n);
		int vivos = 0;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (mask[i][j] && atual[i][j] > 0) {
					int viz = contar_vizinhos_vivos(atual, m, n, i, j);
					int dano = 5 + 8 * viz;
					prox[i][j] -= dano;
					if (prox[i][j] < 0) prox[i][j] = 0;
					if (prox[i][j] > 0) vivos = 1;
				}
			}
		}
		resultados[t] = prox;
		liberar_matriz(atual, m);
		atual = copiar_matriz(prox, m, n);
		(*turnos)++;
		if (!vivos) {
			liberar_matriz(atual, m);
			break;
		}
	}
	liberar_matriz(mask, m);
	return resultados;
}

int main() {
	int m, n;
	scanf("%d %d", &m, &n);
	int **mat = alocar_matriz(m, n);
	ler_matriz(mat, m, n);
	int x, y;
	scanf("%d %d", &x, &y);
	char ataque[32];
	scanf("%s", ataque);

	printf("Estado inicial do mapa:\n");
	imprimir_matriz(mat, m, n);
	printf("\n");

	if (strcmp(ataque, "EXPLOSAO_ARCANA") == 0) {
		int **res = explosao_arcana(mat, m, n, x, y);
		printf("Estado do mapa apos usar a Explosao Arcana:\n");
		imprimir_matriz(res, m, n);
		liberar_matriz(res, m);
	} else if (strcmp(ataque, "NUVEM_VENENOSA") == 0) {
		int turnos = 0;
		int ***resultados = nuvem_venenosa(mat, m, n, x, y, &turnos);
		for (int t = 0; t < turnos; t++) {
			printf("Estado do mapa apos o turno %d:\n", t+1);
			imprimir_matriz(resultados[t], m, n);
			liberar_matriz(resultados[t], m);
		}
		free(resultados);
	}
	liberar_matriz(mat, m);
	return 0;
}
