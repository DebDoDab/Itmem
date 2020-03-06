//
// Created by vadim on 6.03.20.
//

#include "Image.h"

Point::Point() {
    x = y = 0;
}

Point::Point(double x_, double y_) {
    x = x_;
    y = y_;
}

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

void Image::drawLine(Point begin, Point end, double thickness, int color, double gamma) {
    bool steep = abs(begin.x - end.x) < abs(begin.y - end.y);
    if (steep) {
        swap(begin.x, begin.y);
        swap(end.x, end.y);
    }
    if (begin.x > end.x) {
        swap(begin.x, end.x);
        swap(begin.y, end.y);
    }

    auto plot = [&] (int x, int y, double brightness) {
        if (steep) {
            swap(x, y);
        }
        if (x < 0 || x > width || y < 0 || y > height) {
            return;
        }
        pixels[y][x] = (1 - brightness) * (unsigned char)pixels[y][x] + color * brightness;
    };

    double gradient = (end.y - begin.y) / (end.x - begin.x);
    double y = begin.y + gradient * (round(begin.x) - begin.x);

    for (int plotX = round(begin.x); plotX <= round(end.x); plotX++, y += gradient) {
        for (int plotY = int(y - (thickness - 1) / 2.); plotY <= int(y - (thickness - 1) / 2. + thickness); plotY++) {
            plot(plotX, plotY, min(1., (thickness + 1.) / 2. - fabs(y - plotY)));
        }
    }
}
