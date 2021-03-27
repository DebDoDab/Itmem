//
// Created by vadim on 3.03.20.
//
#include <bits/stdc++.h>
using namespace std;

#pragma once


class Square {
private:
    pair<float, float> pos;
    float len;
    float alpha;

public:
    Square();
    Square(const float &, const float &, const float &, const float &);
    Square(const Square &);

    bool operator==(const Square &) const;
    bool operator!=(const Square &) const;
    bool operator<(const Square &) const;
    bool operator>(const Square &) const;
    void print();

    Square operator*(const float &) const;
    Square operator+(const pair<float, float> &) const;
};

