#include <stdio.h>
#include <math.h> //подключаю библиотеку math.h, в которой есть cos, sin, sqrt

#define PI M_PI

int main() {
    double x; //объявляем вещественную переменную
    scanf("%lf", &x); //считываем ее через “%lf”
    double z1 = cos(3. / 8. * PI - x / 4.) * cos(3. / 8. * PI - x / 4.) -
                cos(11. / 8. * PI + x / 4.) * cos(11. / 8. * PI + x / 4.);
    double z2 = sqrt(2.) / 2. * sin(x / 2.);
    printf("z1 = %lf, z2 = %lf", z1, z2);
    return 0;
}