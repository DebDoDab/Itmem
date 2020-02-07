//
// Created by vadim on 7.02.20.
//
#include <bits/stdc++.h>

using namespace std;

#pragma once

template <typename T>
class Matrix {
private:
    int n, m;
    vector<vector<T>> x;

public:
    Matrix();
    Matrix(int n_, int m_);
    Matrix(Matrix& x_);
    Matrix(vector<vector<T>>& x_);

    pair<int, int> getSize();
    T get(int i, int j);
    void editField(int i, int j, T a);
};

class OutOfRangeException : public exception {
public:
    const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        return "Out of range\n";
    }
};

#include "classes.tpp"

