//
// Created by vadim on 1.06.20.
//

#include "cube.h"

Cube::Cube() {
    cube.assign(6, vector<vector<int>>(3, vector<int>(3, 0)));
    for (int i = 0; i < cube.size(); i++) {
        for (auto& side : cube[i]) {
            for (auto& row : side) {
                row = i;
            }
        }
    }
}

Cube::Cube(CubeGL& x) {
    cube.assign(6, vector<vector<int>>(3, vector<int>(3, 0)));
    vector<vector<vector<Small_Cube>>>& smallCubes = x.getCube();
    parse(smallCubes);
}

void Cube::setCube(CubeGL& x) {
    vector<vector<vector<Small_Cube>>>& smallCubes = x.getCube();
    parseBack(smallCubes);
}

void Cube::parse(vector<vector<vector<Small_Cube>>>& x) {
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

void Cube::parseBack(vector<vector<vector<Small_Cube>>>& x) {
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

vector<int> Cube::generateRandomState() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    vector<int> ans((rng() % 10) + 20);
    for (auto& x : ans) {
        x = rng() % 6;
    }
    return Ans;
}

vector<int> Cube::solve() {
    vector<int> ans = {};
    for (auto& x : Ans) {
        ans.push_back(x + 6);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

void Cube::write(const string& filename) {
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


void Cube::print() {
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

void Cube::read(const string& filename) {
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

void Cube::leftwise(int side) {
    swap(cube[side][0][0], cube[side][0][2]);
    swap(cube[side][2][2], cube[side][0][2]);
    swap(cube[side][2][0], cube[side][2][2]);

    swap(cube[side][0][1], cube[side][1][2]);
    swap(cube[side][1][2], cube[side][2][1]);
    swap(cube[side][2][1], cube[side][1][0]);
}

void Cube::rightwise(int side) {
    swap(cube[side][0][0], cube[side][2][0]);
    swap(cube[side][2][2], cube[side][2][0]);
    swap(cube[side][0][2], cube[side][2][2]);

    swap(cube[side][0][1], cube[side][1][0]);
    swap(cube[side][1][0], cube[side][2][1]);
    swap(cube[side][2][1], cube[side][1][2]);
}
