#include <stdio.h>

int main() {
    int x;
    scanf("%d", &x); //cчитываем наше число
    printf("%d\n", (x >= 23) && (x <= 32)); //проверям его принадлежность к диапазону [23; 32]
    int y;
    scanf("%x", &y);
    printf("%d\n", !!(y & (1 << 6))); //также можно написать (y >> 6) & 1
    printf("%d\n", !!(y & 64));
    return 0;
}