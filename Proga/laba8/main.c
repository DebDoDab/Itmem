#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    ///lab rab 8
    int n = 50;
    char *str1 = (char *) malloc(sizeof(char) * n);
    char *str2 = (char *) malloc(sizeof(char) * n);
    char *str3 = (char *) malloc(sizeof(char) * n);
    char *str5 = (char *) malloc(sizeof(char) * n);
    char *str7 = (char *) malloc(sizeof(char) * n);
    char *str8 = (char *) malloc(sizeof(char) * n);
    char *str9 = (char *) malloc(sizeof(char) * n);
    char *str0 = (char *) malloc(sizeof(char) * n);

    //2. Осуществить конкатенация (сложение) первой строки и n начальных символов второй строки.
    scanf("%s", str1);
    scanf("%s", str2);
    int x;
    scanf("%d", &x);
    char *temp = (char *) malloc(sizeof(char) * x);
    strncpy(temp, str2, x); //temp – первые x символов со второй строки
    strcat(str1, temp); //Объединяем первую строку и первые x символов второй строки
    printf("%s\n", str1);

    //7. Определить длину строки.
    scanf("%s", str3);
    printf("%d\n", strlen(str3)); //Вычисляем длину

    //9. Осуществить поиск в строке последнего вхождения указанного символа.
    char c;
    scanf("%s", str5);
    c = getc(stdin); //Считываем пробел
    c = getc(stdin); //Считываем символ
    printf("%d\n", strrchr(str5, c) - str5 + 1); //Находим правое вхождение

    //11. Определить длину отрезка одной строки, содержащего символы из множества символов, входящих во вторую строку.
    scanf("%s", str7);
    scanf("%s", str8);
    printf("%d\n", strspn(str7, str8));

    //13. Выделить из одной строки лексемы (кусочки), разделенные любым из множества символов (разделителей), входящих во вторую строку.
    scanf("%s", str9);
    scanf("%s", str0);
    char *token = strtok(str9, str0);
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, str0);
    }

    return 0;
}