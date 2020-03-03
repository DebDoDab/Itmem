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
    enum Command {
        inverseColors = 0,
        mirrorHorizontal = 1,
        mirrorVertical = 2,
        clockwizeTurn = 3,
        counterclockwizeTurn = 4
    } cmd;
    Image* image = nullptr;

public:
    Settings(int argc, char** argv);
    void solve();
};


#endif //LABA1_SETTINGS_H
