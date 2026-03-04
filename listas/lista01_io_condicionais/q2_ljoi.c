#include <stdio.h>

int main()
{
    int N, A, B;
    scanf("%d", &N);
    scanf("%d %d", &A, &B);

    int somaAteN = (N * (N + 1))/2;
    int kb = N/B;
    int somaMultiplosDeB = B * (kb * (kb + 1))/2;
    int ka = N/A;
    int somaMultiplosDeA = A * (ka * (ka + 1))/2;
    int kAB = N/(A*B);
    int somaMultiplosDeAB = (A*B) * (kAB * (kAB + 1))/2;

    int somaFinal = somaAteN - somaMultiplosDeA - somaMultiplosDeB + somaMultiplosDeAB;
    printf("%d\n", somaFinal);
    if(somaFinal % 2 == 0) {
        printf("Lá ele!!!\n");
    } else {
        printf("Opa xupenio AULAS...\n");
    }
    return 0;
}
