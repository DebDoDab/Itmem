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

    Polynom(const float &, const float &, const float &);

    Polynom(const string &);

    Polynom(const Polynom &);

    void print();

    float solve(const float &);

    vector<float> solve();

    int solveCount();

    float findMin();

    float findMax();
};
