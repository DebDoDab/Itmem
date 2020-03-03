//
// Created by vadim on 3.03.20.
//

#include "Square.h"

Square::Square() {
    pos = {0, 0};
    len = 3;
    alpha = 0;
}

Square::Square(const float &posx, const float &posy, const float &len_, const float &alpha_) {
    pos = {posx, posy};
    len = len_;
    alpha = alpha_;
}

Square::Square(const Square &x) {
    pos = x.pos;
    len = x.len;
    alpha = x.alpha;
}

bool Square::operator==(const Square &x) const {
    return len == x.len;
}

bool Square::operator!=(const Square &x) const {
    return len != x.len;
}

bool Square::operator<(const Square &x) const {
    return len < x.len;
}

bool Square::operator>(const Square &x) const {
    return len > x.len;
}

void Square::print() {
    cout << "position = {" << pos.first << ", " << pos.second << "};\tlen = " << len <<
            ";\tangle between square side and OX = " << alpha * 180. / M_PI << " degrees\n";
}

Square Square::operator*(const float &x) const {
    Square a(*this);
    a.len *= x;
    return a;
}

Square Square::operator+(const pair<float, float> &x) const {
    Square a(*this);
    a.pos.first += x.first;
    a.pos.second += x.second;
    return a;
}

