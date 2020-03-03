//
// Created by vadim on 9.02.20.
//

#include "Settings.h"
#include "Functional.h"
#include "Exceptions.h"

Settings::Settings(int argc, char **argv) {
    input = argv[1];
    output = argv[2];
    if (output == "same") {
        output = input;
    }

    cmd = static_cast<Command>(int(argv[3][0]));
    cout << cmd << endl;

    ifstream fin(input);
    if (!fin.is_open()) {
        throw WrongFile();
    }
    string s;
    fin >> s;
    if (s == "P6") {
        image = new ImageColored(input, output);
    } else if (s == "P5") {
        image = new ImageGrayscale(input, output);
    } else {
        throw WrongFormat();
    }
}

void Settings::solve() {
    switch (cmd) {
        case Command::inverseColors:
            image->inverseColors();
            break;
        case Command::mirrorHorizontal:
            image->mirrorHorizontal();
            break;
        case Command::mirrorVertical:
            image->mirrorVertical();
            break;
        case Command::clockwizeTurn:
            image->clockwizeTurn();
            break;
        case Command::counterclockwizeTurn:
            image->counterclockwizeTurn();
            break;
        default:
            throw WrongCommand();
    }

    image->write();
}
