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

    auto plot = [&](int x, int y, double brightness) {
        if (steep) {
            swap(x, y);
        }
        if (x < 0 || x >= width || y < 0 || y >= height || brightness < 0) {
            return;
        }
        cout << endl << y << " " << x << endl;
        cout << double((unsigned char)pixels[y][x]) / maxValue << " " << brightness << endl;
        cout << (1. - brightness) * (unsigned char)pixels[y][x] / maxValue << " : " << brightness * color / 255. << endl;
        cout << (gamma - 1) * brightness + 1 << " : " << pow((1 - brightness) * (unsigned char)pixels[y][x] / maxValue + brightness * color / 255., (gamma - 1) * brightness + 1) * maxValue << endl;

        pixels[y][x] = pow((1. - brightness) * (unsigned char)pixels[y][x] / maxValue + brightness * color / 255., (gamma - 1) * brightness + 1) * maxValue;
    };

    double gradient = (end.y - begin.y) / (end.x - begin.x);
    double y;

    auto dist = [](int x, int y, int x1, int y1) {
        return sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
    };

    auto findY = [=](int x) {
        return begin.y + gradient * (x - begin.x);
    };

    for (int plotX = round(begin.x) - thickness / 2; plotX < round(begin.x); plotX++, y += gradient) {
        y = findY(plotX);
        Point point(round(begin.x), findY(round(begin.x)));
        for (int plotY = int(y - (thickness - 1) / 2.); plotY <= int(y - (thickness - 1) / 2. + thickness); plotY++) {
            plot(plotX, plotY, min(1., (thickness + 1.) / 2. - dist(plotX, plotY, point.x, point.y)));
        }
    }

    for (int plotX = round(begin.x); plotX <= round(end.x); plotX++, y += gradient) {
        y = findY(plotX);
        for (int plotY = int(y - (thickness - 1) / 2.); plotY <= int(y - (thickness - 1) / 2. + thickness); plotY++) {
            plot(plotX, plotY, min(1., (thickness + 1.) / 2. - fabs(y - plotY)));
        }
    }

    for (int plotX = round(end.x) + 1; plotX <= round(end.x) + thickness / 2; plotX++, y += gradient) {
        y = findY(plotX);
        Point point(round(end.x), findY(round(end.x)));
        for (int plotY = int(y - (thickness - 1) / 2.); plotY <= int(y - (thickness - 1) / 2. + thickness); plotY++) {
            plot(plotX, plotY, min(1., (thickness + 1.) / 2. - dist(plotX, plotY, point.x, point.y)));
        }
    }
}
