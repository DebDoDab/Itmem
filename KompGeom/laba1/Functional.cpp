//
// Created by vadim on 9.02.20.
//

#include <bits/stdc++.h>
#include "Functional.h"
#include "Exceptions.h"

using namespace std;

using t3 = tuple<char, char, char>;
#define g0 get<0>
#define g1 get<1>
#define g2 get<2>

void ImageColored::inverseColors() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            g0(pixels[i][j]) = maxValue - g0(pixels[i][j]);
            g1(pixels[i][j]) = maxValue - g1(pixels[i][j]);
            g2(pixels[i][j]) = maxValue - g2(pixels[i][j]);
        }
    }
}

void ImageGrayscale::inverseColors() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            pixels[i][j] = 255 - pixels[i][j];
        }
    }
}

void ImageColored::mirrorHorizontal() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < (width >> 1); j++) {
            swap(pixels[i][j], pixels[i][width - j - 1]);
        }
    }
}

void ImageGrayscale::mirrorHorizontal() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < (width >> 1); j++) {
            swap(pixels[i][j], pixels[i][width - j - 1]);
        }
    }
}

void ImageColored::mirrorVertical() {
    for (int i = 0; i < (height >> 1); i++) {
        swap(pixels[i], pixels[height - i - 1]);
    }
}

void ImageGrayscale::mirrorVertical() {
    for (int i = 0; i < (height >> 1); i++) {
        swap(pixels[i], pixels[height - i - 1]);
    }
}

void ImageColored::clockwizeTurn() {
    auto temp = pixels;
    pixels.assign(width, vector<t3>(height, {0, 0, 0}));
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            pixels[i][j] = temp[height - j - 1][i];
        }
    }
    swap(width, height);
}

void ImageGrayscale::clockwizeTurn() {
    auto temp = pixels;
    pixels.assign(width, vector<char>(height, 0));
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            pixels[i][j] = temp[height - j - 1][i];
        }
    }
    swap(width, height);
}

void ImageColored::counterclockwizeTurn() {
    auto temp = pixels;
    pixels.assign(width, vector<t3>(height, {0, 0, 0}));
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            pixels[i][j] = temp[j][width - i - 1];
        }
    }
    swap(width, height);
}

void ImageGrayscale::counterclockwizeTurn() {
    auto temp = pixels;
    pixels.assign(width, vector<char>(height, 0));
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            pixels[i][j] = temp[j][width - i - 1];
        }
    }
    swap(width, height);
}

void ImageColored::read() {
    ifstream cin(inputFile);
    cin >> header; ///P6
    cin >> width >> height;
    cin >> maxValue;
    cin.ignore();

    pixels.assign(height, vector<t3>(width, {0, 0, 0}));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (cin.eof()) {
                throw WrongSize();
            }

            cin.read(&g0(pixels[i][j]), 1);
            if (cin.eof()) {
                throw WrongSize();
            }

            cin.read(&g1(pixels[i][j]), 1);
            if (cin.eof()) {
                throw WrongSize();
            }

            cin.read(&g2(pixels[i][j]), 1);
        }
    }

    char x;
    while (!cin.eof()) {
        cin >> x;
//        cout << x;
    }

    if (!cin.eof()) {
        throw WrongSize();
    }
}

void ImageGrayscale::read() {
    ifstream cin(inputFile);
    cin >> header; ///P5
    cin >> width >> height;
    cin >> maxValue;
    cin.ignore();

    pixels.assign(height, vector<char>(width, 0));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (cin.eof()) {
                throw WrongSize();
            }
            cin.read(&pixels[i][j], 1);
        }
    }

    if (!cin.eof()) {
        throw WrongSize();
    }
}

void ImageColored::write() {
    ofstream fout(outputFile);
    fout << header << "\n" << width << " " << height << "\n" << maxValue << "\n";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fout.write(&g0(pixels[i][j]), 1);
            fout.write(&g1(pixels[i][j]), 1);
            fout.write(&g2(pixels[i][j]), 1);
        }
    }
}

void ImageGrayscale::write() {
    ofstream fout(outputFile);
    fout << header << "\n" << width << " " << height << "\n" << maxValue << "\n";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fout.write(&pixels[i][j], 1);
        }
    }
}

ImageColored::ImageColored(const string& input, const string& output) {
    inputFile = input;
    outputFile = output;
    height = width = maxValue = 0;
    this->read();
}

ImageGrayscale::ImageGrayscale(const string& input, const string& output) {
    inputFile = input;
    outputFile = output;
    height = width = maxValue = 0;
    this->read();
}
