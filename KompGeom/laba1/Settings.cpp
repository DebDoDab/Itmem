//
// Created by vadim on 9.02.20.
//

#include "Settings.h"
#include "Functional.h"

Settings::Settings(int argc, char **argv) {
    input = argv[1];
    output = argv[2];
    if (argv[3][0] == '0') {
        inverseColors = true;
    } else if (argv[3][0] == '1') {
        mirrorVertical = true;
    } else if (argv[3][0] == '2') {
        mirrorHorizontal = true;
    } else if (argv[3][0] == '3') {
        clockwizeTurn = true;
    } else if (argv[3][0] == '4') {
        counterclockwizeTurn = true;
    } else {
        cout << "Wrong command\nYou entered: " << argv[3] << endl;
    }
}

void Settings::solve(Image& image) {
    if (inverseColors) {
        image.inverseColors();
    } else if (mirrorHorizontal) {
        image.mirrorHorizontal();
    } else if (mirrorVertical) {
        image.mirrorVertical();
    } else if (clockwizeTurn) {
        image.clockwizeTurn();
    } else if (counterclockwizeTurn) {
        image.counterclockwizeTurn();
    }

    image.write();
}
