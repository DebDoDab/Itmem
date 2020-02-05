//
// Created by vadim on 5.02.20.
//
#include <bits/stdc++.h>
using namespace std;

#pragma once

void floor_(float *x);
void floor_(float &x);

void inv(float *x);
void inv(float &x);
void inv(int *x);
void inv(int &x);

struct Circle {
    float r;
    float x;
    float y;

    Circle(float r_, float x_, float y_) {
        r = r_;
        x = x_;
        y = y_;
    }

    void print() {
        cout << "Circle: \n" << "r: " << r << ", x: " << x << ", y: " << y << "\n\n";
    }
};

void move(Circle *x, const float *delta_x, const float *delta_y);
void move(Circle &x, const float &delta_x, const float &delta_y);

struct Matrix {
    int n, m;
    vector<vector<int>> a;

    Matrix() {
        srand(time(NULL));
        n = 3;
        m = 3;
        a.assign(n, vector<int>(m, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                a[i][j] = rand() % 10;
            }
        }
    }

    void print() {
        cout << "Matrix:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << a[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};

void mult(Matrix &x, const int &delta);
void mult(Matrix *x, const int *delta);