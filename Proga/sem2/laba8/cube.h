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

    vector<vector<vector<int>>> cube;
    //                          WHITE   UP            BLUE   RIGHT         RED     FRONT         GREEN  LEFT          YELLOW  DOWN         BROWN  BACK
    map<int, int> colors = {{0xFFFFFF, 0}, {0x0000FF, 3}, {0xFF0000, 2}, {0x00FF00, 1}, {0xFFFF00, 4}, {0xCD853F, 5}};
    map<int, int> backColors = {{0, 0xFFFFFF}, {3, 0x0000FF}, {2, 0xFF0000}, {1, 0x00FF00}, {4, 0xFFFF00}, {5, 0xCD853F}};

public:

    Cube() {
        cube.assign(6, vector<vector<int>>(3, vector<int>(3, 0)));
        for (int i = 0; i < cube.size(); i++) {
            for (auto& side : cube[i]) {
                for (auto& row : side) {
                    row = i;
                }
            }
        }
    }

    Cube(CubeGL& x) {
        cube.assign(6, vector<vector<int>>(3, vector<int>(3, 0)));
        vector<vector<vector<Small_Cube>>>& smallCubes = x.getCube();
        parse(smallCubes);
    }

    void setCube(CubeGL& x) {
        vector<vector<vector<Small_Cube>>>& smallCubes = x.getCube();
        parseBack(smallCubes);
    }

    void parse(vector<vector<vector<Small_Cube>>>& x) {
        //up
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
//                x[i][j][2].setColor(0, 0);
                cube[0][i][j] = x[2 - i][2 - j][2].getColor(0);
            }
        }

        //down
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
//                x[2 - i][j][0].setColor(1, 0);
                cube[4][i][j] = x[i][2 - j][0].getColor(1);
            }
        }

        //front
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
//                x[2][i][2 - j].setColor(5, 0);
                cube[5][j][i] = x[2][2 - i][j].getColor(5);
            }
        }

        //back
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
//                x[0][i][j].setColor(4, 0);
                cube[2][j][i] = x[0][2 - i][2 - j].getColor(4);
            }
        }

        //right
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
//                x[2 - i][2][2 - j].setColor(3, 0);
                cube[1][j][i] = x[2 - i][2][2 - j].getColor(3);
            }
        }

        //left
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
//                x[i][0][2 - j].setColor(2, 0);
                cube[3][j][i] = x[i][0][2 - j].getColor(2);
            }
        }

        for (int side = 0; side < 6; side++) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    cube[side][i][j] = colors[cube[side][i][j]];
                }
            }
        }
    }

    void parseBack(vector<vector<vector<Small_Cube>>>& x) {
        //up
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                x[2 - i][2 - j][2].setColor(0, backColors[cube[0][i][j]]);
            }
        }

        //down
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                 x[i][2 - j][0].setColor(1, backColors[cube[4][i][j]]);
            }
        }

        //front
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
//                x[2][i][2 - j].setColor(5, 0);
                x[2][2 - i][j].setColor(5, backColors[cube[5][j][i]]);
            }
        }

        //back
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
//                x[0][i][j].setColor(4, 0);
                x[0][2 - i][2 - j].setColor(4, backColors[cube[2][j][i]]);
            }
        }

        //right
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
//                x[2 - i][2][2 - j].setColor(3, 0);
                x[2 - i][2][2 - j].setColor(3, backColors[cube[1][j][i]]);
            }
        }

        //left
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
//                x[i][0][2 - j].setColor(2, 0);
                x[i][0][2 - j].setColor(2, backColors[cube[3][j][i]]);
            }
        }
    }

    vector<int> generateRandomState() {
        mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        vector<int> ans((rng() % 10) + 20);
        for (auto& x : ans) {
            x = rng() % 6;
        }
        return ans;
    }

    vector<int> solve() {
        return {2, 2, 2, 1};
    }

    void write(const string& filename = "../state.cube") {
        ofstream fout(filename);
        for (int side = 0; side < 1; side++) {
            for (int row = 0; row < 3; row++) {
                fout << "      " << cube[side][row][0] << " " << cube[side][row][1] << " " << cube[side][row][2] << " " << "       \n";
            }
        }
        for (int row = 0; row < 3; row++) {
            for (int side = 1; side < 4; side++) {
                fout << cube[side][row][0] << " " << cube[side][row][1] << " " << cube[side][row][2] << " ";
            }
            fout << "\n";
        }
        for (int side = 4; side < 6; side++) {
            for (int row = 0; row < 3; row++) {
                fout << "      " << cube[side][row][0] << " " << cube[side][row][1] << " " << cube[side][row][2] << " " << "       \n";
            }
        }
        fout.close();
        cerr << "Successfully writed.\n";
    }


    void print() {
        for (int side = 0; side < 1; side++) {
            for (int row = 0; row < 3; row++) {
                cout << "      " << cube[side][row][0] << " " << cube[side][row][1] << " " << cube[side][row][2] << " " << "       \n";
            }
        }
        for (int row = 0; row < 3; row++) {
            for (int side = 1; side < 4; side++) {
                cout << cube[side][row][0] << " " << cube[side][row][1] << " " << cube[side][row][2] << " ";
            }
            cout << "\n";
        }
        for (int side = 4; side < 6; side++) {
            for (int row = 0; row < 3; row++) {
                cout << "      " << cube[side][row][0] << " " << cube[side][row][1] << " " << cube[side][row][2] << " " << "       \n";
            }
        }
    }

    void read(string filename = "../state.cube") {
        ifstream fin(filename);
        for (int side = 0; side < 1; side++) {
            for (int row = 0; row < 3; row++) {
                for (int cell = 0; cell < 3; cell++) {
                    int x;
                    fin >> x;
                    cube[side][row][cell] = x;
                }
            }
        }
        for (int row = 0; row < 3; row++) {
            for (int side = 1; side < 4; side++) {
                for (int cell = 0; cell < 3; cell++) {
                    int x;
                    fin >> x;
                    cube[side][row][cell] = x;
                }
            }
        }
        for (int side = 4; side < 6; side++) {
            for (int row = 0; row < 3; row++) {
                for (int cell = 0; cell < 3; cell++) {
                    int x;
                    fin >> x;
                    cube[side][row][cell] = x;
                }
            }
        }
        cerr << "Successfully readed.\n";
    }


};

#endif //LABA8_CUBE_H