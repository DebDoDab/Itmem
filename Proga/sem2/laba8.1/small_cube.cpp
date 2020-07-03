#include "small_cube.h"

small_cube::small_cube()
{
    size = 0.0;
    //По умолчанию черный цвет.
    for (unsigned int & i : _color)
        i = 0;
}

void small_cube::XOY()
{
    unsigned int tmp = _color[5];
    _color[5] = _color[3];
    _color[3] = _color[0];
    _color[0] = _color[1];
    _color[1] = tmp;
}

void small_cube::XOZ()
{
    unsigned int tmp = _color[0];
    _color[0] = _color[2];
    _color[2] = _color[5];
    _color[5] = _color[4];
    _color[4] = tmp;
}

void small_cube::YOZ()
{
    unsigned int tmp = _color[1];
    _color[1] = _color[4];
    _color[4] = _color[3];
    _color[3] = _color[2];
    _color[2] = tmp;
}

unsigned char *small_cube::RGB_(unsigned int a)
{
    _rgb[0] = _color[a] >> 16;
    _rgb[1] = _color[a] >> 8;
    _rgb[2] = _color[a];
    return _rgb;
}

void small_cube::draw(double x, double y, double z)
{
    glPushMatrix(); //Сохранение текущих координат.
    glTranslated(x, y, z); //Смещение относительно центра, где рисуем кубик.
    glBegin(GL_QUADS); //Неделимая часть того, из чего состоит кубик(квадраты).
    glColor3ubv(RGB_(4)); //Красим стороны(матрицы) куба.
    glNormal3f(0, 0, 1); //Задаём нормаль(сторона наложения цвета).
    glVertex3f(size, size, size); //Первая вершина.
    glVertex3f(0, size, size); //Вторая вершина.
    glVertex3f(0, 0, size); //Третья вершина.
    glVertex3f(size, 0, size); //Четвертая вершина.
    glColor3ubv(RGB_(3));
    glNormal3f(-1, 0, 0);
    glVertex3f(0, size, size);
    glVertex3f(0, size, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, size);
    glColor3ubv(RGB_(0));
    glNormal3f(0, -1, 0);
    glVertex3f(size, 0, size);
    glVertex3f(0, 0, size);
    glVertex3f(0, 0, 0);
    glVertex3f(size, 0, 0);
    glColor3ubv(RGB_(1));
    glNormal3f(1, 0, 0);
    glVertex3f(size, size, 0);
    glVertex3f(size, size, size);
    glVertex3f(size, 0, size);
    glVertex3f(size, 0, 0);
    glColor3ubv(RGB_(5));
    glNormal3f(0, 1, 0);
    glVertex3f(size, size, 0);
    glVertex3f(0, size, 0);
    glVertex3f(0, size, size);
    glVertex3f(size, size, size);
    glColor3ubv(RGB_(2));
    glNormal3f(0, 0, -1);
    glVertex3f(size, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, size, 0);
    glVertex3f(size, size, 0);
    glEnd();
    glPopMatrix(); //Восстанавливаем координаты центра.
}

void small_cube::draw()
{
    draw(0.0, 0.0, 0.0);
}

void small_cube::set(int ind, unsigned int color)
{
    _color[ind] = color;
}


