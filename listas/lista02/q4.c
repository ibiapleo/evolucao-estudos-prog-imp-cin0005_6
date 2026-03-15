#include <stdio.h>

int main()
{
    int q, x, n_coluna = 1, primeiro = 1;
    char c, ultimo = 0;

    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        scanf("%d %c", &x, &c);

        if (c == ultimo) {
            printf("Informacao invalida\n");
            return 0;
        }

        switch (c)
        {
        case 'D':
            if (primeiro) {
                for (int j = 0; j < x; j++) printf(".");
                n_coluna = x;
            } else {
                int espaco = n_coluna - 1;
                for (int j = 0; j < espaco; j++) printf(" ");
                for (int j = 0; j < x + 1; j++) printf(".");
                n_coluna += x;
            }
            break;
        case 'E':
            if (primeiro || n_coluna - x < 1) {
                printf("Informacao invalida\n");
                return 0;
            }
            int espaco = (n_coluna - x) - 1;
            for (int j = 0; j < espaco; j++) printf(" ");
            for (int j = 0; j < x + 1; j++) printf(".");
            n_coluna -= x;
            break;
        case 'B':
            if (primeiro) {
                for (int j = 0; j < x - 1; j++) {
                    printf(".\n");
                }
                n_coluna = 1;
            } else {
                printf("\n");
                int espaco_b = n_coluna - 1;
                for (int j = 0; j < x - 1; j++) {
                    for (int k = 0; k < espaco_b; k++) printf(" ");
                    printf(".\n");
                }
            }
            break;
        default:
            printf("Informacao invalida\n");
            return 0;
            break;
        }

        primeiro = 0;
        ultimo = c;
    }

    if (ultimo == 'B') {
        int espaco = n_coluna - 1;
        for (int k = 0; k < espaco; k++) printf(" ");
        printf(".\n");
    } else if (ultimo != 0) {
        printf("\n");
    }

    return 0;
}

