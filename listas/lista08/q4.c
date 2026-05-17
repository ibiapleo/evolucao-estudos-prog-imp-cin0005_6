#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_TAM 100

typedef struct {
	int codigo;
	char nome[NOME_TAM];
	int quantidade;
	float preco;
} Produto;

typedef struct {
	int codigo;
	char tipo;
	int quantidade;
} Movimento;

typedef struct {
	Movimento movimento;
	char motivo[32];
} Inconsistencia;

/* Busca linear pelo codigo do produto no vetor carregado do arquivo. */
static int buscar_produto(const Produto *produtos, int total_produtos, int codigo) {
	int i;

	for (i = 0; i < total_produtos; i++) {
		if (produtos[i].codigo == codigo) {
			return i;
		}
	}

	return -1;
}

int main(void) {
	FILE *arquivo_produtos = fopen("produtos.txt", "r");
	FILE *arquivo_movimentos = fopen("movimentos.txt", "r");
	FILE *arquivo_estoque;
	FILE *arquivo_relatorio;

	Produto *produtos = NULL;
	Inconsistencia *inconsistencias = NULL;

	int capacidade_produtos = 0;
	int total_produtos = 0;

	int capacidade_inconsistencias = 0;
	int total_inconsistencias = 0;

	int movimentos_aplicados = 0;
	int saidas_recusadas = 0;
	int movimentos_sem_cadastro = 0;

	Movimento movimento;

	if (arquivo_produtos == NULL || arquivo_movimentos == NULL) {
		/* falha em qualquer arquivo de entrada encerra o programa. */
		printf("Erro ao abrir arquivo.\n");

		if (arquivo_produtos != NULL) {
			fclose(arquivo_produtos);
		}
		if (arquivo_movimentos != NULL) {
			fclose(arquivo_movimentos);
		}

		return 1;
	}

	while (1) {
		Produto p;
		int leitura = fscanf(arquivo_produtos, "%d %99s %d %f", &p.codigo, p.nome, &p.quantidade, &p.preco);

		if (leitura != 4) {
			break;
		}

		/* Cresce o vetor dinamicamente para armazenar todos os produtos. */
		if (total_produtos == capacidade_produtos) {
			int nova_capacidade = (capacidade_produtos == 0) ? 8 : capacidade_produtos * 2;
			Produto *novo_vetor = realloc(produtos, (size_t)nova_capacidade * sizeof(Produto));

			if (novo_vetor == NULL) {
				free(produtos);
				free(inconsistencias);
				fclose(arquivo_produtos);
				fclose(arquivo_movimentos);
				return 1;
			}

			produtos = novo_vetor;
			capacidade_produtos = nova_capacidade;
		}

		produtos[total_produtos] = p;
		total_produtos++;
	}

	/* Processa cada movimento e registra inconsistencias sem alterar a ordem dos produtos. */
	while (fscanf(arquivo_movimentos, "%d %c %d", &movimento.codigo, &movimento.tipo, &movimento.quantidade) == 3) {
		int indice_produto = buscar_produto(produtos, total_produtos, movimento.codigo);

		if (indice_produto == -1) {
			Inconsistencia inc;

			movimentos_sem_cadastro++;

			inc.movimento = movimento;
			strcpy(inc.motivo, "PRODUTO_INEXISTENTE");

			if (total_inconsistencias == capacidade_inconsistencias) {
				int nova_capacidade = (capacidade_inconsistencias == 0) ? 8 : capacidade_inconsistencias * 2;
				Inconsistencia *novo_vetor = realloc(
					inconsistencias,
					(size_t)nova_capacidade * sizeof(Inconsistencia)
				);

				if (novo_vetor == NULL) {
					free(produtos);
					free(inconsistencias);
					fclose(arquivo_produtos);
					fclose(arquivo_movimentos);
					return 1;
				}

				inconsistencias = novo_vetor;
				capacidade_inconsistencias = nova_capacidade;
			}

			inconsistencias[total_inconsistencias] = inc;
			total_inconsistencias++;
			continue;
		}

		/* Entrada sempre soma no estoque quando o produto existe. */
		if (movimento.tipo == 'E') {
			produtos[indice_produto].quantidade += movimento.quantidade;
			movimentos_aplicados++;
		} else if (movimento.tipo == 'S') {
			/* Saida so e aplicada quando ha quantidade suficiente em estoque. */
			if (produtos[indice_produto].quantidade >= movimento.quantidade) {
				produtos[indice_produto].quantidade -= movimento.quantidade;
				movimentos_aplicados++;
			} else {
				Inconsistencia inc;

				saidas_recusadas++;

				inc.movimento = movimento;
				strcpy(inc.motivo, "ESTOQUE_INSUFICIENTE");

				if (total_inconsistencias == capacidade_inconsistencias) {
					int nova_capacidade = (capacidade_inconsistencias == 0) ? 8 : capacidade_inconsistencias * 2;
					Inconsistencia *novo_vetor = realloc(
						inconsistencias,
						(size_t)nova_capacidade * sizeof(Inconsistencia)
					);

					if (novo_vetor == NULL) {
						free(produtos);
						free(inconsistencias);
						fclose(arquivo_produtos);
						fclose(arquivo_movimentos);
						return 1;
					}

					inconsistencias = novo_vetor;
					capacidade_inconsistencias = nova_capacidade;
				}

				inconsistencias[total_inconsistencias] = inc;
				total_inconsistencias++;
			}
		}
	}

	fclose(arquivo_produtos);
	fclose(arquivo_movimentos);

	arquivo_estoque = fopen("estoque_atualizado.txt", "w");
	arquivo_relatorio = fopen("relatorio.txt", "w");

	if (arquivo_estoque == NULL || arquivo_relatorio == NULL) {
		printf("Erro ao abrir arquivo.\n");

		if (arquivo_estoque != NULL) {
			fclose(arquivo_estoque);
		}
		if (arquivo_relatorio != NULL) {
			fclose(arquivo_relatorio);
		}

		free(produtos);
		free(inconsistencias);
		return 1;
	}

	/* Escreve o estoque final na mesma ordem em que os produtos foram lidos. */
	{
		int i;

		for (i = 0; i < total_produtos; i++) {
			fprintf(
				arquivo_estoque,
				"%d %s %d %.2f\n",
				produtos[i].codigo,
				produtos[i].nome,
				produtos[i].quantidade,
				produtos[i].preco
			);
		}
	}

	/* Consolida os indicadores exigidos e lista os casos especiais no relatorio. */
	fprintf(arquivo_relatorio, "PRODUTOS PROCESSADOS: %d\n", total_produtos);
	fprintf(arquivo_relatorio, "MOVIMENTOS APLICADOS: %d\n", movimentos_aplicados);
	fprintf(arquivo_relatorio, "SAIDAS RECUSADAS: %d\n", saidas_recusadas);
	fprintf(arquivo_relatorio, "MOVIMENTOS SEM CADASTRO: %d\n", movimentos_sem_cadastro);

	fprintf(arquivo_relatorio, "ESTOQUE BAIXO:\n");
	{
		int i;
		for (i = 0; i < total_produtos; i++) {
			if (produtos[i].quantidade <= 5) {
				fprintf(
					arquivo_relatorio,
					"%d %s %d\n",
					produtos[i].codigo,
					produtos[i].nome,
					produtos[i].quantidade
				);
			}
		}
	}

	fprintf(arquivo_relatorio, "INCONSISTENCIAS:\n");
	{
		int i;
		for (i = 0; i < total_inconsistencias; i++) {
			fprintf(
				arquivo_relatorio,
				"%d %c %d %s\n",
				inconsistencias[i].movimento.codigo,
				inconsistencias[i].movimento.tipo,
				inconsistencias[i].movimento.quantidade,
				inconsistencias[i].motivo
			);
		}
	}

	fclose(arquivo_estoque);
	fclose(arquivo_relatorio);
	free(produtos);
	free(inconsistencias);

	return 0;
}
