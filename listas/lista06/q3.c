#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    FOGO,
    AGUA,
    ELETRICIDADE,
    PLANTA
} TipoElemental;

const char* tipo_para_string(TipoElemental t) {
    switch(t) {
        case FOGO: return "Fogo";
        case AGUA: return "Agua";
        case ELETRICIDADE: return "Eletricidade";
        case PLANTA: return "Planta";
        default: return "";
    }
}

typedef struct {
    int id;
    char nome[50];
    TipoElemental tipo;
    int xp;
    int ataque;
    int ordem_registro;
} Pokemon;

typedef struct {
    char nome[50];
    long long int cpf;
    int idade;
    Pokemon *pokemons;
    int qtd_pokemons;
    int nivel;
    int ordem_cadastro;
} Treinador;

typedef struct Sistema {
    Treinador *treinadores;
    int qtd_treinadores;
    int contador_cadastro;

    void (*cadastrar_treinador)(struct Sistema *s);
    void (*cadastrar_pokemon)(struct Sistema *s);
    void (*listar_classificacao)(struct Sistema *s);
    void (*remover_treinador)(struct Sistema *s);
    void (*atualizar_pokemon)(struct Sistema *s);
} Sistema;

int calcular_forca(Pokemon p) {
    return (2 * p.xp) + p.ataque;
}

void atualizar_nivel(Treinador *t) {
    t->nivel = 0;
    for (int i = 0; i < t->qtd_pokemons; i++) {
        t->nivel += (2 * t->pokemons[i].xp + t->pokemons[i].ataque);
    }
}

void cadastrar_treinador(Sistema *s) {
    char nome[50];
    long long int cpf;
    int idade;
    scanf("%s %lld %d", nome, &cpf, &idade);

    for (int i = 0; i < s->qtd_treinadores; i++) {
        if (s->treinadores[i].cpf == cpf) return;
    }

    s->treinadores = realloc(s->treinadores, (s->qtd_treinadores + 1) * sizeof(Treinador));
    Treinador *t = &s->treinadores[s->qtd_treinadores];
    strcpy(t->nome, nome);
    t->cpf = cpf;
    t->idade = idade;
    t->pokemons = NULL;
    t->qtd_pokemons = 0;
    t->nivel = 0;
    t->ordem_cadastro = s->contador_cadastro++;
    s->qtd_treinadores++;
}

void cadastrar_pokemon(Sistema *s) {
    long long int cpf;
    int id, xp, ataque, tipo_int;
    char nome[50];
    scanf("%lld %d %s %d %d %d", &cpf, &id, nome, &xp, &ataque, &tipo_int);

    for (int i = 0; i < s->qtd_treinadores; i++) {
        if (s->treinadores[i].cpf == cpf) {
            Treinador *t = &s->treinadores[i];
            for (int j = 0; j < t->qtd_pokemons; j++) {
                if (t->pokemons[j].id == id) return;
            }
            t->pokemons = realloc(t->pokemons, (t->qtd_pokemons + 1) * sizeof(Pokemon));
            Pokemon *p = &t->pokemons[t->qtd_pokemons];
            p->id = id;
            strcpy(p->nome, nome);
            p->xp = xp;
            p->ataque = ataque;
            p->tipo = (TipoElemental)tipo_int;
            p->ordem_registro = t->qtd_pokemons;
            t->qtd_pokemons++;
            atualizar_nivel(t);
            return;
        }
    }
}

int cmp_pokemons(const void *a, const void *b) {
    Pokemon *p1 = (Pokemon *)a;
    Pokemon *p2 = (Pokemon *)b;
    int f1 = calcular_forca(*p1);
    int f2 = calcular_forca(*p2);
    if (f1 != f2) return f2 - f1;
    return p1->ordem_registro - p2->ordem_registro;
}

int cmp_treinadores(const void *a, const void *b) {
    Treinador *t1 = (Treinador *)a;
    Treinador *t2 = (Treinador *)b;
    if (t1->nivel != t2->nivel) return t2->nivel - t1->nivel;
    return t1->ordem_cadastro - t2->ordem_cadastro;
}

void listar_classificacao(Sistema *s) {
    printf("Classificacao atual\n");
    if (s->qtd_treinadores == 0) return;

    Treinador *temp = malloc(s->qtd_treinadores * sizeof(Treinador));
    memcpy(temp, s->treinadores, s->qtd_treinadores * sizeof(Treinador));

    qsort(temp, s->qtd_treinadores, sizeof(Treinador), cmp_treinadores);

    for (int i = 0; i < s->qtd_treinadores; i++) {
        printf("T: %s, CPF: %lld, Nivel: %d\n", temp[i].nome, temp[i].cpf, temp[i].nivel);
        if (temp[i].qtd_pokemons > 0) {
            Pokemon *p_temp = malloc(temp[i].qtd_pokemons * sizeof(Pokemon));
            memcpy(p_temp, temp[i].pokemons, temp[i].qtd_pokemons * sizeof(Pokemon));
            qsort(p_temp, temp[i].qtd_pokemons, sizeof(Pokemon), cmp_pokemons);
            for (int j = 0; j < temp[i].qtd_pokemons; j++) {
                printf("  P: %d, %s, %d, %d, %s\n", p_temp[j].id, p_temp[j].nome, p_temp[j].xp, p_temp[j].ataque, tipo_para_string(p_temp[j].tipo));
            }
            free(p_temp);
        }
    }
    free(temp);
}

void remover_treinador(Sistema *s) {
    long long int cpf;
    scanf("%lld", &cpf);
    for (int i = 0; i < s->qtd_treinadores; i++) {
        if (s->treinadores[i].cpf == cpf) {
            free(s->treinadores[i].pokemons);
            for (int j = i; j < s->qtd_treinadores - 1; j++) {
                s->treinadores[j] = s->treinadores[j+1];
            }
            s->qtd_treinadores--;
            if (s->qtd_treinadores > 0) {
                s->treinadores = realloc(s->treinadores, s->qtd_treinadores * sizeof(Treinador));
            } else {
                free(s->treinadores);
                s->treinadores = NULL;
            }
            return;
        }
    }
}

void atualizar_pokemon(Sistema *s) {
    long long int cpf;
    int id, xp, ataque, tipo_int;
    char nome[50];
    scanf("%lld %d %s %d %d %d", &cpf, &id, nome, &xp, &ataque, &tipo_int);

    for (int i = 0; i < s->qtd_treinadores; i++) {
        if (s->treinadores[i].cpf == cpf) {
            Treinador *t = &s->treinadores[i];
            for (int j = 0; j < t->qtd_pokemons; j++) {
                if (t->pokemons[j].id == id) {
                    strcpy(t->pokemons[j].nome, nome);
                    t->pokemons[j].xp = xp;
                    t->pokemons[j].ataque = ataque;
                    t->pokemons[j].tipo = (TipoElemental)tipo_int;
                    atualizar_nivel(t);
                    return;
                }
            }
        }
    }
}

int main() {
    Sistema s;
    s.treinadores = NULL;
    s.qtd_treinadores = 0;
    s.contador_cadastro = 0;
    s.cadastrar_treinador = cadastrar_treinador;
    s.cadastrar_pokemon = cadastrar_pokemon;
    s.listar_classificacao = listar_classificacao;
    s.remover_treinador = remover_treinador;
    s.atualizar_pokemon = atualizar_pokemon;

    int cmd;
    while (scanf("%d", &cmd) && cmd != 0) {
        if (cmd == 1) s.cadastrar_treinador(&s);
        else if (cmd == 2) s.cadastrar_pokemon(&s);
        else if (cmd == 3) s.listar_classificacao(&s);
        else if (cmd == 4) s.remover_treinador(&s);
        else if (cmd == 5) s.atualizar_pokemon(&s);
    }

    for (int i = 0; i < s.qtd_treinadores; i++) {
        free(s.treinadores[i].pokemons);
    }
    free(s.treinadores);

    return 0;
}
