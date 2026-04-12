#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_LENGTH 300


char *merge_strings(char **strings, int n) {
    // descobre o maior tamanho entre as strings
    int maxLen = 0;
    for (int i = 0; i < n; i++) {
        int len = strlen(strings[i]);
        if (len > maxLen) maxLen = len;
    }

    // aloca o espaço de todas as strings na string mesclada
    int totalLen = 0;
    for (int i = 0; i < n; i++) {
        totalLen += strlen(strings[i]);
    }

    char *merged = (char *) malloc((totalLen + 1) * sizeof(char)); // +1 para o terminador nulo

    // mescla as strings
    int pos = 0;
    for (int i = 0; i < maxLen; i++) { // o laço externo percorre cada posição possível de 0 a té maxLen - 1.
        for (int j = 0; j < n; j++) { // o laço interno percorre cada string dentro do array de strings.
            if (i < strlen(strings[j])) { // verifica se a string j possui um caractere na posicao
                merged[pos++] = strings[j][i]; // coloca o caractere na proxima posição livre da string merged
            }
        }
    }
    merged[pos] = '\0'; // adiciona o terminador nulo no final da string mesclada
    return merged;
}

char *fuse_strings(char *mergedStrings) {  
    int len = strlen(mergedStrings);
    char *result = (char *) malloc((len + 1) * sizeof(char));
    strcpy(result, mergedStrings);

    int houve_fusao;
    do {
        houve_fusao = 0;
        int i = 0;
        while (result[i] != '\0') {
            if (result[i] == result[i + 1] && result[i] != '\0') {
                // faz a fusão
                if (result[i] == 'z') {
                    result[i] = 'a';
                } else {
                    result[i] = result[i] + 1;
                }
                // remove o caractere fundido (desloca tudo para a esquerda)
                int j = i + 1;
                while (result[j] != '\0') {
                    result[j] = result[j + 1];
                    j++;
                }
                i++;
                houve_fusao = 1;
            } else {
                i++;
            }
        }
    } while (houve_fusao);

    return result;
}

int main()
{
    int numberOfStrings;
    scanf("%d", &numberOfStrings);
    char **strings = (char **) malloc(numberOfStrings * sizeof(char *)); // um array de ponteiros, alocando espaço numberOfStrings ponteiros dentro do array
    for (int i = 0; i < numberOfStrings; i++) {
        strings[i] = (char *) malloc(MAX_STRING_LENGTH * sizeof(char)); // alocando espaço para 100 caracteres para cada string
        scanf("%299s", strings[i]); // lendo a string, limitando a leitura a 99 caracteres para evitar overflow (o último caractere é reservado para o terminador nulo '\0')
    }
    char *merged = merge_strings(strings, numberOfStrings);
    char *fused = fuse_strings(merged);
    printf("%s\n", merged);
    printf("%s\n", fused);

    // libera a memória
    for (int i = 0; i < numberOfStrings; i++) {
        free(strings[i]); // libera cada string individualmente
    }
    free(strings); // libera o array de ponteiros
    free(merged); // libera a string mesclada
    free(fused); // libera a string fundida

    return 0;
}
