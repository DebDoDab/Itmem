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
    // 27 частей
    vector<vector<vector<Small_Cube>>> a;
    // храним угол поворота каждой грани
    int rotate[6];
    // размер кубика-рубика
    double size;
    // цвета граней
    unsigned int color[6];
    // храним номер грани, которая в данный момент поварачивается, или -1 если ничего не поварачивается
    int current;

public:

    vector<int> currentSolve;

    vector<vector<vector<Small_Cube>>>& getCube() {
        return a;
    }

    CubeGL() {
        a.assign(3, vector<vector<Small_Cube>>(3, vector<Small_Cube>(3)));
    }

    CubeGL(double size, unsigned int *color) {
        a.assign(3, vector<vector<Small_Cube>>(3, vector<Small_Cube>(3)));
        clear(size, color);
    }

    int getcurrent() {
        return current;
    }

    void clear(double size, unsigned int *color) {
        memset(rotate, 0, sizeof(rotate));
        this->size = size;
        current = -1;

        for(int i = 0; i < 6; i++)
            this->color[i] = color[i];

        // верх
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                a[i][j][2].setColor(0, color[0]);

        // низ
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                a[i][j][0].setColor(1, color[1]);

        // спереди
        for(int k = 0; k < 3; k++)
            for(int j = 0; j < 3; j++)
                a[j][0][k].setColor(2, color[2]);

        // сзади
        for(int k = 0; k < 3; k++)
            for(int j = 0; j < 3; j++)
                a[j][2][k].setColor(3, color[3]);

        // слева
        for(int i = 0; i < 3; i++)
            for(int k = 0; k < 3; k++)
                a[0][k][i].setColor(4, color[4]);

        // справа
        for(int i = 0; i < 3; i++)
            for(int k = 0; k < 3; k++)
                a[2][k][i].setColor(5, color[5]);

        // устанавливаем размеры мелких деталей
        // это будет треть всего размера, умноженная на коэффициент немного меньший еденицы
        // (чтобы детали не были слишком плотно)
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                for(int k = 0; k < 3; k++)
                    a[i][j][k].setsize((size / 3.0) * 0.98);
    }

    void draw() {
        const double K = 0.65;
        // рисуем корпус - это просто куб черного цвета, размер которого равен K*size
        glPushMatrix();
        glColor3f(0, 0, 0);
        glTranslatef(((1.0 - K)/2)*size + K*size/2, ((1.0 - K)/2)*size + K*size/2, ((1.0 - K)/2)*size + K*size/2);
        glutSolidCube(size * K);
        glPopMatrix();

        // ok[i][j][k] показывает, находится ли в состоянии покоя деталь с координатами (i, j, k)
        memset(ok, true, sizeof(ok));
        if (current != -1) {
            glPushMatrix();
            int i, j, k;

            if (current == 0 || current == 1) {
                // 0 <= current <= 1 показывает, что сейчас крутится грань на плоскости X0Y
                // current = 0 - нижняя часть
                // current = 1 - верхняя часть
                k = (current & 1) * 2;
                // следовательно ok слоя  k  устанавливаем в false
                for(i = 0; i < 3; i++) {
                    for(j = 0; j < 3; j++) {
                        ok[i][j][k] = false;
                    }
                }

                // теперь нужно покрутить грань под номером current на угол rotate[current]
                // относительно центра этой грани
                // для этого сдвинемся к центру, покрутим, сдвинемся обратно
                glTranslated(size / 2, size / 2, 0);   // сдвигаемся к центру
                glRotatef(rotate[current], 0, 0, 1);   // крутим
                glTranslated(-size / 2, -size / 2, 0); // сдвигаемся обратно
                // рисуем
                for(i = 0; i < 3; i++) {
                    for(j = 0; j < 3; j++) {
                        a[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);
                    }
                }
            } else if (current == 2 || current == 3) {
                j = (current & 1) * 2;
                for(i = 0; i < 3; i++) {
                    for(k = 0; k < 3; k++) {
                        ok[i][j][k] = false;
                    }
                }

                glTranslated(size / 2, 0, size / 2);
                glRotatef(rotate[current], 0, 1, 0);
                glTranslated(-size / 2, 0, -size / 2);
                for(i = 0; i < 3; i++) {
                    for(k = 0; k < 3; k++) {
                        a[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);
                    }
                }
            } else if (current == 4 || current == 5) {
                i = (current & 1) * 2;
                for(j = 0; j < 3; j++) {
                    for(k = 0; k < 3; k++) {
                        ok[i][j][k] = false;
                    }
                }

                glTranslated(0, size / 2, size / 2);
                glRotatef(rotate[current], 1, 0, 0);
                glTranslated(0, -size / 2, -size / 2);
                for(j = 0; j < 3; j++) {
                    for(k = 0; k < 3; k++) {
                        a[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);
                    }
                }
            }
            glPopMatrix();
        }

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                for(int k = 0; k < 3; k++) {
                    if (ok[i][j][k]) {
                        // теперь рисуем те детали, которые не поварачивались выше,
                        // они отмечены ok[i][j][k] = true
                        a[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);
                    }
                }
            }
        }
    }

public:
    void rot90(int idx, int sign) {
        int i, j, k;
        // sign задаётся в зависимости он направления
        // sign = -1, sign = 1
        // если sign = -1, значит крутим 3 раза
        if (sign == -1) {
            sign = 3;
        }
        while(sign--) {
            if (idx == 0 || idx == 1) {
                // низ/верх
                k = (idx & 1) * 2;
                // копируем повёрнутую на 90 градусов верхнюю/нижнюю грань
                // в массив tmp, затем грани присваиваем tmp
                // и не забываем повернуть каждую деталь этой грани
                for(i = 0; i < 3; i++) {
                    for(j = 0; j < 3; j++) {
                        tmp[j][2 - i] = a[i][j][k];
                    }
                }
                for(i = 0; i < 3; i++) {
                    for(j = 0; j < 3; j++) {
                        tmp[i][j].rotateZ(), a[i][j][k] = tmp[i][j];
                    }
                }
            } else if (idx == 2 || idx == 3) {
                // лево/право
                j = (idx & 1) * 2;
                for(i = 0; i < 3; i++) {
                    for(k = 0; k < 3; k++) {
                        tmp[k][2 - i] = a[i][j][k];
                    }
                }
                for(i = 0; i < 3; i++) {
                    for(k = 0; k < 3; k++) {
                        tmp[i][k].rotateX(), a[i][j][k] = tmp[i][k];
                    }
                }
            } else if (idx == 4 || idx == 5) {
                // впереди/сзади
                i = (idx & 1) * 2;
                for(j = 0; j < 3; j++) {
                    for(k = 0; k < 3; k++) {
                        tmp[k][2 - j] = a[i][j][k];
                    }
                }
                for(j = 0; j < 3; j++) {
                    for(k = 0; k < 3; k++) {
                        tmp[j][k].rotateY(), a[i][j][k] = tmp[j][k];
                    }
                }
            }
        }
    }

    // крутит грань под номером idx на угол angle (в градусах)
    void Rotate(int idx, int angle) {
        // мы пытаемся покрутить грань с номером idx
        // значит нужно проверить что другая грань уже не крутится
        if (current == -1 || current == idx) {
            // обновляем поворот
            rotate[idx] += angle;
            cerr << rotate[idx] << endl;

            if (rotate[idx] % 90 != 0) {
                current = idx;
            } else {
                // если угол стал кратным 90, то поварачиваем на массиве
                if ((rotate[idx] < 0) ^ (current == 2 || current == 3)) {
                    rot90(idx, 1);
                } else {
                    rot90(idx, -1);
                }
                rotate[idx] = 0;
                current = -1;
            }
        }
    }
};


#endif