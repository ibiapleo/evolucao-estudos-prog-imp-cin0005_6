#include <stdio.h>
#define TAM 61
#define MAX_R 1000
#define MAX_GIGANTE 61000
int main()
{
    int r;
    scanf("%d", &r); // Lê o número da quantidade de casos de teste

    char leds[TAM];
    char luzGigante[MAX_GIGANTE];
    int inicioFio[MAX_R];
    int tamanhoLuzGigante = 0;

    // Processa cada caso de teste individualmente
    for (int i = 0; i < r; i++) {
        int nClock;
        scanf("%s %d", leds, &nClock); // Lê a configuração inicial dos LEDs e o numero de clocks
        // Aplica os clocks ao fio de LEDs
        for (int j = 0; j < nClock; j++) {
            int idx = 0, desligou = 0;
            // Em todo clock o primeiro sempre muda o estado.
            // Se um LED desliga, o próximo troca de estado.
            while (leds[idx] != '\0') {
                if (idx == 0) {
                    leds[idx] = (leds[idx] == 'O') ? 'X' : 'O'; // Inverte o estado do LED atual
                    desligou = (leds[idx] == 'X') ? 1 : 0; // Verifica se o primeiro LED desligou
                } else if (leds[idx - 1] == 'X' && desligou) {
                    leds[idx] = (leds[idx] == 'O') ? 'X' : 'O'; // Inverte o estado do LED atual se o anterior tiver desligado
                    desligou = (leds[idx] == 'X') ? 1 : 0; // Atualiza o estado de desligado para o próximo LED
                }
                idx++;
            }
        }
        printf("%s\n", leds); // Exibe a configuração final do fio após os clocks
        inicioFio[i] = tamanhoLuzGigante; // Marca o início deste fio na luz gigante
        // Copia o fio processado para a luz gigante
        for (int k = 0; leds[k] != '\0'; k++) {
            luzGigante[tamanhoLuzGigante++] = leds[k];
        }
    }

    // Monta a luz gigante final com ornamentos entre os fios
    char luzFinal[MAX_GIGANTE];
    int pos = 0;
    for (int i = 0; i < r; i++) {
    int ini = inicioFio[i];
    // Calcula o índice final do fio atual na luz gigante:
    // Se for o último fio, o fim é o tamanho total da luz gigante;
    // Caso contrário, o fim é o índice de início do próximo fio.
    int fim = (i == r-1) ? tamanhoLuzGigante : inicioFio[i+1];
        // Copia o fio para luzFinal
        for (int j = ini; j < fim; j++) {
            luzFinal[pos++] = luzGigante[j];
        }
        // Se não for o último fio, insere ornamento conforme as regras
        if (i < r-1) {
            char ultimo = luzGigante[fim-1]; // Último led do fio atual
            char proximo = luzGigante[inicioFio[i+1]]; // Primeiro led do próximo fio
            int tamAtual = pos; // Tamanho atual da luz gigante
            // Insere o ornamento correto de acordo com o tamanho e estados
            if (tamAtual % 2 == 0) {
                luzFinal[pos++] = (ultimo == proximo) ? '@' : '$';
            } else {
                luzFinal[pos++] = (ultimo == proximo) ? '#' : '%';
            }
        }
    }
    luzFinal[pos] = '\0'; // Finaliza a string da luz gigante
    printf("%s\n", luzFinal); // Exibe a luz gigante final

    return 0;
}
