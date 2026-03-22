#include <stdio.h>

int main()
{
    int t, n;
    scanf("%d", &t); // Lê o número da quantidade de casos de teste

    for (int i = 0; i < t; i++) {
        scanf("%d", &n); // Lê o tamanho da sequência
        int sequencia[n];

        // Lê os números da sequência para o teste
        for (int j = 0; j < n; j++) {
            scanf("%d", &sequencia[j]);
        }

        // Inicializa/Reinicia variáveis entre os testes para rastrear a maior sequência decrescente
        int melhor_inicio = 0; // Início da melhor sequência encontrada
        int melhor_tam = 1;    // Tamanho da melhor sequência encontrada
        int atual_inicio = 0;  // Início da sequência atual
        int atual_tam = 1;     // Tamanho da sequência atual

        // Percorre o vetor para encontrar a maior sequência decrescente contínua
        for (int j = 1; j < n; j++) {
            if (sequencia[j] < sequencia[j - 1]) {
                atual_tam++;
            } else {
                // Sequência foi quebrada, verifica se era a maior até agora
                if (atual_tam > melhor_tam) {
                    melhor_tam = atual_tam;
                    melhor_inicio = atual_inicio;
                }
                // Reinicia a sequência atual a partir do elemento atual
                atual_inicio = j;
                atual_tam = 1;
            }
        }
        // Verifica se a última sequência é a maior porque sai fora do laço
        if (atual_tam > melhor_tam) {
            melhor_tam = atual_tam;
            melhor_inicio = atual_inicio;
        }

        // Se não existe sequência decrescente (tamanho 1), imprime 0
        if (melhor_tam < 2) {
            printf("0\n");
        } else {
            // Imprime o tamanho da maior sequência
            printf("%d\n", melhor_tam);
            // Imprime os elementos da maior sequência decrescente
            for (int j = melhor_inicio; j < melhor_inicio + melhor_tam; j++) {
                printf("%d ", sequencia[j]);
            }
            printf("\n");
        }
    }
    return 0;
}