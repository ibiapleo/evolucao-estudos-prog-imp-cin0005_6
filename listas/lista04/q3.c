#include <stdio.h>
#define SIZE 41 // tamanho necessário pra 20 caracteres + 20 espaços + terminador nulo

void pedroWalkthrough(char in[], int size, int city[4][4]) {
    int x = 0, y = 0; // posição inicial de Pedro
    for (int i = 0; i < size - 1; i++) { // itera sobre o vetor com as entradas dos movimentos de Pedro, desconsiderando o terminador nulo
        if (in[i] == 'c') {
            if (y == 0) { // se Pedro tentar subir além do limite da cidade, ele simplesmente ignora o comando e continua para o próximo movimento
                continue;
            }  
            y--; // atualiza a posição de Pedro para cima
            city[y][x] += 1; 
        } else if (in[i] == 'b') {
            if (y == 3) { // se Pedro tentar descer além do limite da cidade, ele simplesmente ignora o comando e continua para o próximo movimento
                continue;
            }
            y++; // atualiza a posição de Pedro para baixo
            city[y][x] += 1;
        } else if (in[i] == 'e') {
            if (x == 0) { // se Pedro tentar ir para a esquerda além do limite da cidade, ele simplesmente ignora o comando e continua para o próximo movimento
                continue;
            }
            x--; // atualiza a posição de Pedro para a esquerda
            city[y][x] += 1;
        } else if (in[i] == 'd') {
            if (x == 3) { // se Pedro tentar ir para a direita além do limite da cidade, ele simplesmente ignora o comando e continua para o próximo movimento
                continue;
            }
            x++; // atualiza a posição de Pedro para a direita
            city[y][x] += 1;
        }
    }

    int greater = 0; // variável para armazenar o greater número de visitas a um local
    int greater_x = 0, greater_y = 0; // variáveis para armazenar as coordenadas do local mais visitado
    for (int i = 0; i < 4; i++) { 
        for (int j = 0; j < 4; j++) {
            if (city[i][j] > greater) { // verifica se o número de visitas ao local atual é greater do que o greater registrado até agora
                greater = city[i][j]; // atualiza o greater número de visitas
                greater_x = j; // atualiza a coordenada x do local mais visitado
                greater_y = i; // atualiza a coordenada y do local mais visitado
            }
        }
    }
    printf("Coordenada X:%d, Y:%d\n", greater_x, greater_y); // imprime as coordenadas do local mais visitado por Pedro
}   

int main()
{
    char input[SIZE]; // vetor que armazena a sequência de movimentos de Pedro
    int city[4][4] = {0}; // matriz para contar as visitas de Pedro
    fgets(input, SIZE, stdin); // lê a sequência de movimentos de Pedro com fgets para desconsiderar os espaços
    pedroWalkthrough(input, SIZE, city);
    return 0;
}
