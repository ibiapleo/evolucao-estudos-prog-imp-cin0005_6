#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Aluno {
    long long int matricula;
    int prioridade;
    double cr;
    int l, r, score;
    struct Aluno *prox;
} Aluno;

typedef struct {
    Aluno *inicio;
    Aluno *fim;
} Fila;

Fila* criarFila() {
    Fila *f = (Fila*)malloc(sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

void enqueue(Fila *f, long long int mat, int pri, double cr, int l, int r) {
    Aluno *novo = (Aluno*)malloc(sizeof(Aluno));
    novo->matricula = mat;
    novo->prioridade = pri;
    novo->cr = cr;
    novo->l = l;
    novo->r = r;
    novo->score = (int)round(cr * 100) / pri;
    novo->prox = NULL;

    if (f->inicio == NULL) {
        f->inicio = novo;
        f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }
}

Aluno* dequeue(Fila *f) {
    if (f->inicio == NULL) {
        return NULL;
    }
    Aluno *temp = f->inicio;
    f->inicio = f->inicio->prox;

    if (f->inicio == NULL) {
        f->fim = NULL;  
    } 
    temp->prox = NULL;

    return temp;
}

void imprimirListaOficial(Fila *confirmados, char *disciplina) {
    printf("--- LISTA OFICIAL: %s ---\n", disciplina);
    Aluno *atual = confirmados->inicio;
    int pos = 1;
    while (atual != NULL) {
        printf("%d. Matricula: %lld\n", pos++, atual->matricula);
        atual = atual->prox;
    }
}

void liberarFila(Fila *f) {
    while (f->inicio != NULL) {
        free(dequeue(f));
    }
    free(f);
}

int main() {
    char comando[10], disciplina[50];
    int vagas, tempoAtual = 1;
    Fila *filaEspera = criarFila();
    Fila *confirmados = criarFila();

    while (scanf("%s", comando) != EOF) {
        if (strcmp(comando, "START") == 0) {
            scanf(" %s %d", disciplina, &vagas);
        } else if (strcmp(comando, "ADD") == 0) {
            long long int mat;
            int pri, l, r;
            double cr;
            scanf(" %lld %d %lf %d %d", &mat, &pri, &cr, &l, &r);
            enqueue(filaEspera, mat, pri, cr, l, r);
        } else if (strcmp(comando, "PROC") == 0) {
            int qtd;
            scanf(" %d", &qtd);
            for (int i = 0; i < qtd && filaEspera->inicio != NULL; i++) {
                Aluno *aluno = dequeue(filaEspera);
                if (tempoAtual > aluno->r) {
                    printf("[TIMEOUT] mat=%lld | Desconectado da fila.\n", aluno->matricula);
                } else {
                    if (tempoAtual < aluno->l) tempoAtual = aluno->l;
                    if (vagas > 0) {
                        printf("[ALOCADO] mat=%lld | score=%d | Processado no seg: %d\n", aluno->matricula, aluno->score, tempoAtual);
                        enqueue(confirmados, aluno->matricula, aluno->prioridade, aluno->cr, aluno->l, aluno->r);
                        vagas--;
                    } else {
                        printf("[LOTADO] mat=%lld | score=%d | Processado no seg: %d\n", aluno->matricula, aluno->score, tempoAtual);
                    }
                    tempoAtual++;
                }
                free(aluno);
            }
        } else if (strcmp(comando, "FIM") == 0) {
            imprimirListaOficial(confirmados, disciplina);
            break;
        }
    }

    liberarFila(filaEspera);
    liberarFila(confirmados);
    return 0;
}