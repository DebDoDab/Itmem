#ifndef _SMALL_CUBE_H
#define _SMALL_CUBE_H

#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

// класс частей кубика-рубика, большой кубик будет состоять из 27 маленьких.
class Small_Cube {
private:
    // шесть граней куба - шесть цветов
    vector<unsigned int> color; // (верх, низ, впереди, сзади, лево, право)
    // размер ребра
    double size;
    unsigned char _color[3];

public:
    Small_Cube() {
        // по умолчанию черный цвет
        color.assign(6, 0);
        size = 0.0;
    }

    void setsize(double size_) {
        size = size_;
    }

    // поворот на плоскости X0Y
    void rotateZ() {
        swap(color[5], color[3]);
        swap(color[3], color[4]);
        swap(color[4], color[2]);
    }

    // поворот на плоскости X0Z
    void rotateY() {
        swap(color[2], color[1]);
        swap(color[1], color[3]);
        swap(color[3], color[0]);
    }

    // поворот на плоскости Y0Z
    void rotateX() {
        swap(color[0], color[4]);
        swap(color[4], color[1]);
        swap(color[1], color[5]);
    }

    void setColor(int i, int color) {
        this->color[i] = color;
//        cerr << i << " " << this->color[i] << "\n";
    }

    int getColor(int i) {
        return color[i];
    }

    unsigned char* at(int i) {
        // разбиваем color[i] на 3 составляющих
        // например для 0xFF0000 RGB(FF, 0, 00) - красный цвет;
        _color[0] = color[i] >> 16;
        _color[1] = color[i] >>  8;
        _color[2] = color[i]      ;
        return _color;
    }

    // отрисовка куба:
    // устанавливаем цвет и нормали
    void draw() {
        glPushMatrix();
        glBegin(GL_QUADS);

        // верх
        glColor3ubv(at(0));
        glNormal3f(0, 0, 1);
        glVertex3f(size, size, size);
        glVertex3f(0, size, size);
        glVertex3f(0, 0, size);
        glVertex3f(size, 0, size);

        // низ
        glColor3ubv(at(1));
        glNormal3f(0, 0, -1);
        glVertex3f(size, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, size, 0);
        glVertex3f(size, size, 0);

        // спереди
        glColor3ubv(at(2));
        glNormal3f(0, -1, 0);
        glVertex3f(size, 0, size);
        glVertex3f(0, 0, size);
        glVertex3f(0, 0, 0);
        glVertex3f(size, 0, 0);

        // сзади
        glColor3ubv(at(3));
        glNormal3f(0, 1, 0);
        glVertex3f(size, size, 0);
        glVertex3f(0, size, 0);
        glVertex3f(0, size, size);
        glVertex3f(size, size, size);

        // слева
        glColor3ubv(at(4));
        glNormal3f(-1, 0, 0);
        glVertex3f(0, size, size);
        glVertex3f(0, size, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, size);

        // справа
        glColor3ubv(at(5));
        glNormal3f(1, 0, 0);
        glVertex3f(size, size, 0);
        glVertex3f(size, size, size);
        glVertex3f(size, 0, size);
        glVertex3f(size, 0, 0);

        glEnd();
        glPopMatrix();
    }

    // отрисовка куба со смещением (x, y, z)
    void draw(double x, double y, double z) {
        glPushMatrix();
        glTranslated(x, y, z);
        draw();
        glPopMatrix();
    }
};


#endif