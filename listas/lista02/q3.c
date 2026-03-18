#include <stdio.h>

int main()
{
    int x, n, i1, i2, f;
    scanf("%d %d", &x, &n);
    
    int proximidade = -1, minuto, minutoMaisProximo = 0, fValorMaisProximo = 0, canal = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &i1, &i2);
        f = 0;
        minuto = 2;

        int compf1 = (x > i1) ? (x - i1) : (i1 - x);
        int compf2 = (x > i2) ? (x - i2) : (i2 - x);

        if (compf1 <= compf2) {
            if (proximidade == -1 || compf1 < proximidade) {
                proximidade = compf1;
                fValorMaisProximo = i1;
                canal = i + 1;
                minutoMaisProximo = 1;
            }
        } else {
            if (proximidade == -1 || compf2 < proximidade) {
                proximidade = compf2;
                fValorMaisProximo = i2;
                canal = i + 1;
                minutoMaisProximo = 2;
            }
        }

        // f(i) = f(i-1) + f(i-2)
        while(f <= x) {
            f = i1 + i2;    
            i1 = i2;
            i2 = f;
            minuto += 1;
            int comp = (x > f) ? (x - f) : (f - x);
            if (comp < proximidade) {
                proximidade = comp;
                fValorMaisProximo = f;
                canal = i + 1;
                minutoMaisProximo = minuto;
            }
        }
    }

    int somaAlgarismos = 0;
    int valorTemp = fValorMaisProximo;
    while (valorTemp > 0) {
        somaAlgarismos += valorTemp % 10;
        valorTemp /= 10;
    }
    int vip = 0;
    if (somaAlgarismos > 10) {
        vip = 1;
    }

    if (vip) {
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d e com o VIP garantido!!!\n", canal, minutoMaisProximo);
    } else {
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d, mas o ingresso VIP não vai rolar :(\n", canal, minutoMaisProximo);
    }


    return 0;
}
