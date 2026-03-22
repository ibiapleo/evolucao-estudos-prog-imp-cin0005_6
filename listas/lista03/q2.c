#include <stdio.h>
#include <string.h>
#define TAM 6
int main()
{
    int n, x, y, totalLatasCompradas = 0, minutosTotais = 0, hora = 0, minuto = 0, latasCliente = 0;
    scanf("%d %d %d", &n, &x, &y);
    char horarios[TAM * y];
    int latas[y];

    // Armazena os horários e as latas compradas pelos clientes y (que compraram mais de uma lata)
    for (int j = 0; j < y; j++) {
        scanf("%s %d", &horarios[j * 6], &latas[j]);
    }

    for (int i = 1; i <= n; i++) {
        // Começa contagem dos horários de atendimento por cliente
        minutosTotais = i * 3;
        hora = 7 + (minutosTotais / 60);
        minuto = minutosTotais % 60;
        char horarioCliente[TAM];
        sprintf(horarioCliente, "%02d:%02d", hora, minuto);

        int ehClienteY = 0;
        // Verificando se o horário calculado está entre os horários dos clientes y
        for (int j = 0; j < y; j++) {
            if (strcmp(horarioCliente, &horarios[j * 6]) == 0) { // Se o horário calculado for o horário que o cliente y foi atendido, soma a quantidade de latas que ele comprou ao total
                totalLatasCompradas += latas[j];
                ehClienteY = 1;
                if (totalLatasCompradas >= 50) {
                    int numeroCliente = i;
                    printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %s. Que comprou %d latas.\n", numeroCliente, horarioCliente, latas[j]);
                    return 0; // Encerra o programa após encontrar o cliente que levou a cesta básica
                }
                break;
            }
        }

        // Verificando se o cliente é um cliente x
        if (x == 0) {
            // Nenhum cliente comprou nenhuma lata, então não faz nada e segue o loop
            continue;
        } else if (i % x == 0 && !ehClienteY) {
            totalLatasCompradas += 1; // Cliente x compra 1 lata
        }

        if (totalLatasCompradas >= 50) {
            int numeroCliente = i;
            printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %s. Que comprou %d lata.\n", numeroCliente, horarioCliente, 1);
            return 0; 
        }
    }

    printf("Ainda nao foram vendidas latas suficientes. Faltam %d latas.\n", 50 - totalLatasCompradas);
    return 0;
}
