#include <stdio.h>

int main()
{
    int x, y, qd_evitado, qd_atual;

    scanf("%d %d %d", &x, &y, &qd_evitado);

    if (x>0 && y>0) {
        qd_atual = 1;
    } else if (x<0 && y>0) {
        qd_atual = 2;
    } else if (x<0 && y<0) {
        qd_atual = 3;
    } else if (x>0 && y<0) {
        qd_atual = 4;
    }
    
    int andar_y, andar_x;

    if (qd_atual == qd_evitado) {
        printf("caminhada invalida\n");
    } else if (qd_atual == 1) {
        andar_y = -(y + 1);
        andar_x = -(x + 1);
        switch(qd_evitado) {
            case 2:
                printf("%d passos em y e %d passos em x\n",- andar_y, -andar_x);
                break;
            case 4:
                printf("%d passos em x e %d passos em y\n", -andar_x, -andar_y);
                break;
        }
    } else if (qd_atual == 2) {
        andar_y = -(y + 1);
        andar_x = -(x) + 1;
        switch (qd_evitado) {
        case 1:
            printf("%d passos em y e %d passos em x\n", -andar_y, andar_x);
            break;
        case 3:
            printf("%d passos em x e %d passos em y\n", andar_x, -andar_y);
            break;
        }
    } else if (qd_atual == 3) {
        andar_y = -(y) + 1;
        andar_x = -(x) + 1;
        switch (qd_evitado) {
        case 2:
            printf("%d passos em x e %d passos em y\n", andar_x, andar_y);
            break;
        case 4:
            printf("%d passos em y e %d passos em x\n", andar_y, andar_x);
            break;
        }
    } else if (qd_atual == 4) {
        andar_y = -(y) + 1;
        andar_x = -(x + 1);
        switch (qd_evitado)
        {
        case 1:
            printf("%d passos em x e %d passos em y\n", -andar_x, andar_y);
            break;
        case 3:
            printf("%d passos em y e %d passos em x\n", andar_y, -andar_x);
            break;
        } 
    }
    return 0;
}
