//
// Created by vadim on 6.03.20.
//
#include <bits/stdc++.h>
#include "Exceptions.h"
#include "Image.h"

using namespace std;

#ifndef LABA2_SETTINGS_H
#define LABA2_SETTINGS_H


class Settings {
private:
    string input, output;
    int color;
    double thickness;
    Point begin, end;
    double gamma;
    Image image;

public:
    Settings(int argc, char** argv);
};


#endif //LABA2_SETTINGS_H
