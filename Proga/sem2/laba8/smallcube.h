#ifndef _SMALL_CUBE_H
#define _SMALL_CUBE_H

#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

class Small_Cube {
private:
    vector<unsigned int> color; // U, D, F, B, L, R
    double size;
    unsigned char _color[3];

public:
    Small_Cube();

    void setsize(double);

    void rotateZ();

    void rotateY();

    void rotateX();

    void setColor(int, int);

    int getColor(int);

    unsigned char* at(int);

    void draw();

    void draw(double, double, double);
};


#endif