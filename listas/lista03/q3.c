#include <stdio.h>
#define TAM 101

int main() {
    char string[TAM] = "";
    fgets(string, TAM, stdin); // lê a frase com fgets para permitir espaços

    int i = 0, totalAnagramas = 0, primeiro = 1;
    // Percorre a frase inteira
    while (string[i] != '\0') {
        // Pega a primeira palavra da frase (original e para comparação)
        char palavra1[TAM], palavra1_cmp[TAM];
        int idx1 = 0, idx1_cmp = 0;
        while (string[i] == ' ') i++; // Pula espaços
        while (string[i] != ' ' && string[i] != '\n' && string[i] != '\0') {
            palavra1[idx1++] = string[i]; // Guarda a palavra original (com pontuação)
            // Só considera letras para comparação
            if ((string[i] >= 'A' && string[i] <= 'Z') || (string[i] >= 'a' && string[i] <= 'z')) {
                // Conversão para minúsculo para comparação
                if (string[i] >= 'A' && string[i] <= 'Z')
                    palavra1_cmp[idx1_cmp++] = string[i] + ('a' - 'A');
                else
                    palavra1_cmp[idx1_cmp++] = string[i];
            }
            i++;
        }
        palavra1[idx1] = '\0';
        palavra1_cmp[idx1_cmp] = '\0';
        if (idx1 == 0) break; // Não tem mais palavras na frase

        int j = i;
        // Para cada palavra seguinte, compara com a palavra na posição de palavra1
        while (string[j] != '\0') {
            // Pega a próxima palavra (original e para comparação)
            char palavra2[TAM], palavra2_cmp[TAM];
            int idx2 = 0, idx2_cmp = 0, k = j;
            while (string[k] == ' ') k++; // Pula espaços
            while (string[k] != ' ' && string[k] != '\n' && string[k] != '\0') {
                palavra2[idx2++] = string[k]; // Guarda a palavra original (com pontuação)
                // Só considera letras para comparação
                if ((string[k] >= 'A' && string[k] <= 'Z') || (string[k] >= 'a' && string[k] <= 'z')) {
                    if (string[k] >= 'A' && string[k] <= 'Z')
                        palavra2_cmp[idx2_cmp++] = string[k] + ('a' - 'A');
                    else
                        palavra2_cmp[idx2_cmp++] = string[k];
                }
                k++;
            }
            palavra2[idx2] = '\0';
            palavra2_cmp[idx2_cmp] = '\0';
            if (idx2 == 0) break; // Não tem mais palavras na frase

            // Verifica se são anagramas (comparando as versões minúsculas e só letras)
            int tam1 = idx1_cmp, tam2 = idx2_cmp;
            if (tam1 == tam2) { // se tiverem o mesmo tamanho, são candidatas a serem anagramas
                char usado[TAM] = {0}; // para marcar quais letras da palavra2 já foram usadas uma vez na palavra1
                int ehAnagrama = 1;
                for (int a = 0; a < tam1; a++) { 
                    int achou = 0;
                    for (int b = 0; b < tam2; b++) {
                        if (!usado[b] && palavra1_cmp[a] == palavra2_cmp[b]) {
                            usado[b] = 1;
                            achou = 1;
                            break;
                        }
                    }
                    if (!achou) {
                        ehAnagrama = 0;
                        break;
                    }
                }
                if (ehAnagrama) {
                    totalAnagramas++;
                    if (primeiro) {
                        printf("Pares de anagramas encontrados:\n");
                        primeiro = 0;
                    }
                    // Exibe as palavras como foram digitadas originalmente
                    printf("%s e %s\n", palavra1, palavra2);
                }
            }
            j = k; // Avança pra próxima palavra como palavra2
        }
        i++; // Avança para a próxima palavra como palavra1
    }

    if (totalAnagramas == 0) {
        printf("Nao existem anagramas na frase.\n");
    } else {
        printf("\nTotal de pares: %d\n", totalAnagramas);
    }
    return 0;
}