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
    Matrix(int, int);
    Matrix(Matrix&);
    Matrix(vector<vector<T>>&);

    pair<int, int> getSize();
    T get(int, int);
    void editField(int, int, T);
};

class OutOfRangeException : public exception {
public:
    const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

#include "classes.tpp"

