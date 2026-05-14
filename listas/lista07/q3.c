#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Mecha Mecha;

typedef struct {
    char nome[30];
    int atrib1;
    int atrib2;
    void (*subrotina)(Mecha *m, int slot, int input, int *output);
} SubSistema;

struct Mecha {
    int id;
    char modelo[50];
    int energia_atual;
    int num_sistemas;
    int valor_wintermute;
    SubSistema sistemas[];
};


void subrotina_defesa(Mecha *m, int slot, int input, int *output) {
    int dano_final = input - m->sistemas[slot].atrib1 - (slot * m->sistemas[slot].atrib2);
    if (dano_final < 0) {
        dano_final = 0;
    }
    *output = dano_final;
}

void subrotina_utilidade(Mecha *m, int slot, int input, int *output) {
    int recuperado = m->sistemas[slot].atrib1 + (slot * m->sistemas[slot].atrib2);
    m->energia_atual += recuperado;
    *output = m->energia_atual;
}

void subrotina_ataque(Mecha *m, int slot, int input, int *output) {
    if (m->energia_atual < m->sistemas[slot].atrib2) {
        *output = -1;
    } else {
        int dano = m->sistemas[slot].atrib1 + m->energia_atual + slot - input;
        m->energia_atual -= m->sistemas[slot].atrib2;
        *output = dano;
    }
}

int main() {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    Mecha **esquadrao = (Mecha **)malloc(N * sizeof(Mecha *));

    for (int i = 0; i < N; i++) {
        int id, energia, num_sistemas;
        char modelo[50];
        scanf("%d %s %d %d", &id, modelo, &energia, &num_sistemas);

        Mecha *m = (Mecha *)malloc(sizeof(Mecha) + num_sistemas * sizeof(SubSistema));
        
        m->id = id;
        strcpy(m->modelo, modelo);
        m->energia_atual = energia;
        m->num_sistemas = num_sistemas;

        for (int j = 0; j < num_sistemas; j++) {
            char tipo;
            char nome[30];
            int at1, at2;
            scanf(" %c %s %d %d", &tipo, nome, &at1, &at2);

            strcpy(m->sistemas[j].nome, nome);
            m->sistemas[j].atrib1 = at1;
            m->sistemas[j].atrib2 = at2;

            if (tipo == 'D') {
                m->sistemas[j].subrotina = subrotina_defesa;
            } else if (tipo == 'U') {
                m->sistemas[j].subrotina = subrotina_utilidade;
            } else if (tipo == 'A') {
                m->sistemas[j].subrotina = subrotina_ataque;
            }
        }
        
        scanf("%d", &m->valor_wintermute);
        esquadrao[i] = m;
    }

    // Ordenação do esquadrão em ordem crescente de IDs (Bubble Sort)
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (esquadrao[j]->id > esquadrao[j + 1]->id) {
                Mecha *temp = esquadrao[j];
                esquadrao[j] = esquadrao[j + 1];
                esquadrao[j + 1] = temp;
            }
        }
    }

    // Fase de Combate
    printf("[RELATORIO DE MISSÃO: OPERAÇÃO LANÇA DE NETUNO]\n");

    for (int i = 0; i < N; i++) {
        Mecha *m = esquadrao[i];
        int energia_inicial = m->energia_atual; // Captura para o cabeçalho antes do processamento

        printf("ID: %d | MECHA: %s | ENERGIA: %d\n", m->id, m->modelo, energia_inicial);

        int output;

        // Prioridade 1: Defesa
        for (int j = 0; j < m->num_sistemas; j++) {
            if (m->sistemas[j].subrotina == subrotina_defesa) {
                m->sistemas[j].subrotina(m, j, m->valor_wintermute, &output);
                printf("-> [DEFESA] %s | Dano final sofrido: %d\n", m->sistemas[j].nome, output);
            }
        }

        // Prioridade 2: Utilidade
        for (int j = 0; j < m->num_sistemas; j++) {
            if (m->sistemas[j].subrotina == subrotina_utilidade) {
                m->sistemas[j].subrotina(m, j, m->valor_wintermute, &output);
                printf("-> [UTILIDADE] %s | Energia atual: %d\n", m->sistemas[j].nome, output);
            }
        }

        // Prioridade 3: Ataque
        for (int j = 0; j < m->num_sistemas; j++) {
            if (m->sistemas[j].subrotina == subrotina_ataque) {
                m->sistemas[j].subrotina(m, j, m->valor_wintermute, &output);
                if (output == -1) {
                    printf("-> [ATAQUE] %s | Energia insuficiente!\n", m->sistemas[j].nome);
                } else {
                    printf("-> [ATAQUE] %s | Dano causado: %d | Energia restante: %d\n", m->sistemas[j].nome, output, m->energia_atual);
                }
            }
        }

        printf("ENERGIA FINAL: %d\n", m->energia_atual);
        printf("-----------------------------------------\n");
    }

    printf("Esquadrao pronto para o combate.\n");

    for (int i = 0; i < N; i++) {
        free(esquadrao[i]);
    }
    free(esquadrao);

    return 0;
}