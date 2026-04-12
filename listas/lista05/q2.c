#include <stdio.h>
#include <stdlib.h>

float average_grade(float *grades, int n);


float *higher_grade_and_student(float *grades, int n) {
    float* result = (float *) malloc(2 * sizeof(float));
    float higher_grade = 0.0; // inicializa a maior nota com o valor mínimo possível
    float student_index = -1; // inicializa o índice do aluno com um valor inválido
    for (int i = 0; i < n; i++) {
        if (grades[i] > higher_grade) {
            higher_grade = grades[i];
            student_index = i;
        }
    }
    result[0] = higher_grade;
    result[1] = student_index + 1;
    return result;
}

float *lower_grade_and_student(float *grades, int n) {
    float* result = (float *) malloc(2 * sizeof(float));
    float lower_grade = 100.0; // inicializa a menor nota com o valor máximo possível
    float student_index = -1; // inicializa o índice do aluno com um valor inválido
    for (int i = 0; i < n; i++) {
        if (grades[i] < lower_grade) {
            lower_grade = grades[i];
            student_index = i;
        }
    }
    result[0] = lower_grade;
    result[1] = student_index + 1;
    return result;
}

int count_students_above_average(float *grades, int n)  {
    int count = 0;
    float avg = average_grade(grades, n);
    for (int i = 0; i < n; i++) {
        if (grades[i] > avg) {
            count++;
        }
    }
    return count;
}

float average_grade(float *grades, int n) {
    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum += grades[i];
    }
    return sum / n;
}

float median(float *grades, int n) {
    float *copy = (float *) malloc( n * sizeof(float));
    for (int i = 0; i < n; i++) {
        copy[i] = grades[i];
    }

    // ordena a cópia do array de notas usando bubble sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (copy[j] > copy[j + 1]) {
                float temp = copy[j];
                copy[j] = copy[j + 1];
                copy[j + 1] = temp;
            }
        }
    }

    // calcula a mediana
    float median;
    if (n % 2 == 1) { // quando o número de elementos é ímpar, a mediana é o elemento do meio
        median = copy[n / 2];
    } else { // quando o número de elementos é par, a mediana é a média dos dois elementos do meio
        median = (copy[n / 2 - 1] + copy[n / 2]) / 2.0;
    }
    free(copy);
    return median;
}

float mode(float *grades, int n) {
    float mode = -1; // inicializa a moda com um valor inválido
    int maxCount = 1;
    int hasTie = 0;

    for (int i = 0; i < n; i++) {
        int count = 1;
        for (int j = i + 1; j < n; j++) {
            if (grades[i] == grades[j]) {
                count++;
            }
        }

        if (count > maxCount) {
            maxCount = count;
            mode = grades[i];
            hasTie = 0;
        } else if (count == maxCount && count > 1 && grades[i] != mode) {
            hasTie = 1;
        }
    }

    if (hasTie || maxCount == 1) {
        return -1;
    }

    return mode; // se retornar -1, não tem moda
}

void print_report(float *grades, int n, const char *title) {
    printf("%s\n", title);
    printf("Media: %.2f\n", average_grade(grades, n));

    float *higher_info = higher_grade_and_student(grades, n);
    printf("Maior nota: %.2f (aluno %.0f)\n", higher_info[0], higher_info[1]);
    free(higher_info);

    float *lower_info = lower_grade_and_student(grades, n);
    printf("Menor nota: %.2f (aluno %.0f)\n", lower_info[0], lower_info[1]);
    free(lower_info);

    printf("Acima da media: %d\n", count_students_above_average(grades, n));
    printf("Mediana: %.2f\n", median(grades, n));
    float mode_value = mode(grades, n);
    if (mode_value == -1) {
        printf("Moda: Nao ha moda unica\n");
    } else {
        printf("Moda: %.2f\n", mode_value);
    }
}

int main()
{
    int initialStudentsCount = 0;
    scanf("%d", &initialStudentsCount);
    float *grades = (float *) malloc(initialStudentsCount * sizeof(float));
    for (int i = 0; i < initialStudentsCount; i++) { // inicializa as notas iniciais
        scanf("%f", &grades[i]);
    }
    print_report(grades, initialStudentsCount, "Relatorio inicial");
    
    int newGradesToBeAdded = 0;
    scanf("%d", &newGradesToBeAdded);

    int updatedStudentsCount = initialStudentsCount + newGradesToBeAdded;
    float *resized_grades = (float *) realloc(grades, updatedStudentsCount * sizeof(float));
    grades = resized_grades;

    for (int i = 0; i < newGradesToBeAdded; i++) {
        scanf("%f", &grades[initialStudentsCount + i]);
    }

    printf("\n");
    print_report(grades, updatedStudentsCount, "Relatorio atualizado");

    free(grades);
    return 0;
}