#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_COLLECTION_SIZE 100
#define MAX_NAME_LENGTH 31

typedef struct {
    char name[MAX_NAME_LENGTH];
    char genre[MAX_NAME_LENGTH];
    char studio[MAX_NAME_LENGTH];
    char platform[MAX_NAME_LENGTH];
    int score;
    int yearOfRelease;
} Game;

typedef struct {
    Game games[MAX_COLLECTION_SIZE];
    int size;
} Collection;

void printAno(Collection *col) {
    int year, count = 0;
    scanf("%d", &year);
    for (int i = 0; i < col->size; i++) {
        if (col->games[i].yearOfRelease == year) {
            printf("%s\n", col->games[i].name);
            count++;
        }
    }

    if (count > 0) {
        printf("Tenho %d jogos || %d.\n", count, year);
    } else {
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
    }
}

void printLetra(Collection *col) {
    char letter;
    int count = 0;
    scanf(" %c", &letter);
    for (int i = 0; i < col->size; i++) {
        if (col->games[i].name[0] == letter) {
            printf("%s\n", col->games[i].name);
            count++;
        }
    }

    if (count > 0) {
        printf("Tenho %d jogos || %c.\n", count, letter);
    } else {
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
    }
}

void printStudio(Collection *col) {
    char studio[MAX_NAME_LENGTH];
    int count = 0;
    scanf("%s", studio);
    for (int i = 0; i < col->size; i++) {
        if (strcmp(col->games[i].studio, studio) == 0) {
            printf("%s\n", col->games[i].name);
            count++;
        }
    }

    if (count > 0) {
        printf("Tenho %d jogos || %s.\n", count, studio);
    } else {
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
    }
}

void printConsole(Collection *col) {
    char console[MAX_NAME_LENGTH];
    int count = 0;
    scanf("%s", console);
    for (int i = 0; i < col->size; i++) {
        if (strcmp(col->games[i].platform, console) == 0) {
            printf("%s\n", col->games[i].name);
            count++;
        }
    }

    if (count > 0) {
        printf("Tenho %d jogos || %s.\n", count, console);
    } else {
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
    }
}

void printColecao(Collection *col) {
    for (int i = 0; i < col->size; i++) {
        printf("%s %d\n", col->games[i].name, col->games[i].score);
    }
}

void readCollection(Collection *col) {
    char line[256];

    for (int i = 0; i < col->size; i++) {
        if (!fgets(line, sizeof(line), stdin)) return;
        line[strcspn(line, "\n")] = '\0';

        int consumed = 0;
        sscanf(line, "%30s %30s %30s%n",
               col->games[i].name,
               col->games[i].genre,
               col->games[i].studio,
               &consumed);
        
        // pula o espaço após o terceiro campo
        // rest agora aponta para o que sobrou: "nintendo 64 10 1998"
        char rest[256];
        strncpy(rest, line + consumed + 1, sizeof(rest));
        
        // strrchr busca da direita pra esquerda o último espaço
        // sep fica apontando para o espaço antes do último token
        //
        // ex: "nintendo 64 10 1998"
        //                    ^ sep
        //
        // sep + 1 aponta para "1998", que atoi converte para int
        // *sep = '\0' corta a string ali, descartando o year
        char *sep = strrchr(rest, ' ');
        col->games[i].yearOfRelease = atoi(sep + 1);
        *sep = '\0';
        
        // repete o mesmo processo, agora rest é "nintendo 64 10"
        //
        //  ex:  "nintendo 64 10"
        //                   ^ sep
        //
        // sep + 1 aponta para "10", *sep = '\0' descarta o score
        sep = strrchr(rest, ' ');
        col->games[i].score = atoi(sep + 1);
        *sep = '\0';
        
        // o que sobrou em rest é somente o platform
        // pode ter uma ou duas palavras: "switch" ou "nintendo 64"
        strncpy(col->games[i].platform, rest, MAX_NAME_LENGTH - 1);

        if (col->games[i].score > 7) {
            printf("AWESOME! Mais um GOTY pra minha coleção!\n");
        } else if (col->games[i].score < 4) {
            printf("Era melhor jogar mais um jogo de Mahjong.\n");
        }
    }
}

int main()
{   
    Collection col;
    scanf("%d", &col.size);
    getchar();
    readCollection(&col);
    
    char command[MAX_NAME_LENGTH];
    while (scanf("%s", command) != EOF) {
        if (strcmp(command, "printAno") == 0) {
            printAno(&col);
        } else if (strcmp(command, "printLetra") == 0) {
            printLetra(&col);
        } else if (strcmp(command, "printStudio") == 0) {
            printStudio(&col);
        } else if (strcmp(command, "printConsole") == 0) {
            printConsole(&col);
        } else if (strcmp(command, "printColecao") == 0) {
            printColecao(&col);
        }
    }
    
    printf("Enjoei de jogar, agora vou ver TV.\n");
    return 0;
}
