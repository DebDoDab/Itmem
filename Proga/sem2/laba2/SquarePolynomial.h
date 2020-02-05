//
// Created by vadim on 5.02.20.
//

#include <bits/stdc++.h>
#include <string>
using namespace std;

#pragma once

class Polynom {
private:
    float a, b, c;

public:
    Polynom();

    Polynom(const float &a_, const float &b_, const float &c_);

    Polynom(const string &s);

    Polynom(const Polynom &x);

    void print();

    float solve(const float &x);

    vector<float> solve();

    int solveCount();

    float findMin();

    float findMax();
};
