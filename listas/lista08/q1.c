#include <stdio.h>

typedef union {
    unsigned char raw;
    struct {
        /* Mapeamento dos bits do byte de status (1 + 3 + 4 = 8 bits). */
        unsigned char error   : 1;
        unsigned char mode    : 3;
        unsigned char reading : 4;
    } fields; 
} Status;

int main() {
    int input;
    scanf("%d", &input);

    /* Grava o valor bruto e permite acessar os campos por bitfield. */
    Status status;
    status.raw = (unsigned char)input;

    /* Exibe o byte inteiro e, em seguida, cada parte decodificada. */
    printf("Byte bruto: %u | ", status.raw);
    printf("Erro: %u | ", status.fields.error);
    printf("Modo: %u | ", status.fields.mode);
    printf("Leitura: %u\n", status.fields.reading);
    return 0;
}