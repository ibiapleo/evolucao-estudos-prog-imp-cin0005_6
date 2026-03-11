#include <stdio.h>

int main()
{
    long N, A, B;
    scanf("%ld", &N);
    scanf("%ld %ld", &A, &B);

    long somaAteN = (N * (N + 1))/2;
    long kb = N/B;
    long somaMultiplosDeB = B * (kb * (kb + 1))/2;
    long ka = N/A;
    long somaMultiplosDeA = A * (ka * (ka + 1))/2;
    long kAB = N/(A*B);
    long somaMultiplosDeAB = (A*B) * (kAB * (kAB + 1))/2;

    long somaFinal = somaAteN - somaMultiplosDeA - somaMultiplosDeB + somaMultiplosDeAB;
    printf("%ld\n", somaFinal);
    if(somaFinal % 2 == 0) {
        printf("Lá ele!!!\n");
    } else {
        printf("Opa xupenio AULAS...\n");
    }
    return 0;
}
