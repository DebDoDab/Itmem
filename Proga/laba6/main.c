#include <stdio.h>
#include <stdlib.h>

int main() {
    int ar[4]; //Создаем массив
    int *p = &ar; //Создаем указатель на массив
    p[0] = 50; p[1] = 40; p[2] = 30; p[3] = 20; //Заполняем массив
    printf("idx : val\n");
    for (int i = 0; i < 4; i++) {
        printf("%d : %d\n", i, p[i]); //Выводим его по указателям
    }
    printf("\n");

    int *a;
    a = (int *) calloc(4, sizeof(int)); //Создаем динамический массив
    a[0] = 50; a[1] = 40; a[2] = 30; a[3] = 20;
    printf("\nidx : val\n");
    for (int i = 0; i < 4; i++) {
        printf("%d : %d\n", i, a[i]); //Выводим его
    }


    free(a);
    return 0;
}