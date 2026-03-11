#include <stdio.h>



int main()
{
    int total, x, y, z;
    scanf("%d\n%d\n%d\n%d", &total, &x, &y, &z);

    int a, b, c, sobra;
    int dinheiroRebeka = 3;
    int investimento = 0;
    int sucesso = 0;

    a = (total * x) / 100;
    b = (total * y) / 100;
    c = (total * z) / 100;
    sobra = total - (a + b + c);

    if ((total * x) % 100 == 0 && (total * y) % 100 == 0 && (total * z) % 100 == 0 && sobra >= investimento) {
        dinheiroRebeka += sobra;
        sucesso = 1;
    } else {
        total += 1;
        investimento += 1;
        dinheiroRebeka -=1;
        a = (total * x) / 100;
        b = (total * y) / 100;
        c = (total * z) / 100;
        sobra = total - (a + b + c);

        if ((total * x) % 100 == 0 && (total * y) % 100 == 0 && (total * z) % 100 == 0 && sobra > investimento) {
            dinheiroRebeka += sobra;
            sucesso = 1;
        } else {
            total += 1;
            investimento += 1;
            dinheiroRebeka -=1;
            a = (total * x) / 100;
            b = (total * y) / 100;
            c = (total * z) / 100;
            sobra = total - (a + b + c);
            if ((total * x) % 100 == 0 && (total * y) % 100 == 0 && (total * z) % 100 == 0  && sobra > investimento) {
                dinheiroRebeka += sobra;
                sucesso = 1;
            } else {
                total += 1;
                investimento += 1;
                dinheiroRebeka -=1;
                a = (total * x) / 100;
                b = (total * y) / 100;
                c = (total * z) / 100;
                sobra = total - (a + b + c);
                if ((total * x) % 100 == 0 && (total * y) % 100 == 0 && (total * z) % 100 == 0) {
                    dinheiroRebeka += sobra;
                    sucesso = 1;
                }
            }
        }
    }

    if (sucesso) {
        printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", a, b, c);
    } else {
        printf("Nao foi dessa vez que Rebeka pode ajudar...\n");
    }

    if (investimento == 2) {
        char c1, c2, c3;
        scanf(" %c %c %c", &c1, &c2, &c3);
        int soma = (c1 - 'a' + 1) + (c2 - 'a' + 1) + (c3 - 'a' + 1);
        printf("%d\n", soma);
    } else if (investimento == 3) {
        int i1, i2, i3;
        scanf("%d %d %d", &i1, &i2, &i3);
        if (i1 % 3 == 0 || i2 % 3 == 0 || i3 % 3 == 0) {
            int soma = 0;
            if (i1 % 3 == 0) {
                soma += i1;
            }
            if (i2 % 3 == 0) {
                soma += i2;
            }
            if (i3 % 3 == 0) {
                soma += i3;
            }
            printf("%d\n", soma/3);
        }
    }

    if (dinheiroRebeka >= 7) {
        printf("Ela conseguiu! Rebeka voltou para casa e apanhou da mae por sumir noite passada!\n");
    } else {
        printf("E parece que Rebeka vai ter que voltar andando...\n");
    }
            
    return 0;
}
