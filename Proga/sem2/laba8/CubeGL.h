#ifndef _CUBE_H
#define _CUBE_H

#include "smallcube.h"
#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

class CubeGL {
private:
    bool ok[3][3][3];
    Small_Cube tmp[3][3];
    vector<vector<vector<Small_Cube>>> a;
    int rotate[6];
    double size;
    unsigned int color[6];
    int current;
    int clockwise = 1;

public:

    vector<int> currentSolve;

    vector<vector<vector<Small_Cube>>>& getCube();

    CubeGL();

    CubeGL(double, unsigned int*);

    int getcurrent();

    int getclockwise();

    void clear(double, unsigned int*);

    void draw();

public:
    void rot90(int, int);

    // крутит грань под номером idx на угол angle (в градусах)
    void Rotate(int, int);
};


#endif