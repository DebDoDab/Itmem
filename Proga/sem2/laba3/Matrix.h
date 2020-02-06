//
// Created by vadim on 5.02.20.
//
#include <bits/stdc++.h>
using namespace std;

#pragma once

class Matrix {
private:
    int n = 3, m = 3;
    vector<vector<float>> a;

public:
    Matrix();
    Matrix(const vector<vector<float>> &x);
    Matrix(const Matrix &x);
    Matrix operator*(const Matrix &b) const;
    Matrix operator*(const float &x) const;
    Matrix operator+(const Matrix &x) const;
    Matrix operator-(const Matrix &x) const;
    bool operator==(const Matrix &x) const;
    bool operator!=(const Matrix &x) const;
    bool operator<(const Matrix &x) const;
    bool operator>(const Matrix &x) const;
    void print();
};