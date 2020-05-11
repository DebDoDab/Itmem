//
// Created by vadim on 6.03.20.
//

#include "Settings.h"

Settings::Settings(int argc, char** argv) {
    if (argc < 6 || argc > 7) {
        throw ArgsEsception();
    }
    input = argv[1];
    output = argv[2];
    gradient = atoi(argv[3]);
    int dithering = atoi(argv[4]);
    bitRate = atoi(argv[5]);
    gamma = 0; //Default value
    if (argc == 7) {
        gamma = stod(argv[6]);
    }
    image = Image(input, output);

    if (gradient) {
        image.gradientGenerate();
    }
    if (dithering == 0) {
        image.noDithering(bitRate);
    } else if (dithering == 1) {
        image.OrderedDithering(bitRate);
    } else if (dithering == 2) {
        image.RandomDithering(bitRate);
    } else if (dithering == 3) {
        image.FloydSteinbergDithering(bitRate);
    } else if (dithering == 4) {
        image.JJNDithering(bitRate);
    } else if (dithering == 5) {
        image.SieraDithering(bitRate);
    } else if (dithering == 6) {
        image.AtkinsonDithering(bitRate);
    } else if (dithering == 7) {
        image.HalftoneDithering(bitRate);
    }


    image.write();
}
