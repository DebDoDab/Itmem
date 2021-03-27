//
// Created by vadim on 6.03.20.
//
#include <bits/stdc++.h>
#include "Exceptions.h"
#include "Image.h"

using namespace std;

#ifndef LABA3_1_SETTINGS_H
#define LABA3_1_SETTINGS_H


class Settings {
private:
    string input, output;
    int gradient;
    int bitRate;
    double gamma;
    Image image;
    int dithering;

public:
    Settings(int argc, char** argv);
};


#endif //LABA3_1_SETTINGS_H
