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

    switch (dithering) {
        case 0: image.noDithering(bitRate); break;
        case 1: image.OrderedDithering(bitRate); break;
        case 2: image.RandomDithering(bitRate); break;
        case 3: image.FloydSteinbergDithering(bitRate); break;
        case 4: image.JJNDithering(bitRate); break;
        case 5: image.SieraDithering(bitRate); break;
        case 6: image.AtkinsonDithering(bitRate); break;
        case 7: image.HalftoneDithering(bitRate); break;
    }
    ///TODO add dithering algorithm execution


    image.write();
}
