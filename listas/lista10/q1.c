#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    char dado;
    struct No* proximo;
} No;

typedef struct {
    No *topo;
    int tamanho;
} Pilha;

Pilha* criarPilha() {
    Pilha *p = (Pilha*)malloc(sizeof(Pilha));
    if (p != NULL) {
        p->topo = NULL;
        p->tamanho = 0;
    }
    return p;
}

void empilhar(Pilha *p, char c) {
    No *novo = (No*)malloc(sizeof(No));
    if (!novo) {
        exit(1);
    }
    novo->dado = c;
    novo->proximo = p->topo;
    p->topo = novo;
    p->tamanho++;
}

void desempilhar(Pilha *p) {
    if (p->topo == NULL) {
        exit(1);
    }
    No *tmp = p->topo;
    char valor = tmp->dado;
    p->topo = tmp->proximo;
    free(tmp);
    p->tamanho--;
}

void liberar(Pilha *p) {
    while (p->topo != NULL) {
        No *tmp = p->topo;
        p->topo = tmp->proximo;
        free(tmp);
    }
    p->tamanho = 0;
}

void imprimirPilha(Pilha *p) {
    if (p->topo == NULL) {
        printf("Pilha vazia!\n\n");
        return;
    }
    No *atual = p->topo;
    while (atual != NULL) {
        printf("%c\n", atual->dado);
        atual = atual->proximo;
    }
    printf("\n");
}

void processar(Pilha *p) {
    int mudou = 1;
    
    while (mudou && p->tamanho >= 2) {
        mudou = 0;
        
        if (p->tamanho >= 3) {
            char topo = p->topo->dado;
            char abaixo = p->topo->proximo->dado;
            char terceiro = p->topo->proximo->proximo->dado;
            
            if (topo == abaixo && abaixo == terceiro) {
                desempilhar(p); desempilhar(p); desempilhar(p);
                mudou = 1; // Avisa que a pilha mudou, então repita o teste
                continue;  // Volta ao início do while para checar o novo topo
            }
        }
        
        char topo = p->topo->dado;
        char abaixo = p->topo->proximo->dado;
        
        if ((topo == 'g' && abaixo == 'b') || (topo == 'b' && abaixo == 'g')) {
            desempilhar(p); 
            desempilhar(p); 
            empilhar(p, 'c');
            mudou = 1;
        } 
        else if ((topo == 'r' && abaixo == 'b') || (topo == 'b' && abaixo == 'r')) {
            desempilhar(p); 
            desempilhar(p); 
            empilhar(p, 'm');
            mudou = 1;
        }
        else if ((topo == 'r' && abaixo == 'g') || (topo == 'g' && abaixo == 'r')) {
            desempilhar(p); 
            desempilhar(p); 
            empilhar(p, 'y');
            mudou = 1;
        }
    }
}

int main()
{
    Pilha *blocos = criarPilha();
    char entrada;
    while(scanf(" %c", &entrada) != EOF) {
        empilhar(blocos, entrada);
        processar(blocos); 
        imprimirPilha(blocos);
    }
    printf("Thank You So Much For Playing My Game!\n");
    liberar(blocos);
    return 0;
}
