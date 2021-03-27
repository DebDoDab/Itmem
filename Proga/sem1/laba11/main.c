#include <stdio.h>
#include "Pentagon.h"

int main() {
    struct Pentagon x;
    double R;
    scanf("%lf", &R);
    init(&x, R);
    printf("Perimeter = %lf", perimeter(x));
}
