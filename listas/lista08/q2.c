#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

typedef union 
{
    uint32_t raw;
    struct
    {
        /* Estrutura compacta do pacote em 32 bits. */
        uint32_t sensorID      : 10;
        uint32_t statusCode    : 3;
        uint32_t lowBattery    : 1;
        int32_t temperature    : 12;
        uint32_t errorControl  : 6;
    } fields;
} Package;

void printPackage(Package *pack, int size)
{   
    /* Exibe cada pacote ja decodificado por campos. */
    for (int i = 0; i < size; i++) {
        printf("Pacote [%d] - Dado Bruto: 0x%08" PRIX32 "\n", i + 1, pack[i].raw);
        printf("ID do Sensor : %u\n", pack[i].fields.sensorID);
        printf("Status : %u\n", pack[i].fields.statusCode);
        if (pack[i].fields.lowBattery) {
            printf("Bateria Baixa : SIM (ALERTA)\n");
        } else {
            printf("Bateria Baixa : Nao\n");
        }
        printf("Temperatura : %d graus\n", pack[i].fields.temperature);
        printf("-------------------------------------------------\n");
    }
}

int main()
{
    /* Vetor dinamico para armazenar quantidade variavel de pacotes. */
    Package *packs = (Package*) malloc(sizeof(Package));
    int size = 0, capacity = 1;
    if (packs == NULL) {
        free(packs);
        return 1;
    }

    /* Le ate encontrar 0, que funciona como sentinela de parada. */
    while (scanf("%" SCNx32, &packs[size].raw) == 1) {
        if (packs[size].raw == 0) {
            break;
        }
        size++;
        if (size == capacity) {
            /* Dobra a capacidade. */
            int newCapacity = capacity * 2;
            Package *newPacks = (Package*) realloc(packs, newCapacity * sizeof(Package));
            if (newPacks == NULL) {
                free(packs);
                return 1;
            }
            packs = newPacks;
            capacity = newCapacity;
        }
    }
    
    printPackage(packs, size);
    free(packs);     
    return 0;
}
