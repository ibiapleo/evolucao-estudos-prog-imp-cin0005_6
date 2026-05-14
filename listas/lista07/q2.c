#include <stdio.h>
#include <string.h>

#define MAX_CIDADES 1000
#define MAX_LEN     210

typedef struct {
    char      nome[MAX_LEN];
    char      funcao[MAX_LEN];
    long long populacao;
    int       periculosidade;
} Cidadela;


void capitalize(char *s) {
    int i;
    if (s[0] == '\0') return;

    if (s[0] >= 'a' && s[0] <= 'z')
        s[0] = s[0] - 'a' + 'A';

    for (i = 1; s[i] != '\0'; i++)
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] = s[i] - 'A' + 'a';
}


int analisar_mensagem(char linha[], int tamanho, Cidadela *cidade, long long *chave) {
    int i, j;
    int eh_especial = 0;

    char nome[MAX_LEN]   = "";  int ni = 0;
    char funcao[MAX_LEN] = "";  int fi = 0;
    long long numero = 0;
    int periculosidade = 0;

    for (i = 0; i < tamanho; i++)
        if (linha[i] == '!') { eh_especial = 1; break; }

    /* percorre cada caractere da linha */
    for (i = 0; i < tamanho; i++) {
        char c = linha[i];

        /* letra maiúscula (A-Z) → nome da cidadela */
        if (c >= 'A' && c <= 'Z')
            nome[ni++] = c;

        /* dígito → concatena ao número (população ou chave) */
        if (c >= '0' && c <= '9')
            numero = numero * 10 + (c - '0');

        /* asterisco → aumenta periculosidade */
        if (c == '*')
            periculosidade++;

        /* duplo espaço → próxima letra → função */
        if (c == ' ' && i + 1 < tamanho && linha[i + 1] == ' ') {
            /* avança j até o 1º caractere não-espaço */
            j = i + 2;
            while (j < tamanho && linha[j] == ' ')
                j++;

            /* apenas letras ASCII contribuem para a função */
            if (j < tamanho &&
                ((linha[j] >= 'a' && linha[j] <= 'z') ||
                 (linha[j] >= 'A' && linha[j] <= 'Z')))
            {
                funcao[fi++] = linha[j];
            }

            /* pula direto para o caractere encontrado
               (o for vai fazer i++, chegando exatamente em j) */
            i = j - 1;
        }
    }

    nome[ni]   = '\0';
    funcao[fi] = '\0';

    capitalize(nome);
    capitalize(funcao);

    if (eh_especial) {
        *chave = numero;
        return 1;
    }

    cidade->populacao      = numero;
    cidade->periculosidade = periculosidade;
    strcpy(cidade->nome,   nome);
    strcpy(cidade->funcao, funcao);
    return 0;
}

void trocar(Cidadela *a, Cidadela *b) {
    Cidadela tmp = *a;
    *a = *b;
    *b = tmp;
}

int vem_antes(Cidadela *a, Cidadela *b) {
    if (a->populacao != b->populacao)
        return a->populacao > b->populacao;

    if (a->periculosidade != b->periculosidade)
        return a->periculosidade > b->periculosidade;

    return strcmp(a->nome, b->nome) < 0;
}

void ordenar(Cidadela cidades[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - 1 - i; j++)
            if (!vem_antes(&cidades[j], &cidades[j + 1]))
                trocar(&cidades[j], &cidades[j + 1]);
}

int main(void) {
    Cidadela  cidades[MAX_CIDADES];
    int       total = 0;
    long long chave = -1;

    char linha[MAX_LEN];

    /* lê mensagens até EOF */
    while (fgets(linha, sizeof(linha), stdin) != NULL) {
        /* remove '\n' e '\r' do final */
        int tam = (int)strlen(linha);
        while (tam > 0 && (linha[tam-1] == '\n' || linha[tam-1] == '\r'))
            linha[--tam] = '\0';

        if (tam == 0) continue;

        Cidadela tmp;
        long long k = -1;

        if (analisar_mensagem(linha, tam, &tmp, &k)) {
            chave = k;               /* mensagem especial: guarda a chave */
        } else {
            cidades[total++] = tmp;  /* mensagem normal: cadastra cidadela */
        }
    }

    if (chave < 0) {
        printf("Gingrey ainda não foi achada, vamos esperar mais um pouco.\n");
        return 0;
    }

    ordenar(cidades, total);

    if (chave < 1 || chave > total) {
        printf("Gingrey ainda não foi achada, vamos esperar mais um pouco.\n");
        return 0;
    }

    Cidadela *g = &cidades[chave - 1];   /* chave é 1-indexada */

    char peric[MAX_LEN];
    int  i;
    for (i = 0; i < g->periculosidade; i++)
        peric[i] = '*';
    peric[g->periculosidade] = '\0';

    printf("Gingrey foi encontrada em %s, uma cidadela com %lld mil habitantes cuja função é %s e periculosidade %s. ", g->nome, g->populacao, g->funcao, peric);

    int densa    = (g->populacao      >= 1000);
    int perigosa = (g->periculosidade >  3);

    if (densa && perigosa) {
        printf("Talvez seja melhor desistir...\n");
    } else if (densa) {
        printf("Um lugar denso, vai ser difícil achar ela.\n");
    } else if (perigosa) {
        printf("Vai ser complicado entrar lá.\n");
    }

    return 0;
}