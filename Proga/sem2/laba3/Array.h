//
// Created by vadim on 3.03.20.
//
#include <bits/stdc++.h>
using namespace std;

#pragma once

class Array {
private:
    vector<int> a;

public:
    Array();
    Array(const int &);
    Array(const vector<int> &);

    bool operator==(const Array &) const;
    bool operator!=(const Array &) const;
    bool operator<(const Array &) const;
    bool operator>(const Array &) const;
    void print();

    Array operator+(const Array &) const;
};

