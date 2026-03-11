#include <stdio.h>

int main()
{
    char letra;
    scanf(" %c", &letra);
    int asci = letra - 'A' + 1;

    for (int i = 1; i <= asci; i++) {
        int padding = asci - i;
        for (int j = 0; j < padding; j++) {
            printf(".");
        }
        for (int k = 0; k < i; k++) {
            printf("%c", 'A' + k);
        }
        for (int k = i - 2; k >= 0; k--) {
            printf("%c", 'A' + k);
        }
        for (int j = 0; j < padding; j++) {
            printf(".");
        }
        printf("\n");
    }
    return 0;
}
