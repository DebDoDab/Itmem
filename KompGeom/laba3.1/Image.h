//
// Created by vadim on 6.03.20.
//
#include <bits/stdc++.h>
#include <chrono>
#include "Exceptions.h"

using namespace std;

#ifndef LABA3_1_IMAGE_H
#define LABA3_1_IMAGE_H

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

    unsigned char tosrgb(unsigned char color);

    unsigned char tolinear(unsigned char color);

    void gradientGenerate();

    void noDithering(int bitRate);
    void OrderedDithering(int bitRate);
    void RandomDithering(int bitRate);
    void FloydSteinbergDithering(int bitRate);
    void JJNDithering(int bitRate);
    void SieraDithering(int bitRate);
    void AtkinsonDithering(int bitRate);
    void HalftoneDithering(int bitRate);
};


#endif //LABA3_1_IMAGE_H
