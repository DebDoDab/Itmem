//
// Created by vadim on 6.03.20.
//

#include "Image.h"

Image::Image() {
    inputFile = outputFile = "";
    height = width = maxValue = 0;
}

Image::Image(const string &input, const string &output) {
    inputFile = input;
    outputFile = output;
    height = width = maxValue = 0;
    this->read();
}

void Image::read() {
    ifstream fin(inputFile);
    fin >> header; ///P5
    if (header != "P5") {
        throw WrongFormatException();
    }
    fin >> width >> height;
    fin >> maxValue;
    fin.get();

    pixels.assign(height, vector<char>(width, 0));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (cin.eof()) {
                throw WrongSizeException();
            }
            fin.read(&pixels[i][j], 1);
        }
    }

    fin.get();
    if (!fin.eof()) {
        throw WrongSizeException();
    }
}

void Image::write() {
    ofstream fout(outputFile);
    fout << header << "\n" << width << " " << height << "\n" << maxValue << "\n";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fout.write(&pixels[i][j], 1);
        }
    }
}


void Image::gradientGenerate() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            pixels[i][j] = tosrgb(double(i) / double(height) * 255);
        }
    }
}

void Image::noDithering(int bitRate) {
    int maxValue = (1 << bitRate) - 1;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double value = tolinear(pixels[i][j]) / 255.;

            value = max(min(value, 1.), 0.);

            int newPixel = round(value * maxValue) / maxValue * 255;
            pixels[i][j] = tosrgb(newPixel);
        }
    }
}

const double Ordered[8][8] = {
        {0.0 / 64.0, 48.0 / 64.0, 12.0 / 64.0, 60.0 / 64.0, 3.0 / 64.0, 51.0 / 64.0, 15.0 / 64.0, 63.0 / 64.0},
        {32.0 / 64.0, 16.0 / 64.0, 44.0 / 64.0, 28.0 / 64.0, 35.0 / 64.0, 19.0 / 64.0, 47.0 / 64.0, 31.0 / 64.0},
        {8.0 / 64.0, 56.0 / 64.0, 4.0 / 64.0, 52.0 / 64.0, 11.0 / 64.0, 59.0 / 64.0, 7.0 / 64.0, 55.0 / 64.0},
        {40.0 / 64.0, 24.0 / 64.0, 36.0 / 64.0, 20.0 / 64.0, 43.0 / 64.0, 27.0 / 64.0, 39.0 / 64.0, 23.0 / 64.0},
        {2.0 / 64.0, 50.0 / 64.0, 14.0 / 64.0, 62.0 / 64.0, 1.0 / 64.0, 49.0 / 64.0, 13.0 / 64.0, 61.0 / 64.0},
        {34.0 / 64.0, 18.0 / 64.0, 46.0 / 64.0, 30.0 / 64.0, 33.0 / 64.0, 17.0 / 64.0, 45.0 / 64.0, 29.0 / 64.0},
        {10.0 / 64.0, 58.0 / 64.0, 6.0 / 64.0, 54.0 / 64.0, 9.0 / 64.0, 57.0 / 64.0, 5.0 / 64.0, 53.0 / 64.0},
        {42.0 / 64.0, 26.0 / 64.0, 38.0 / 64.0, 22.0 / 64.0, 41.0 / 64.0, 25.0 / 64.0, 37.0 / 64.0, 21.0 / 64.0}
};

void Image::OrderedDithering(int bitRate) {
    int maxValue = (1 << bitRate) - 1;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double value = tolinear(pixels[i][j]) / 255.;
            value += (Ordered[i % 8][j % 8] - 0.5) / bitRate;

            value = max(min(value, 1.), 0.);

            int newPixel = round(value * maxValue) / maxValue * 255;
            pixels[i][j] = tosrgb(newPixel);
        }
    }
}

void Image::RandomDithering(int bitRate) {
    int maxValue = (1 << bitRate) - 1;

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_real_distribution<> dis(0., 0.25);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double pixel = tolinear(pixels[i][j]) / 255.;
            double noise = dis(rng);
            double value = pixel + noise / bitRate;

            value = max(min(value, 1.), 0.);

            int newPixel = round(value * maxValue) / maxValue * 255;
            pixels[i][j] = tosrgb(newPixel);
        }
    }
}

void Image::FloydSteinbergDithering(int bitRate) {
    int maxValue = (1 << bitRate) - 1;

    vector<vector<double>> errors(height, vector<double>(width, 0));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double value = tolinear(pixels[i][j]) / 255.;
            value += errors[i][j] / 255.;
            value = max(min(value, 1.), 0.);

            double newPixel = round(value * maxValue) / maxValue * 255;

            double error = tolinear(pixels[i][j]) + errors[i][j] - newPixel;

            pixels[i][j] = tosrgb(newPixel);

            if (j + 1 < width)
                errors[i][j + 1] += error * 7.0 / 16.0;
            if (i + 1 < height && j + 1 < width)
                errors[i + 1][j + 1] += error * 1.0 / 16.0;
            if (i + 1 < height)
                errors[i + 1][j] += error * 5.0 / 16.0;
            if (i + 1 < height && j - 1 >= 0)
                errors[i + 1][j - 1] += error * 3.0 / 16.0;
        }
    }
}

const double JJN[3][5] = {
        {0, 0, 0, 7.0 / 48.0, 5.0 / 48.0},
        {3.0 / 48.0, 5.0 / 48.0, 7.0 / 48.0, 5.0 / 48.0, 3.0 / 48.0},
        {1.0 / 48.0, 3.0 / 48.0, 5.0 / 48.0, 3.0 / 48.0, 1.0 / 48.0}
};

void Image::JJNDithering(int bitRate) {
    int maxValue = (1 << bitRate) - 1;

    vector<vector<double>> errors(height, vector<double>(width));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double value = tolinear(pixels[i][j]) / 255.;
            value += errors[i][j] / 255.0;
            value = max(min(value, 1.), 0.);

            double newPixel = round(value * maxValue) / maxValue * 255.;

            double error = tolinear(pixels[i][j]) + errors[i][j] - newPixel;

            pixels[i][j] = tosrgb(newPixel);

            for (int ie = 0; ie < 3; ie++) {
                for (int je = 0; je < 5; je++) {
                    if (i + ie >= height || j + (je - 2) >= width || j + (je - 2) < 0)
                        break;
                    if (ie == 0 && je <= 2)
                        break;

                    errors[i + ie][j + (je - 2)] += error * JJN[ie][je];
                }
            }
        }
    }
}

const double Sierra3[3][5] = {
        {0, 0, 0, 5.0 / 32.0, 3.0 / 32.0},
        {2.0 / 32.0, 4.0/ 32.0, 5.0 / 32.0, 4.0 / 32.0, 2.0 / 32.0},
        {0, 2.0 / 32.0, 3.0 / 32.0, 2.0 / 32.0, 0}
};

void Image::SieraDithering(int bitRate) {
    int maxValue = (1 << bitRate) - 1;

    vector<vector<double>> errors(height, vector<double>(width));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double value = tolinear(pixels[i][j]) / 255.;
            value += errors[i][j] / 255.0;
            value = max(min(value, 1.), 0.);

            double newPixel = round(value * maxValue) / maxValue * 255.;

            double error = tolinear(pixels[i][j]) + errors[i][j] - newPixel;

            pixels[i][j] = tosrgb(newPixel);

            for (int ie = 0; ie < 3; ie++) {
                for (int je = 0; je < 5; je++) {
                    if (i + ie >= height || j + (je - 2) >= width || j + (je - 2) < 0)
                        break;
                    if (ie == 0 && je <= 2)
                        break;

                    errors[i + ie][j + (je - 2)] += error * Sierra3[ie][je];
                }
            }
        }
    }
}

const int Atkinson[3][5] = {
        {0, 0, 0, 1, 1},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0}
};

void Image::AtkinsonDithering(int bitRate) {
    int maxValue = (1 << bitRate) - 1;

    vector<vector<double>> errors(height, vector<double>(width));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double value = tolinear(pixels[i][j]) / 255.;
            value += errors[i][j] / 255.0;
            value = max(min(value, 1.), 0.);

            double newPixel = round(value * maxValue) / maxValue * 255.;

            double error = tolinear(pixels[i][j]) + errors[i][j] - newPixel;

            pixels[i][j] = tosrgb(newPixel);

            for (int ie = 0; ie < 3; ie++) {
                for (int je = 0; je < 5; je++) {
                    if (i + ie >= height || j + (je - 2) >= width || j + (je - 2) < 0)
                        break;
                    if (ie == 0 && je <= 2)
                        break;

                    errors[i + ie][j + (je - 2)] += error * Atkinson[ie][je] / 8.0;
                }
            }
        }
    }
}

const double Halftone[4][4] = {
        {13.0 / 16.0, 11.0 / 16.0, 4.0 / 16.0, 8.0 / 16.0},
        {6.0 / 16.0, 0, 3.0 / 16.0, 15.0 / 16.0},
        {14.0 / 16.0, 1.0 / 16.0, 2.0 / 16.0, 7.0 / 16.0},
        {9.0 / 16.0, 5.0 / 16.0, 10.0 / 16.0, 12.0 / 16.0},
};

void Image::HalftoneDithering(int bitRate) {
    int maxValue = (1 << bitRate) - 1;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double value = tolinear(pixels[i][j]) / 255.;
            value += (Halftone[i % 4][j % 4] - 0.75) / bitRate;
            value = max(min(value, 1.), 0.);

            double newPixel = round(value * maxValue) / maxValue * 255;

            pixels[i][j] = tosrgb(newPixel);
        }
    }
}

unsigned char Image::tolinear(unsigned char color) {
    double colorSRGB = color / 255.0;
    double colorLinear = (colorSRGB <= 0.04045 ? colorSRGB / 12.92 : pow((colorSRGB + 0.055) / 1.055, 2.4));
    return colorLinear * 255;
}

unsigned char Image::tosrgb(unsigned char color) {
    double colorLinear = color / 255.0;
    double colorSRGB = (colorLinear <= 0.0031308 ? 12.92 * colorLinear : 1.055 * pow(colorLinear, 1 / 2.4) - 0.055);
    return colorSRGB * 255;
}
