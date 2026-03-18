#include <stdio.h>

int main()
{
    int n_inicial, k, p;
    scanf("%d %d %d", &n_inicial, &k, &p);

    int primeiro = -1;
    int q = 0;

    int start = n_inicial;
    
    for (int i = start; i < k; i++) {
        int n = i;
        int contador = 0;
        int invalido = 0;

        if (n == 0) {
            invalido = 1;
        } else {
            while (n % 2 == 0) {
                n /= 2;
            }

            for (int j = 3; (long long)j * j <= n; j += 2) {
                if (n % j == 0) {
                    int vezes = 0;
                    while (n % j == 0) {
                        n /= j;
                        vezes++;
                    }

                    if (vezes > 1) {
                        invalido = 1;
                        break;
                    }

                    contador++;
                }
            }

            if (!invalido && n > 1) {
                contador++;
            }
        }

        if (!invalido && contador == p) {
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
