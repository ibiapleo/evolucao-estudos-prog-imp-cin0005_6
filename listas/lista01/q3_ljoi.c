#include <stdio.h>

int main()
{
    int total, px, py, pz;
    scanf("%d\n%d\n%d\n%d", &total, &px, &py, &pz);

    int a = (total * px) / 100;
    int b = (total * py) / 100;
    int c = (total * pz) / 100;
    int soma = a + b + c;
    int sobra = total - soma;

    int exato = ((total * px) % 100 == 0) && ((total * py) % 100 == 0) && ((total * pz) % 100 == 0);

    int conseguiu = 0;
    int investido = 0;

    if (exato) {
        printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", a, b, c);
    } else {
        int achou = 0;
        int novo_total = total + 1;

        int novo_a = (novo_total * px) / 100;
        int novo_b = (novo_total * py) / 100;
        int novo_c = (novo_total * pz) / 100;
        int nova_soma = novo_a + novo_b + novo_c;
        int nova_sobra = novo_total - nova_soma;

        int novo_exato = ((novo_total * px) % 100 == 0) && ((novo_total * py) % 100 == 0) && ((novo_total * pz) % 100 == 0);

        if (novo_exato && nova_sobra >= 2) {
            investido = 1;
            a = novo_a;
            b = novo_b;
            c = novo_c;
            sobra = nova_sobra;
            exato = 1;
            achou = 1;
        }
        if (!achou) {
            novo_total = total + 2;

            novo_a = (novo_total * px) / 100;
            novo_b = (novo_total * py) / 100;
            novo_c = (novo_total * pz) / 100;
            nova_soma = novo_a + novo_b + novo_c;
            nova_sobra = novo_total - nova_soma;

            novo_exato = ((novo_total * px) % 100 == 0) && ((novo_total * py) % 100 == 0) && ((novo_total * pz) % 100 == 0);

            if (novo_exato && nova_sobra >= 3) {
                investido = 2;
                a = novo_a;
                b = novo_b;
                c = novo_c;
                sobra = nova_sobra;
                exato = 1;
                achou = 1;
            }
        }
        if (!achou) {
            novo_total = total + 3;

            novo_a = (novo_total * px) / 100;
            novo_b = (novo_total * py) / 100;
            novo_c = (novo_total * pz) / 100;
            nova_soma = novo_a + novo_b + novo_c;
            nova_sobra = novo_total - nova_soma;

            novo_exato = ((novo_total * px) % 100 == 0) && ((novo_total * py) % 100 == 0) && ((novo_total * pz) % 100 == 0);

            if (novo_exato && nova_sobra >= 4) {
                investido = 3;
                a = novo_a;
                b = novo_b;
                c = novo_c;
                sobra = nova_sobra;
                exato = 1;
                achou = 1;
            }
        }
        if (exato && investido > 0) {
            printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", a, b, c);
            if (investido == 2) {
                char l1, l2, l3;
                scanf("\n%c %c %c", &l1, &l2, &l3);
                int soma_letras = (l1 - 'a' + 1) + (l2 - 'a' + 1) + (l3 - 'a' + 1);
                printf("%d\n", soma_letras);
            }
            if (investido == 3) {
                int id1, id2, id3;
                scanf("%d %d %d", &id1, &id2, &id3);
                int parcelas = 0;
                if (id1 % 3 == 0 || id2 % 3 == 0 || id3 % 3 == 0) {
                    parcelas = (id1 / 3) + (id2 / 3) + (id3 / 3);
                }
                printf("%d\n", parcelas);
            }
        } else {
            printf("Nao foi dessa vez que Rebeka pode ajudar...\n");
        }
    }

    if (sobra + investido >= 7) {
        printf("Ela conseguiu! Rebeka voltou para casa e apanhou da mae por sumir noite passada!\n");
    } else {
        printf("E parece que Rebeka vai ter que voltar andando...\n");
    }

    return 0;
}
