#include <stdio.h>
#include <math.h>
#include <string.h>

float max(float a, float b) {
    return a > b ? a : b;
}

int main() {
    ///2
    float all;
    printf("Продолжительность разговоров: ");
    scanf("%f", &all);

    float cost_month;
    printf("Абонентская плата: ");
    scanf("%f", &cost_month);

    float cost_extra;
    printf("Стоимость дополнительной минуты: ");
    scanf("%f", &cost_extra);

    while (cost_extra <= (cost_month / 499.0)) { //Если доп.плата меньше абонентской
        printf("Стоимость дополнительной минуты должна быть больше минуты в тарифе. Попробуйте еще раз: "); //То вводим новую, пока не введется нормальная доп плата
        scanf("%f", &cost_extra);
    }

    printf("Стоимость обслуживания: %0.2lfRUB\n\n", cost_month + (max(all - 499.0, 0.0) * cost_extra)); //Абон плата + штрафные минуты (если есть) * их цену

    ///4
    int maxn;
    printf("Введите число, до которого нужно ввести простые ");
    scanf("%d", &maxn);
    int arr[1001]; //Делаем массив для решета Эратосфена
    memset(arr, 0, 1001);
    for (int i = 2; i <= maxn; i++) {
        if (!arr[i]) {  //Если наше число простое
            printf("%d ", i); //То выводим его
            for (int j = i * i; j <= maxn; j += i) {
                arr[j] = 1;
            }
        }
    }
    return 0;
}