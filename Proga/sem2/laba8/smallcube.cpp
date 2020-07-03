//
// Created by vadim on 1.06.20.
//

#include "smallcube.h"

Small_Cube::Small_Cube() {
    color.assign(6, 0);
    size = 0.0;
}

void Small_Cube::setsize(double size_) {
    size = size_;
}

void Small_Cube::rotateZ() {
    swap(color[5], color[3]);
    swap(color[3], color[4]);
    swap(color[4], color[2]);
}

void Small_Cube::rotateY() {
    swap(color[2], color[1]);
    swap(color[1], color[3]);
    swap(color[3], color[0]);
}

void Small_Cube::rotateX() {
    swap(color[0], color[4]);
    swap(color[4], color[1]);
    swap(color[1], color[5]);
}

void Small_Cube::setColor(int i, int color) {
    this->color[i] = color;
}

int Small_Cube::getColor(int i) {
    return color[i];
}

unsigned char* Small_Cube::at(int i) {
    _color[0] = color[i] >> 16;
    _color[1] = color[i] >> 8;
    _color[2] = color[i];
    return _color;
}

void Small_Cube::draw() {
    glPushMatrix();
    glBegin(GL_QUADS);

    // up
    glColor3ubv(at(0));
    glNormal3f(0, 0, 1);
    glVertex3f(size, size, size);
    glVertex3f(0, size, size);
    glVertex3f(0, 0, size);
    glVertex3f(size, 0, size);

    // down
    glColor3ubv(at(1));
    glNormal3f(0, 0, -1);
    glVertex3f(size, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, size, 0);
    glVertex3f(size, size, 0);

    // front
    glColor3ubv(at(2));
    glNormal3f(0, -1, 0);
    glVertex3f(size, 0, size);
    glVertex3f(0, 0, size);
    glVertex3f(0, 0, 0);
    glVertex3f(size, 0, 0);

    // back
    glColor3ubv(at(3));
    glNormal3f(0, 1, 0);
    glVertex3f(size, size, 0);
    glVertex3f(0, size, 0);
    glVertex3f(0, size, size);
    glVertex3f(size, size, size);

    // left
    glColor3ubv(at(4));
    glNormal3f(-1, 0, 0);
    glVertex3f(0, size, size);
    glVertex3f(0, size, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, size);

    // right
    glColor3ubv(at(5));
    glNormal3f(1, 0, 0);
    glVertex3f(size, size, 0);
    glVertex3f(size, size, size);
    glVertex3f(size, 0, size);
    glVertex3f(size, 0, 0);

    glEnd();
    glPopMatrix();
}

void Small_Cube::draw(double x, double y, double z) {
    glPushMatrix();
    glTranslated(x, y, z);
    draw();
    glPopMatrix();
}

