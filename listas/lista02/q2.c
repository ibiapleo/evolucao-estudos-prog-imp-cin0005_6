#include <stdio.h>

int main()
{
    int n_inicial, k, p;
    scanf("%d %d %d", &n_inicial, &k, &p);

    int primeiro = -1;
    int q = 0;

    int start = n_inicial;
    
    for (int i = start; i < k; i += 2) {
        int n = i;
        int contador = 0;
        int invalido = 0;

        for (int j = 3; j * j <= n; j += 2) {
            if (n % j == 0) {
                contador++;
                int vezes = 0;
                while (n % j == 0) {
                    n /= j;
                    vezes++;
                }
                if (vezes > 1) {
                    invalido = 1;
                    break;
                }
            }
        }
        if (invalido) continue;
        if (n > 2) contador++;

        if (contador == p) {
            if (primeiro == -1) {
                primeiro = i;
            } else {
                q++;
            }
        }
    }

    if (primeiro == -1) {
        printf("Poxa dudinha, me desculpa, nao achei os numeros mas vou te mandar uma foto de um gatinho fofo.\n");
    } else {
        printf("%d %d\n", primeiro, q);
    }
    return 0;
}
