#ifndef LAB8_CUBE_H
#define LAB8_CUBE_H

#include "cube_sweep.h"
#include <GL/glut.h>
#include <iostream>
#include "small_cube.h"
#include <fstream>

using namespace std;

class cube {
private:
    small_cube cubes[3][3][3];

    double size;
    int color[6];
    cube_sweep sweep; //Развёртка.

public:
    cube() = default;

    cube(cube const& a);

    cube(cube_sweep const& Cur, double _size);

    cube(std::ifstream& F, double size);

    //Рисуем.
    void draw();

    //Поворот на 90 градусов грани.
    void full_turn(int idx, int sign);

    //Крутит грань под номером idx на угол _angle (в градусах).
    void small_turn(int idx, int _angle);

    //Поворот всего кубика на 90 градусов.
    void swapper();

    //Переводим кубик-рубик в развёртку.
    cube_sweep solve();

    //Храним номер грани, которая в данный момент поварачивается, или -1 если ничего не поварачивается.
    int rotated = -1;

    //Храним угол поворота каждой грани.
    int angle[7];

private:
    unsigned int _correct_color[6] = {0xFFFFFF, 0xCD853F, 0x0000FF, 0xFF0000, 0x00FF00, 0xFFFF00};
    small_cube tmp[4][4];
    bool check[3][3][3]{true};
    //Перевод цветов в числа, для облегчения сборки.
    void switcher(std::vector<brink> &br, int a, int b, int c, int i, int j, int k);
};

#endif
