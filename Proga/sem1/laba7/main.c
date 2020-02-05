#include <stdio.h>

enum sweet {pie, cake, brownie, icecream, candy}; //Инициализирую данные перечисляемого типа

struct S {
    double x, y, a; //Объявляем структуру квадрата: расположение левого нижнего угла
};				//и длина его стороны

union Printer {
    struct laser_printer {
        unsigned elements : 1; //Отводим по одному биту на состояния в структуре
        unsigned low_toner : 1;
        unsigned broken : 1;
        unsigned no_paper : 1;
    } stats;
    unsigned input; //Объединяем состояния с input
} printer;

int main() {
    enum sweet sweets = candy; //Объявляю sweets типа sweet
    printf("%d\n", sweets); // Вывожу число, соответсвующее конфете


    struct S square = {0, 0, 5.2}; //Объявляем переменную класса S
    double perimeter = square.a * 4; //Вычисляем его периметр
    printf("%lf\n", perimeter);


    scanf("%x", &printer.input);
    printf("Элементы: %s\n", printer.stats.elements ? "ON" : "OFF");
    printf("Мало тонера: %s\n", printer.stats.low_toner ? "ON" : "OFF");
    printf("Сломан: %s\n", printer.stats.broken ? "ON" : "OFF");
    printf("Нет бумаги: %s\n", printer.stats.no_paper ? "ON" : "OFF");
    return 0;
}