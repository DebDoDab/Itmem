//
// Created by vadim on 3.03.20.
//

#include "Array.h"

Array::Array() {
    a = {1, 2, 3};
}

Array::Array(const int &len) {
    a.assign(len, 0);
}

Array::Array(const vector<int> &x) {
    a = x;
}

bool Array::operator==(const Array &x) const {
    return a.size() == x.a.size();
}

bool Array::operator!=(const Array &x) const {
    return a.size() != x.a.size();
}

bool Array::operator<(const Array &x) const {
    return a.size() < x.a.size();
}

bool Array::operator>(const Array &x) const {
    return a.size() > x.a.size();
}

void Array::print() {
    cout << "Array: len = " << a.size() << "\n";
    for (auto &x : a) {
        cout << x << " ";
    }
    cout << "\n";
}

Array Array::operator+(const Array &x) const {
    Array temp(*this);
    for (auto &y : x.a) {
        temp.a.push_back(y);
    }
    return temp;
}