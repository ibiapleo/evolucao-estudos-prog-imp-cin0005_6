#include <stdio.h>

int main()
{
    int n_inicial, k, p;
    scanf("%d %d %d", &n_inicial, &k, &p);

    int primeiro = -1;
    int q = 0;
    int i;

    int start = n_inicial;
    if (start < 3) start = 3;
    if (start % 2 == 0) start++;

    if (n_inicial <= 2 && 2 < k) {
        int count2 = 0;
        if (p == 0) {
            primeiro = 2;
        }
    }

    for (i = start; i < k; i += 2) {
        int n = i;
        int count = 0;
        int invalido = 0;


        int j;
        for (j = 3; j * j <= n; j += 2) {
            if (n % j == 0) {
                count++;
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
        if (n > 2) count++;

        if (count == p) {
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
