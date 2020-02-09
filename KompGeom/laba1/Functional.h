//
// Created by vadim on 9.02.20.
//

#include <bits/stdc++.h>

using namespace std;

#ifndef LABA1_FUNCTIONAL_H
#define LABA1_FUNCTIONAL_H

class Image {
private:
    string inputFile, outputFile;
    string header;
    int height{}, width{}, maxValue{};
    vector<vector<tuple<char, char, char>>> pixels;

public:

    Image(const string& input, const string& output);

    void inverseColors();

    void mirrorHorizontal();

    void mirrorVertical();

    void clockwizeTurn();

    void counterclockwizeTurn();

    void read();

    void write();
};

#endif //LABA1_FUNCTIONAL_H
