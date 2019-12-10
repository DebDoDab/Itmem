#include <stdio.h>

int main() {
    int x[7] = {90, 76, 54, 23, 56, 12, 48};
    printf("\nidx : val\n");
    for (int i = 0; i < 7; i++) {
        printf("%d : %d\n", i, x[i]); //Выводим массив
    }

    int a[2][2] = {{2, 5}, {2, 2}}; //Задаем матрицы
    int b[2][2] = {{1, 2}, {0, 1}};
    int c[2][2] = {{0, 0}, {0, 0}};
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int h = 0; h < 2; h++) {
                c[i][j] += a[i][h] * b[h][j]; //Перемножаем
            }
        }
    }
    printf("\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", c[i][j]); //Выводим результат перемножения матриц
        }
        printf("\n");
    }
    return 0;
}