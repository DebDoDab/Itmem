//
// Created by vadim on 9.02.20.
//

#include <bits/stdc++.h>
#include "Functional.h"

using namespace std;

#ifndef LABA1_SETTINGS_H
#define LABA1_SETTINGS_H

/*
 * Commands:
 0 - inverse colors
 1 - mirror horizontally
 2 - mirror vertically
 3 - turn clockwize
 4 - turn counterclockwize
 */

class Settings {
public:
    string input, output;
    bool inverseColors = false;
    bool mirrorHorizontal = false;
    bool mirrorVertical = false;
    bool clockwizeTurn = false;
    bool counterclockwizeTurn = false;

public:
    Settings(int argc, char** argv);
    void solve(Image& image);
};


#endif //LABA1_SETTINGS_H
