#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *take_number(FILE *input);
int gamma_epsilon(int const *count_of_1, int size, int count);
int to_decimal(char *number);
char often_bit(char **numbers, int size, int j);
char *oxygen(char **numbers, int size, int j);
char *CO2(char **numbers, int size, int j);

int main(int argc, char *argv[argc])
{
    FILE *input;
    if (argc != 2) {
        return 1;
    }
    input = fopen(argv[1], "r");
    int *count_of_1 = NULL;
    int size = 0;
    char *number;
    int count = 0;
    while ((number = take_number(input)) != NULL) {
        int len = (int)strlen(number);
        if (size == 0) {
            count_of_1 = realloc(count_of_1, len * sizeof(int));
            for (int i = size; i < len; i++) {
                count_of_1[size] = 0;
            }
            size = len;
        }
        if (len != size) {
            return 1;
        }
        for (int i = 0; i < size; i++) {
            if (number[len - 1 - i] == '1') {
                count_of_1[i]++;
            }
        }
        free(number);
        count++;
    }
    printf("%d\n", gamma_epsilon(count_of_1, size, count));
    rewind(input);
    char often;
    char **numbers_often = NULL;
    int size_numbers_often = 0;
    if (count_of_1[size - 1] >= count / 2) {
        often = '1';
    } else {
        often = '0';
    }
    while ((number = take_number(input)) != NULL) {
        if (number[0] == often) {
            numbers_often = realloc(numbers_often,
                                    (size_numbers_often + 1) * sizeof(char *));
            numbers_often[size_numbers_often] =
                malloc((size + 1) * sizeof(char));
            numbers_often[size_numbers_often] = number;
            size_numbers_often++;
        }
    }
    char *oxy = oxygen(numbers_often, size_numbers_often, 1);
    rewind(input);
    char rare;
    char **numbers_rare = NULL;
    int size_numbers_rare = 0;
    if (count_of_1[size - 1] > count / 2) {
        rare = '0';
    } else {
        rare = '1';
    }
    while ((number = take_number(input)) != NULL) {
        if (number[0] == rare) {
            numbers_rare =
                realloc(numbers_rare, (size_numbers_rare + 1) * sizeof(char *));
            numbers_rare[size_numbers_rare] = malloc((size + 1) * sizeof(char));
            numbers_rare[size_numbers_rare] = number;
            size_numbers_rare++;
        }
    }
    char *co2 = CO2(numbers_rare, size_numbers_rare, 1);
    printf("%d\n", to_decimal(co2) * to_decimal(oxy));
    free(co2);
    free(oxy);
    free(count_of_1);
    fclose(input);
    return 0;
}

char *take_number(FILE *input)
{
    char *number = NULL;
    int length = 0;
    char c;
    int res;
    while ((res = fscanf(input, "%c", &c) == 1) && c != '\n') {
        length++;
        number = realloc(number, (length + 1) * sizeof(char));
        number[length - 1] = c;
        number[length] = '\0';
    }
    if (res == EOF) {
        return NULL;
    }
    return number;
}

int gamma_epsilon(int const *count_of_1, int size, int count)
{
    int gamma = 0;
    int epsilon = 0;
    for (int i = size - 1; i >= 0; i--) {
        if (count_of_1[i] > count / 2) {
            gamma = 2 * gamma + 1;
            epsilon = 2 * epsilon;
        } else {
            gamma = 2 * gamma;
            epsilon = 2 * epsilon + 1;
        }
    }
    return gamma * epsilon;
}

int to_decimal(char *number)
{
    int num = 0;
    int len = (int)strlen(number);
    for (int i = 0; i < len; i++) {
        num = 2 * num + (int)number[i] - (int)'0';
    }
    return num;
}

char often_bit(char **numbers, int size, int j)
{
    int count_1 = 0;
    int count_0 = 0;
    for (int i = 0; i < size; i++) {
        if (numbers[i][j] == '1') {
            count_1 += 1;
        } else {
            count_0 += 1;
        }
    }
    if (count_1 >= count_0) {
        return '1';
    }
    if (count_1 < count_0) {
        return '0';
    }
    return '2';
}

char *oxygen(char **numbers, int size, int j)
{
    if (size == 1) {
        return numbers[0];
    }
    char **new_numbers = NULL;
    int new_size = 0;
    int len = (int)strlen(numbers[0]);
    char often = often_bit(numbers, size, j);
    if (often == '2') {
        often = '1';
    }
    for (int i = 0; i < size; i++) {
        if (len - 1 >= j) {
            if (numbers[i][j] == often) {
                new_numbers =
                    realloc(new_numbers, (new_size + 1) * sizeof(char *));
                new_numbers[new_size] = malloc((len + 1) * sizeof(char));
                new_numbers[new_size] = numbers[i];
                new_size++;
            }
        }
    }
    free(numbers);
    return oxygen(new_numbers, new_size, j + 1);
}

char *CO2(char **numbers, int size, int j)
{
    if (size == 1) {
        return numbers[0];
    }
    char **new_numbers = NULL;
    int new_size = 0;
    int len = (int)strlen(numbers[0]);
    char rare = often_bit(numbers, size, j);
    if (rare == '1' || rare == '2') {
        rare = '0';
    } else {
        rare = '1';
    }
    for (int i = 0; i < size; i++) {
        if (len - 1 >= j) {
            if (numbers[i][j] == rare) {
                new_numbers =
                    realloc(new_numbers, (new_size + 1) * sizeof(char *));
                new_numbers[new_size] = malloc((len + 1) * sizeof(char));
                new_numbers[new_size] = numbers[i];
                new_size++;
            }
        }
    }
    free(numbers);
    return CO2(new_numbers, new_size, j + 1);
}
