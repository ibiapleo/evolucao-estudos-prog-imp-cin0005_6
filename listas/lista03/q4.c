#include <stdio.h>
#define TAM 61
int main()
{
    int r, tamanhoLuzGigante = 0;
    scanf("%d", &r); // Lê o número da quantidade de casos de teste
    
    char leds[TAM];
    char luzGigante[TAM];

    for (int i = 0; i < r; i++) { 
        int nClock;
        scanf("%s %d", leds, &nClock); // Lê a configuração inicial dos LEDs e o numero de clocks
        for (int j = 0; j < nClock; j++) {
            // Em todo clock o primeiro sempre muda o estado.
            // Se um LED desliga, o próximo troca de estado.
            int i = 0, desligou = 0;
            while (leds[i] != '\0') {
                if (i == 0) {
                    leds[i] = (leds[i] == 'O') ? 'X' : 'O'; // Inverte o estado do LED atual
                    desligou = (leds[i] == 'X') ? 1 : 0; // Verifica se o primeiro LED desligou
                }
                else if (leds[i - 1] == 'X' && desligou) {
                    leds[i] = (leds[i] == 'O') ? 'X' : 'O'; // Inverte o estado do LED atual se o anterior tiver desligado
                    desligou = (leds[i] == 'X') ? 1 : 0; // Atualiza o estado de desligado para o próximo LED
                }
                i++;
            }    
        }
        printf("%s\n", leds);
        // Insere os leds na luz gigante para o próximo teste, já que a luz gigante é a configuração final dos leds depois de nClock clocks.
        for (int k = 0; leds[k] != '\0'; k++) {
            luzGigante[tamanhoLuzGigante] = leds[k];
            tamanhoLuzGigante++; // Guarda o tamanho da luz gigante
        }
        if (i != r-1) luzGigante[tamanhoLuzGigante++] = 'A'; // Finaliza deixando espaço para as junções da luz gigante
    }

    int j = 0;
    // Com a luz gigante já formada, com o A no lugar das junções, percorre a luz gigante e substitui os A's de acordo com as regras de junções.
    while (luzGigante[j] != '\0') {
        if (luzGigante[j] == 'A') {
            if (j % 2 == 0) {
                if (luzGigante[tamanhoLuzGigante - 1] == luzGigante[j + 1]) {
                    luzGigante[j] = '@';
                } else {
                    luzGigante[j] = '$';
                }
            } else {
                if (luzGigante[tamanhoLuzGigante - 1] == luzGigante[j + 1]) {
                    luzGigante[j] = '#';
                } else {
                    luzGigante[j] = '%';
                }
            }
        }
        j++;
    }
    printf("%s\n", luzGigante);

    return 0;
}
