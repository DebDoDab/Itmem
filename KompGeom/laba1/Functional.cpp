//
// Created by vadim on 9.02.20.
//

#include <bits/stdc++.h>
#include "Functional.h"

using namespace std;

using t3 = tuple<char, char, char>;
#define g0 get<0>
#define g1 get<1>
#define g2 get<2>

void Image::inverseColors() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            g0(pixels[i][j]) = 255 - g0(pixels[i][j]);
            g1(pixels[i][j]) = 255 - g1(pixels[i][j]);
            g2(pixels[i][j]) = 255 - g2(pixels[i][j]);
        }
    }
}

void Image::mirrorHorizontal() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < (width >> 1); j++) {
            swap(pixels[i][j], pixels[i][width - j - 1]);
        }
    }
}

void Image::mirrorVertical() {
    for (int i = 0; i < (height >> 1); i++) {
        swap(pixels[i], pixels[height - i - 1]);
    }
}

void Image::clockwizeTurn() {
    auto temp = pixels;
    pixels.assign(width, vector<t3>(height, {0, 0, 0}));
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            pixels[i][j] = temp[height - j - 1][i];
        }
    }
}

void Image::counterclockwizeTurn() {
    auto temp = pixels;
    pixels.assign(width, vector<t3>(height, {0, 0, 0}));
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            pixels[i][j] = temp[j][width - i - 1];
        }
    }
}

void Image::read() {
    ifstream cin(inputFile);
    cin >> header; ///P6
    cin >> height >> width;
    cin >> maxValue;
    cin.ignore();

    pixels.assign(height, vector<t3>(width, {0, 0, 0}));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cin.read(&g0(pixels[i][j]), 1);
            cin.read(&g1(pixels[i][j]), 1);
            cin.read(&g2(pixels[i][j]), 1);
        }
    }
}

void Image::write() {
    ofstream fout(outputFile);
    fout << header << "\n" << height << " " << width << "\n" << maxValue << "\n";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fout.write(&g0(pixels[i][j]), 1);
            fout.write(&g1(pixels[i][j]), 1);
            fout.write(&g2(pixels[i][j]), 1);
        }
    }
}

Image::Image(const string& input, const string& output) {
    inputFile = input;
    outputFile = output;
    height = width = maxValue = 0;
    this->read();
}
