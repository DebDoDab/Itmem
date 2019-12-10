//
// Created by vadim on 4.11.19.
//

#include "Pentagon.h"
#include <math.h>

double perimeter(struct Pentagon x) {
    float t = x.R * sqrt(5 - sqrt(5)) / 2;
    return t * 5;
}

void init(struct Pentagon* x, double R) {
    x->R = R;
    return;
}