//
// Created by vadim on 5.02.20.
//

#include "functional.h"

void floor_(float *x) {
    *x = float(int(*x));
}

void floor_(float &x) {
    x = float(int(x));
}

void inv(float *x) {
    *x = -(*x);
}

void inv(float &x) {
    x = -x;
}

void inv(int *x) {
    *x = -(*x);
}

void inv(int &x) {
    x = -x;
}

void move(Circle &x, const float &delta_x, const float &delta_y) {
    x.x += delta_x;
    x.y += delta_y;
}

void move(Circle *x, const float *delta_x, const float *delta_y) {
    x->x += *delta_x;
    x->y += *delta_y;
}

void mult(Matrix &x, const int &delta) {
    for (int i = 0; i < x.n; i++) {
        for (int j = 0; j < x.m; j++) {
            x.a[i][j] *= delta;
        }
    }
}

void mult(Matrix *x, const int *delta) {
    for (int i = 0; i < x->n; i++) {
        for (int j = 0; j < x->m; j++) {
            x->a[i][j] *= *delta;
        }
    }
}

