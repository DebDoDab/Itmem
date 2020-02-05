#include <stdio.h>

int main(int argc, char **argv) {
    ///Пользователю дан текстовый файл. В файле находится группа цифр, каждая от другой отделена пробелом.
    ///Первая цифра в диапазоне от 1 до 100 определяет кол-во последующих цифр в файле.
    ///Написать программу, которая обработает цифры в файле след. образом: найти макс значение среди цифр,
    /// начиная со второй, найти сумму этих цифр. Найденные значения вывести на экран

    if (argc < 2) {
        printf("Write filename");
        return 0;
    }

    char *fileName = argv[1];
    FILE *file = fopen(fileName, "r");

    int n = 0;
    fscanf(file, "%d", &n);

    int sum = 0, mx = -2147483648;

    for (int i = 0; i < n; i++) {
        int x = 0;
        fscanf(file, "%d", &x);
        sum += x;
        if (x > mx) mx = x;
    }

    fclose(file);

    printf("Max = %d, Sum = %d\n", mx, sum);

}