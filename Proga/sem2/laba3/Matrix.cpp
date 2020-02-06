//
// Created by vadim on 5.02.20.
//

#include "Matrix.h"

Matrix::Matrix() {
    a.assign(n, vector<float>(m, 0));
}

Matrix::Matrix(const vector<vector<float>> &x) {
    if (x.size() == 3 && x[0].size() == 3) {
        a = x;
    } else {
        cout << "Wrong matrix!\n";
        *this = Matrix();
    }
}

Matrix::Matrix(const Matrix &x) {
    a = x.a;
}

Matrix Matrix::operator*(const Matrix &b) const {
    Matrix c;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < m; k++) {
                c.a[i][j] = a[i][j] * b.a[j][k];
            }
        }
    }
    return c;
}

Matrix Matrix::operator*(const float &x) const {
    Matrix c;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            c.a[i][j] = a[i][j] * x;
        }
    }
    return c;
}

Matrix Matrix::operator+(const Matrix &x) const {
    Matrix c;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            c.a[i][j] = a[i][j] + x.a[i][j];
        }
    }
    return c;
}

Matrix Matrix::operator-(const Matrix &x) const {
    Matrix c;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            c.a[i][j] = a[i][j] - x.a[i][j];
        }
    }
    return c;
}

bool Matrix::operator==(const Matrix &x) const {
    if (n != x.n && m != x.m) return false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] != x.a[i][j]) return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix &x) const {
    return !(*this == x);
}

bool Matrix::operator<(const Matrix &x) const {
    if (n != x.n && m != x.m) return false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] > x.a[i][j]) return false;
            else if (a[i][j] < x.a[i][j]) return true;
        }
    }
    return false;
}

bool Matrix::operator>(const Matrix &x) const {
    if (n != x.n && m != x.m) return false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] < x.a[i][j]) return false;
            else if (a[i][j] > x.a[i][j]) return true;
        }
    }
    return false;
}

void Matrix::print() {
    cout << "Matrix: n = " << n << ", m = " << m << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}