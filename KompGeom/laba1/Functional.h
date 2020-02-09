//
// Created by vadim on 9.02.20.
//

#include <bits/stdc++.h>

using namespace std;

#ifndef LABA1_FUNCTIONAL_H
#define LABA1_FUNCTIONAL_H

class Image {
public:
    virtual void inverseColors() = 0;

    virtual void mirrorHorizontal() = 0;

    virtual void mirrorVertical() = 0;

    virtual void clockwizeTurn() = 0;

    virtual void counterclockwizeTurn() = 0;

    virtual void read() = 0;

    virtual void write() = 0;
};

class ImageColored : public Image {
public:
    string inputFile, outputFile;
    string header;
    int height, width, maxValue;
    vector<vector<tuple<char, char, char>>> pixels;

public:
    ImageColored(const string& input, const string& output);

    void read() override;

    void write() override;

    void inverseColors() override;

    void mirrorVertical() override;

    void mirrorHorizontal() override;

    void clockwizeTurn() override;

    void counterclockwizeTurn() override;
};

class ImageGrayscale : public Image {
public:
    string inputFile, outputFile;
    string header;
    int height, width, maxValue;
    vector<vector<char>> pixels;

public:
    ImageGrayscale(const string& input, const string& output);

    void read() override ;

    void write() override;

    void inverseColors() override;

    void mirrorHorizontal() override;

    void mirrorVertical() override;

    void clockwizeTurn() override;

    void counterclockwizeTurn() override;
};

#endif //LABA1_FUNCTIONAL_H
