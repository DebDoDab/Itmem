//
// Created by vadim on 6.03.20.
//
#include <bits/stdc++.h>
#include "Exceptions.h"

using namespace std;

#ifndef LABA2_IMAGE_H
#define LABA2_IMAGE_H

class Point {
public:
    double x, y;
    Point();
    Point(double, double);
};

class Image {
public:
    string inputFile, outputFile;
    string header;
    int height, width, maxValue;
    vector<vector<char>> pixels;

public:
    Image();
    Image(const string& input, const string& output);
    void read();
    void write();
    void drawLine(Point begin, Point end, double thickness, int color, double gamma);
};


#endif //LABA2_IMAGE_H
