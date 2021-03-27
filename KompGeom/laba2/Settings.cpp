//
// Created by vadim on 6.03.20.
//

#include "Settings.h"

Settings::Settings(int argc, char** argv) {
    if (argc < 9 || argc > 10) {
        throw ArgsEsception();
    }
    input = argv[1];
    output = argv[2];
    color = stoi(argv[3]);
    thickness = stod(argv[4]);
    begin = Point(stod(argv[5]), stod(argv[6]));
    end = Point(stod(argv[7]), stod(argv[8]));
    gamma = 2.2; //Default value
    if (argc == 10) {
        gamma = stod(argv[9]);
    }
    image = Image(input, output);
    image.drawLine(begin, end, thickness, color, gamma);
    image.write();
}
