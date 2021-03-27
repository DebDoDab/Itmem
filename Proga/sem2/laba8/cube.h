//
// Created by vadim on 1.06.20.
//

#include <bits/stdc++.h>
#include "CubeGL.h"
#include "smallcube.h"
#include <chrono>
using namespace std;

#ifndef LABA8_CUBE_H
#define LABA8_CUBE_H


class Cube {
private:
    //                          WHITE   UP            BLUE   RIGHT         RED     FRONT         GREEN  LEFT          YELLOW  DOWN         BROWN  BACK
    map<int, int> colors = {{0xFFFFFF, 0}, {0x0000FF, 3}, {0xFF0000, 2}, {0x00FF00, 1}, {0xFFFF00, 4}, {0xCD853F, 5}};

    map<int, int> backColors = {{0, 0xFFFFFF}, {3, 0x0000FF}, {2, 0xFF0000}, {1, 0x00FF00}, {4, 0xFFFF00}, {5, 0xCD853F}};
public:
    vector<vector<vector<int>>> cube;


    Cube();

    Cube(CubeGL&);

    void setCube(CubeGL&);

    void parse(vector<vector<vector<Small_Cube>>>&);

    void parseBack(vector<vector<vector<Small_Cube>>>&);

    void leftwise(int);

    void rightwise(int);

    vector<int> Ans = {2, 0, 2, 4, 5, 0, 5, 1, 2, 2, 1, 3, 2, 3, 4, 2, 4, 4, 3, 2, 2};
    vector<int> generateRandomState();

    vector<int> solve();

    void write(const string& filename = "../state.cube");


    void print();

    void read(const string& filename = "../state.cube");


};

#endif //LABA8_CUBE_H