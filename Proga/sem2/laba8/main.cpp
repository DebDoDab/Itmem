#include "CubeGL.h"
#include "cube.h"
#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "cube_sweep.h"

using namespace std;

#define CUBE_SIZE 13
#define TIMER 30
// обозначаем цвета:
//                    (верх,      низ,   впереди,   сзади,    лево,      право)
unsigned int c[6] = {0xFFFFFF, 0xFFFF00, 0x0000FF, 0x00FF00, 0xFF0000, 	0xCD853F};

// координаты источника света
GLfloat lightPos[] = {0, 100, 200, 0};
// проекции угла поворота на оси
int xRot = 24, yRot = 34, zRot = 0;
// отдаление
double translateZ = -35.0;
// кубик-рубик
CubeGL cube;
Cube algoCube;
// флаг того, крутится куб сам, или нет (будет переключаться правой кнопкой мыши)
// 0 - nothing, 1 - solving, 2 - random
int solving = 0;

void display() {
    glPushMatrix();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glTranslatef(0, 0, translateZ);
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    glTranslatef(CUBE_SIZE / -2.0, CUBE_SIZE / -2.0, CUBE_SIZE / -2.0);
    cube.draw();
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat fAspect = (GLfloat)w/(GLfloat)h;
    GLfloat zNear = 1;
    GLfloat zFar = 1000.0;
    GLfloat aspect = fAspect;
    GLfloat fH = tan( float(60 / 360.0f * 3.14159f) ) * zNear;
    GLfloat fW = fH * aspect;
    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    // инициализируем случайные числа
    srand(time(0));

    // освещение
    float mat_specular[] = {0.3, 0.3, 0.3, 0};
    float diffuseLight[] = {0.2, 0.2, 0.2, 1};
    float ambientLight[] = {0.9, 0.9, 0.9, 1.0};
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMateriali(GL_FRONT, GL_SHININESS, 128);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    // инициализируем куб
    cube.clear(CUBE_SIZE, c);
}

void specialKeys(int key, int, int) {
    // клавиши влево/вправо вращают по Y
    // клавиши вверх/вниз вращают по X
    // F1 - возвращает в начальное положение
    if (key == GLUT_KEY_DOWN) {
        xRot += 3;
        if (xRot >= 360) {
            xRot -= 360;
        }
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_UP) {
        xRot -= 3;
        if (xRot < 0) {
            xRot += 360;
        }
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_RIGHT) {
        yRot += 3;
        if (yRot >= 360) {
            yRot -= 360;
        }
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_LEFT) {
        yRot -= 3;
        if (yRot < 0) {
            yRot += 360;
        }
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_HOME) {
        translateZ += 5;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_END) {
        translateZ -= 5;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_F1) {
        cube.clear(CUBE_SIZE, c);
        solving = 0;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_PAGE_UP) {
        algoCube = cube;
        algoCube.write();
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_PAGE_DOWN) {
        algoCube.read();
        algoCube.setCube(cube);
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_F11) {
        if (solving != 1) {
            algoCube = cube;
            cube.currentSolve = algoCube.solve();
            solving = 1;
        } else {
            solving = 0;
        }
    }

    if (key == GLUT_KEY_F12) {
        if (solving != 2) {
            algoCube = cube;
            cube.currentSolve = algoCube.generateRandomState();
            solving = 2;
        } else {
            solving = 0;
        }
    }

    if (key == GLUT_KEY_F3) {
        algoCube = cube;
        cube_sweep x(algoCube);
        x.print();
//        auto ans = x.solver();
//        for (auto& a : ans) {
//            cerr << a << " ";
//        }
//        cerr << endl;
    }
}

void keys(unsigned char key, int, int) {
    // если нажали клавишу от 0 до 5 - начинаем поворот на 3 градуса
    if (cube.getcurrent() == -1 && key >= '0' && key < '6') {
        cube.Rotate(key - '0', 3);
        display();
    }
}

void timer(int) {
    glutTimerFunc(TIMER, timer, 0);
    if (solving != 0) {
        if (cube.getcurrent() == -1) {
            if (cube.currentSolve.empty()) {
                solving = 0;
            } else {
//                keys(cube.currentSolve.back() + '0', 0, 0);
                cube.Rotate(cube.currentSolve.back(), 9);
                cube.currentSolve.pop_back();
            }
        } else {
            cube.Rotate(cube.getcurrent() + (cube.getclockwise() == -1 ? 6 : 0), 9);
        }
    } else {
        if (cube.getcurrent() != -1) {
            cube.Rotate(cube.getcurrent() + (cube.getclockwise() == -1 ? 6 : 0), 3);
        }
    }
    display();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 700);
    glutInitWindowPosition(1, 1);
    glutCreateWindow("Cube");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keys);
    glutTimerFunc(TIMER, timer, 0);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}