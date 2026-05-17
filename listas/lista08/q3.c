#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    double sepal_length, sepal_width, petal_length, petal_width;
    char species[32];
} CSVRow;

typedef struct {
    double avg_sepal_length, avg_sepal_width, avg_petal_length, avg_petal_width;
    char mode_species[32];
} Stats;

Stats calc_stats(const CSVRow *rows, size_t size)
{
    Stats stats = {0};

    if (size == 0) {
        return stats;
    }

    /* Acumula os valores para calcular medias das colunas numericas. */
    double sum_sepal_length = 0.0;
    double sum_sepal_width = 0.0;
    double sum_petal_length = 0.0;
    double sum_petal_width = 0.0;

    for (size_t i = 0; i < size; i++) {
        sum_sepal_length += rows[i].sepal_length;
        sum_sepal_width += rows[i].sepal_width;
        sum_petal_length += rows[i].petal_length;
        sum_petal_width += rows[i].petal_width;
    }

    stats.avg_sepal_length = sum_sepal_length / size;
    stats.avg_sepal_width = sum_sepal_width / size;
    stats.avg_petal_length = sum_petal_length / size;
    stats.avg_petal_width = sum_petal_width / size;

    /* Determina a moda da especie por contagem de frequencia. */
    int best_count = 0;
    stats.mode_species[0] = '\0';

    for (size_t i = 0; i < size; i++) {
        int count = 0;

        for (size_t j = 0; j < size; j++) {
            if (strcmp(rows[i].species, rows[j].species) == 0) {
                count++;
            }
        }

        if (count > best_count ||
            (count == best_count && (stats.mode_species[0] == '\0' || strcmp(rows[i].species, stats.mode_species) < 0))) {
            best_count = count;
            strncpy(stats.mode_species, rows[i].species, sizeof(stats.mode_species) - 1);
            stats.mode_species[sizeof(stats.mode_species) - 1] = '\0';
        }
    }

    return stats;
}

void write_stats(FILE *file, const Stats *stats)
{
    fprintf(file, "\nsummary,avg_sepal_length,avg_sepal_width,avg_petal_length,avg_petal_width,mode_species\n");
    fprintf(file, "Summary,%.4f,%.4f,%.4f,%.4f,%s\n",
            stats->avg_sepal_length,
            stats->avg_sepal_width,
            stats->avg_petal_length,
            stats->avg_petal_width,
            stats->mode_species);
}

int main(void)
{
    int numberOfFiles;
    char line[256];

    if (scanf("%d", &numberOfFiles) != 1) {
        return 1;
    }

    for (int i = 1; i <= numberOfFiles; i++) {
        /* Armazena todas as linhas validas do CSV atual em memoria. */
        CSVRow *rows = NULL;
        size_t size = 0;
        size_t capacity = 0;

        char name[128];
        snprintf(name, sizeof(name), "listas/lista08/iris%d.csv", i);

        FILE *file = fopen(name, "r");
        if (!file) {
            perror(name);
            continue;
        }

        /* Le e preserva o cabecalho original do arquivo. */
        char header[512] = {0};
        if (fgets(line, sizeof(line), file)) {
            size_t hlen = strlen(line);
            while (hlen > 0 && (line[hlen-1] == '\n' || line[hlen-1] == '\r')) line[--hlen] = '\0';
            strncpy(header, line, sizeof(header)-1);
            header[sizeof(header)-1] = '\0';

            printf("===== %s =====\n", name);
            printf("%s\n", header);
        }

        /* Faz o parse das linhas, descartando entradas mal formatadas. */
        while (fgets(line, sizeof(line), file)) {
            size_t len = strlen(line);
            while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
                line[--len] = '\0';
            }

            CSVRow tmp;
            if (sscanf(line, "%lf,%lf,%lf,%lf,%31[^\n\r]",
                       &tmp.sepal_length, &tmp.sepal_width,
                       &tmp.petal_length, &tmp.petal_width,
                       tmp.species) != 5) {
                continue;
            }

            if (size == capacity) {
                /* Cresce o vetor dinamico conforme a quantidade de linhas lidas. */
                size_t newCapacity = (capacity == 0) ? 4 : capacity * 2;
                CSVRow *newRows = realloc(rows, newCapacity * sizeof(CSVRow));
                if (!newRows) {
                    free(rows);
                    fclose(file);
                    fprintf(stderr, "Memory allocation failed\n");
                    return 1;
                }
                rows = newRows;
                capacity = newCapacity;
            }

            rows[size] = tmp;
            size++;
            printf("%s\n", line);
        }

        fclose(file);

        if (size > 0) {
            Stats stats = calc_stats(rows, size);

            FILE *fw = fopen(name, "w");
            if (!fw) {
                perror(name);
                free(rows);
                continue;
            }

            /* Reescreve o CSV com os dados originais e uma linha final de resumo. */
            fprintf(fw, "%s,avg_sepal_length,avg_sepal_width,avg_petal_length,avg_petal_width,mode_species\n", header);

            for (size_t r = 0; r < size; ++r) {
                fprintf(fw, "%.4g,%.4g,%.4g,%.4g,%s,,,,,\n",
                        rows[r].sepal_length,
                        rows[r].sepal_width,
                        rows[r].petal_length,
                        rows[r].petal_width,
                        rows[r].species);
            }

            fprintf(fw, "Summary,,,,,%.4f,%.4f,%.4f,%.4f,%s\n",
                    stats.avg_sepal_length,
                    stats.avg_sepal_width,
                    stats.avg_petal_length,
                    stats.avg_petal_width,
                    stats.mode_species);

            if (fflush(fw) != 0 || ferror(fw)) perror("write");
            fclose(fw);
        }
        free(rows);
        printf("\n");
    }

    return 0;
}
