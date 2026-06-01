#include <stdio.h>
#include <stdlib.h>

typedef struct Tarefa {
    int id;
    int prioridade;
    struct Tarefa *prox;
} Tarefa;

typedef struct {
    Tarefa *inicio;
    Tarefa *fim;
} Fila;

Fila* criarFila() {
    Fila *f = (Fila*)malloc(sizeof(Fila));
    if (f == NULL) {
        exit(1);
    }
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

void inserir(Fila *f, int id, int prioridade) {
    Tarefa *nova = (Tarefa *)malloc(sizeof(Tarefa));
    if (nova == NULL) {
        exit(1);
    }

    nova->id = id;
    nova->prioridade = prioridade;
    nova->prox = NULL;

    if (f->inicio == NULL) {
        f->inicio = nova;
        f->fim = nova;
    } else {
        f->fim->prox = nova;
        f->fim = nova;
    }
}

void remover(Fila *f) {
    if (f->inicio == NULL) {
        printf("Fila vazia\n");
        return;
    }

    Tarefa *tmp = f->inicio;
    printf("Removida: id=%d prioridade=%d\n", tmp->id, tmp->prioridade);

    f->inicio = f->inicio->prox;

    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    free(tmp);
}

void listar(Fila *f) {
    if (f->inicio == NULL) {
        printf("Fila vazia\n");
        return;
    }
    Tarefa *atual = f->inicio;
    while (atual != NULL) {
        printf("id=%d prioridade=%d\n", atual->id, atual->prioridade);
        atual = atual->prox;
    }
}

int main()
{
    Fila *tarefas = criarFila();
    char comando;
    int id, prioridade;
    while (scanf(" %c", &comando) != EOF) {
        if (comando == 'I') {
            scanf(" %d %d", &id, &prioridade);
            inserir(tarefas, id, prioridade);
        } else if (comando == 'R') {
            remover(tarefas);
        } else if (comando == 'L') {
            listar(tarefas);
        } else if (comando == 'F') {
            break;
        }
    }

    return 0;
}
