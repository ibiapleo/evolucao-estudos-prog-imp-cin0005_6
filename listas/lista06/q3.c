#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes para os tipos elementais dos Pokémons 
#define TYPE_FIRE     0
#define TYPE_WATER    1
#define TYPE_ELECTRIC 2
#define TYPE_PLANT    3

// Constantes de limite
#define MAX_NAME 100
#define MAX_CPF  50

// Cada índice i representa um treinador:
//   trainer_name[i]       -> nome
//   trainer_cpf[i]        -> CPF
//   trainer_age[i]        -> idade
//   trainer_level[i]      -> nível (calculado)
//   trainer_order[i]      -> ordem de cadastro (para desempate)
//   trainer_count         -> quantidade total de treinadores
static char   **trainer_name  = NULL;
static char   **trainer_cpf   = NULL;
static int     *trainer_age   = NULL;
static int     *trainer_level = NULL;
static int     *trainer_order = NULL;
static int      trainer_count = 0;

// Cada índice j representa um pokémon:
//   poke_owner[j]   -> índice do treinador dono
//   poke_id[j]      -> ID do pokémon (único por treinador)
//   poke_name[j]    -> nome
//   poke_xp[j]      -> pontos de experiência
//   poke_atk[j]     -> ataque
//   poke_type[j]    -> tipo elemental (enum)
//   poke_reg[j]     -> ordem de registro (para desempate)
//   poke_count      -> quantidade total de pokémons
static int    *poke_owner = NULL;
static int    *poke_id    = NULL;
static char  **poke_name  = NULL;
static int    *poke_xp    = NULL;
static int    *poke_atk   = NULL;
static int    *poke_type  = NULL;
static int    *poke_reg   = NULL;
static int     poke_count = 0;
static int     poke_reg_counter = 0; // contador global de registro de pokémons 

// Contador global de ordem de cadastro de treinadores
static int trainer_reg_counter = 0;

// --------------- Funções auxiliares de alocação de strings ---------------

/* Duplica uma string usando malloc */
char *dup_string(const char *src) {
    // aloca memória para copiar a string
    char *dst = (char *)malloc((strlen(src) + 1) * sizeof(char));
    if (dst) strcpy(dst, src);
    return dst;
}

// --------------- Funções de cálculo ---------------

/* Calcula a força de um pokémon: Força = (2 * XP) + Ataque */
int calc_pokemon_strength(int xp, int atk) {
    // fórmula de força do pokémon
    return (2 * xp) + atk;
}

/* Recalcula o nível de um treinador pelo índice */
void recalc_trainer_level(int t_idx) {
    // soma a força de todos os pokémons do treinador
    int level = 0;
    for (int j = 0; j < poke_count; j++) {
        if (poke_owner[j] == t_idx) {
            level += calc_pokemon_strength(poke_xp[j], poke_atk[j]);
        }
    }
    trainer_level[t_idx] = level;
}

// Conversão de tipo elemental para string
const char *type_to_string(int type) {
    // retorna o nome do tipo como string
    if (type == TYPE_FIRE)     return "Fogo";
    if (type == TYPE_WATER)    return "Agua";
    if (type == TYPE_ELECTRIC) return "Eletricidade";
    return "Planta";
}

// Converte string lida do input para enum de tipo
int string_to_type(const char *s) {
    // mapeia o número lido para o tipo elemental: 0=Fogo, 1=Agua, 2=Eletricidade, 3=Planta
    int val = atoi(s);
    if (val == 0) return TYPE_FIRE;
    if (val == 1) return TYPE_WATER;
    if (val == 2) return TYPE_ELECTRIC;
    return TYPE_PLANT;
}

// Encontra índice do treinador pelo CPF, retorna -1 se não achar
int find_trainer_by_cpf(const char *cpf) {
    // percorre todos os treinadores buscando o CPF
    for (int i = 0; i < trainer_count; i++) {
        if (strcmp(trainer_cpf[i], cpf) == 0) return i;
    }
    return -1;
}

// Encontra índice do pokémon pelo dono e ID
int find_pokemon(int t_idx, int pid) {
    // percorre os pokémons buscando o ID dentro do treinador
    for (int j = 0; j < poke_count; j++) {
        if (poke_owner[j] == t_idx && poke_id[j] == pid) return j;
    }
    return -1;
}

// --------------- Operações principais ---------------

// Comando 1: Cadastrar Treinador
void op_register_trainer(void) {
    char name[MAX_NAME], cpf[MAX_CPF];
    int  age;
    // lê os dados do treinador
    scanf("%s %s %d", name, cpf, &age);

    // verifica se CPF já existe
    if (find_trainer_by_cpf(cpf) != -1) return;

    // expande os arrays paralelos de treinadores
    int idx = trainer_count;
    trainer_name  = (char **)realloc(trainer_name,  (idx + 1) * sizeof(char *));
    trainer_cpf   = (char **)realloc(trainer_cpf,   (idx + 1) * sizeof(char *));
    trainer_age   = (int *)  realloc(trainer_age,   (idx + 1) * sizeof(int));
    trainer_level = (int *)  realloc(trainer_level, (idx + 1) * sizeof(int));
    trainer_order = (int *)  realloc(trainer_order, (idx + 1) * sizeof(int));

    // armazena os dados do novo treinador
    trainer_name[idx]  = dup_string(name);
    trainer_cpf[idx]   = dup_string(cpf);
    trainer_age[idx]   = age;
    trainer_level[idx] = 0;
    trainer_order[idx] = trainer_reg_counter++;
    trainer_count++;
}

// Comando 2: Cadastrar Pokémon
void op_register_pokemon(void) {
    char cpf[MAX_CPF], pname[MAX_NAME], stype[10];
    int  pid, xp, atk;
    // lê os dados do pokémon
    scanf("%s %d %s %d %d %s", cpf, &pid, pname, &xp, &atk, stype);

    // encontra o treinador pelo CPF
    int t_idx = find_trainer_by_cpf(cpf);
    if (t_idx == -1) return;

    // verifica se o ID já existe para este treinador
    if (find_pokemon(t_idx, pid) != -1) return;

    // expande os arrays paralelos de pokémons
    int idx = poke_count;
    poke_owner = (int *)  realloc(poke_owner, (idx + 1) * sizeof(int));
    poke_id    = (int *)  realloc(poke_id,    (idx + 1) * sizeof(int));
    poke_name  = (char **)realloc(poke_name,  (idx + 1) * sizeof(char *));
    poke_xp    = (int *)  realloc(poke_xp,    (idx + 1) * sizeof(int));
    poke_atk   = (int *)  realloc(poke_atk,   (idx + 1) * sizeof(int));
    poke_type  = (int *)  realloc(poke_type,  (idx + 1) * sizeof(int));
    poke_reg   = (int *)  realloc(poke_reg,   (idx + 1) * sizeof(int));

    // armazena os dados do novo pokémon
    poke_owner[idx] = t_idx;
    poke_id[idx]    = pid;
    poke_name[idx]  = dup_string(pname);
    poke_xp[idx]    = xp;
    poke_atk[idx]   = atk;
    poke_type[idx]  = string_to_type(stype);
    poke_reg[idx]   = poke_reg_counter++;
    poke_count++;

    // recalcula nível do treinador após novo pokémon
    recalc_trainer_level(t_idx);
}

// Comando 3: Listar Classificação
void op_list_ranking(void) {
    // cria array de índices de treinadores para ordenar
    int *order = (int *)malloc(trainer_count * sizeof(int));
    for (int i = 0; i < trainer_count; i++) order[i] = i;

    // ordena por nível (decrescente) e, em empate, por ordem de cadastro
    for (int i = 0; i < trainer_count - 1; i++) {
        for (int j = i + 1; j < trainer_count; j++) {
            int should_swap = 0;
            // compara nível
            if (trainer_level[order[j]] > trainer_level[order[i]]) {
                should_swap = 1;
            } else if (trainer_level[order[j]] == trainer_level[order[i]]) {
                // desempate por ordem de cadastro (menor índice = cadastrou antes)
                if (trainer_order[order[j]] < trainer_order[order[i]]) {
                    should_swap = 1;
                }
            }
            if (should_swap) {
                int tmp   = order[i];
                order[i]  = order[j];
                order[j]  = tmp;
            }
        }
    }

    // imprime o cabeçalho da classificação
    printf("Classificação atual\n");

    // percorre treinadores na ordem classificada
    for (int i = 0; i < trainer_count; i++) {
        int t = order[i];
        printf("T: %s, CPF: %s, Nivel: %d\n",
               trainer_name[t], trainer_cpf[t], trainer_level[t]);

        // cria array de índices dos pokémons deste treinador
        int *porder = (int *)malloc(poke_count * sizeof(int));
        int  pcnt   = 0;
        for (int j = 0; j < poke_count; j++) {
            if (poke_owner[j] == t) porder[pcnt++] = j;
        }

        // ordena pokémons por força (decrescente) e, em empate, por ordem de registro
        for (int a = 0; a < pcnt - 1; a++) {
            for (int b = a + 1; b < pcnt; b++) {
                int fa = calc_pokemon_strength(poke_xp[porder[a]], poke_atk[porder[a]]);
                int fb = calc_pokemon_strength(poke_xp[porder[b]], poke_atk[porder[b]]);
                int swap = 0;
                if (fb > fa) {
                    swap = 1;
                } else if (fb == fa) {
                    // desempate por ordem de registro
                    if (poke_reg[porder[b]] < poke_reg[porder[a]]) {
                        swap = 1;
                    }
                }
                if (swap) {
                    int tmp     = porder[a];
                    porder[a]   = porder[b];
                    porder[b]   = tmp;
                }
            }
        }

        // imprime cada pokémon do treinador
        for (int k = 0; k < pcnt; k++) {
            int p = porder[k];
            printf("  P: %d, %s, %d, %d, %s\n",
                   poke_id[p], poke_name[p],
                   poke_xp[p], poke_atk[p],
                   type_to_string(poke_type[p]));
        }

        free(porder);
    }

    free(order);
}

// Comando 4: Remover Treinador
void op_remove_trainer(void) {
    char cpf[MAX_CPF];
    // lê o CPF do treinador a remover
    scanf("%s", cpf);

    int t_idx = find_trainer_by_cpf(cpf);
    if (t_idx == -1) return;

    // libera memória do treinador removido
    free(trainer_name[t_idx]);
    free(trainer_cpf[t_idx]);

    // remove os pokémons do treinador, compactando o array
    int new_poke_count = 0;
    for (int j = 0; j < poke_count; j++) {
        if (poke_owner[j] == t_idx) {
            // libera pokémon que pertence ao treinador removido
            free(poke_name[j]);
        } else {
            // mantém o pokémon, atualizando o índice do dono se necessário
            int new_owner = poke_owner[j];
            if (new_owner > t_idx) new_owner--;
            poke_owner[new_poke_count] = new_owner;
            poke_id[new_poke_count]    = poke_id[j];
            poke_name[new_poke_count]  = poke_name[j];
            poke_xp[new_poke_count]    = poke_xp[j];
            poke_atk[new_poke_count]   = poke_atk[j];
            poke_type[new_poke_count]  = poke_type[j];
            poke_reg[new_poke_count]   = poke_reg[j];
            new_poke_count++;
        }
    }
    poke_count = new_poke_count;

    // compacta o array de treinadores removendo o treinador no índice t_idx
    for (int i = t_idx; i < trainer_count - 1; i++) {
        trainer_name[i]  = trainer_name[i + 1];
        trainer_cpf[i]   = trainer_cpf[i + 1];
        trainer_age[i]   = trainer_age[i + 1];
        trainer_level[i] = trainer_level[i + 1];
        trainer_order[i] = trainer_order[i + 1];
    }
    trainer_count--;
}

// Comando 5: Atualizar Pokémon
void op_update_pokemon(void) {
    char cpf[MAX_CPF], pname[MAX_NAME], stype[10];
    int  pid, xp, atk;
    // lê os dados do pokémon a atualizar
    scanf("%s %d %s %d %d %s", cpf, &pid, pname, &xp, &atk, stype);

    int t_idx = find_trainer_by_cpf(cpf);
    if (t_idx == -1) return;

    int p_idx = find_pokemon(t_idx, pid);
    if (p_idx == -1) return;

    // atualiza os dados do pokémon
    free(poke_name[p_idx]);
    poke_name[p_idx] = dup_string(pname);
    poke_xp[p_idx]   = xp;
    poke_atk[p_idx]  = atk;
    poke_type[p_idx] = string_to_type(stype);

    // recalcula o nível do treinador após atualização
    recalc_trainer_level(t_idx);
}

// Libera toda a memória alocada ao encerrar
void free_all(void) {
    // libera nomes e CPFs dos treinadores
    for (int i = 0; i < trainer_count; i++) {
        free(trainer_name[i]);
        free(trainer_cpf[i]);
    }
    free(trainer_name);
    free(trainer_cpf);
    free(trainer_age);
    free(trainer_level);
    free(trainer_order);

    // libera nomes dos pokémons
    for (int j = 0; j < poke_count; j++) {
        free(poke_name[j]);
    }
    free(poke_owner);
    free(poke_id);
    free(poke_name);
    free(poke_xp);
    free(poke_atk);
    free(poke_type);
    free(poke_reg);
}

int main(void) {
    void (*ops[6])(void); // Ponteiro pra armazenar ponteiros pra funções
    ops[0] = NULL;                  // comando 0 tratado no loop
    ops[1] = op_register_trainer;   // cadastrar treinador
    ops[2] = op_register_pokemon;   // cadastrar pokémon
    ops[3] = op_list_ranking;       // listar classificação
    ops[4] = op_remove_trainer;     // remover treinador
    ops[5] = op_update_pokemon;     // atualizar pokémon

    int cmd;
    // lê comandos continuamente até receber 0
    while (scanf("%d", &cmd) == 1) {
        if (cmd == 0) break;           // encerra o programa
        if (cmd >= 1 && cmd <= 5) {
            ops[cmd]();                // despacha para a função correspondente
        }
    }
    // libera toda a memória antes de sair
    free_all();
    return 0;
}