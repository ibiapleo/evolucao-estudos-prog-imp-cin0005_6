#include <stdio.h>
#include <stdlib.h>

void push_value (long **values, int *size, long newValue) { // adiciona dinamicamente valores ao array de valores, aumentando seu tamanho conforme necessário
    long *resized_values = (long *) realloc(*values, (*size + 1) * sizeof(long));
    *values = resized_values;
    (*values)[*size] = newValue;
    (*size)++;
}

void print_odds (long *values, int size) { 
    for (int i = 0; i < size; i++) {
        if (values[i] % 2 != 0) {
            printf("%d\n", values[i]);
        }
    }
}

void print_evens (long *values, int size) { 
    for (int i = 0; i < size; i++) {
        if (values[i] % 2 == 0) {
            printf("%d\n", values[i]);
        }
    }
}

void print_cornifer_statement (long *values, int size) {
    printf("Mais um bom dia de trabalho!\n");
    print_odds(values, size);
    print_evens(values, size);
    printf("Vou visitar esses lugares de novo... algum dia.\n");
}

int main()
{
    long value; // variável temporária para armazenar os valores lidos da entrada padrão
    int size = 0; // contador para o número de valores lidos
    long *values = (long *) malloc(size * sizeof(long)); // aloca um array dinâmico para armazenar os valores, inicialmente com tamanho 0
    while (scanf("%d", &value) == 1) {
        push_value(&values, &size, value); // chama a função push_value para adicionar o valor lido ao array de valores, aumentando seu tamanho conforme necessário
    }
    print_cornifer_statement(values, size); // chama a função print_cornifer_statement para imprimir a mensagem de início, os valores ímpares, os valores pares e a mensagem de encerramento
    free(values);
    return 0;
}
