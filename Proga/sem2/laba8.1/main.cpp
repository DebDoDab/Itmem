#include <ctime>
#include <cstdlib>
#include <fstream>
#include "cube.h"

//Размер.
#define CUBE_SIZE 13
//Как часто таймер обновляется.
#define TIMER 10

//Позиция света относительно центра.
GLfloat lightPos[] = {0, 100, 200, 0};
//Проекции угла поворота на оси.
int xRot = 24, yRot = 34, zRot = 0;
//Отдаление.
double translateZ = -100.0;

std::vector<char> solution;

//Создаём куб.
cube cube1;
//Флаг того, крутится куб сам, или нет (будет переключаться правой кнопкой мыши).
int timerOn = 0;
int it = 0;
int tmpx = 0;
int tmpy = 0;
int grad = 10;

//Отображение.
void display()
{
    glPushMatrix(); //Сохранить текущие координаты(изменить текущие координаты).
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos); //Источник света.
    glTranslatef(0, 0, translateZ); //В глубь.
    glRotatef(xRot, 1, 0, 0); //Вращение по оси X.
    glRotatef(yRot, 0, 1, 0); //Вращение по оси Y.
    glTranslatef(CUBE_SIZE / -2.0, CUBE_SIZE / -2.0, CUBE_SIZE / -2.0); //Имитирование вращения камеры.
    cube1.draw();
    glPopMatrix();
    glutSwapBuffers(); //Обменивает буфера, отображая окно целиком после того, как оно уже сформировано.
}

//Меняем размеры окна.
void reshape(int w, int h)
{
    glMatrixMode(GL_PROJECTION); //Говорит о том, что команды относятся к проекту.
    glLoadIdentity(); // Считывает текущую матрицу.
    //Настройка перспективы просмотра.
    GLfloat fAspect = (GLfloat)w/(GLfloat)h;
    GLfloat zNear = 1;
    GLfloat zFar = 1000.0;
    GLfloat aspect = fAspect;
    GLfloat fH = tan( float(30 / 360.0f * 3.14159f) ) * zNear;
    GLfloat fW = fH * aspect;
    glFrustum( -fW, fW, -fH, fH, zNear, zFar );

    glMatrixMode(GL_MODELVIEW); //Говорит о том, что работы будет теперь просмотром, а не проектом.
    glLoadIdentity();
}

void init()
{
    glClearColor (0.3, 0.3, 0.3, 0.0); //Фон.
    srand(time(0));
    //Освещение.
    float diffuseLight[] = {0.2, 0.2, 0.2, 1}; //Цвет объекта под рассеянным освещением.
    float ambientLight[] = {0.9, 0.9, 0.9, 1.0}; //Окружающее освещение.
    glMateriali(GL_FRONT, GL_SHININESS, 128); //Яркость материалов спереди.
    //Свойства материала для освещения.
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    //Включить освещение.
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST); //Автоматически сохранять значения глубины для всех прошедших тест фрагментов и отбрасывать не прошедшие.
    std::ifstream F("../cube.in");
    cube cube2(F, 13);
    cube1 = cube2;
    glutSwapBuffers();
}

void specialKeys(int key, int, int)
{
    if (key == GLUT_KEY_DOWN)
    {
        xRot -= grad;
        if (xRot < 0)
            xRot += 360;
        if (xRot >= 360)
            xRot -= 360;
        glutPostRedisplay();//Вне таймера.
    }

    if (key == GLUT_KEY_UP)
    {
        xRot += grad;
        if (xRot >= 360)
            xRot -= 360;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_RIGHT)
    {
        yRot += grad;
        if (yRot >= 360)
            yRot -= 360;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_LEFT)
    {
        yRot -= grad;
        if (yRot < 0)
            yRot += 360;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_HOME)
    {
        translateZ += 5;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_END)
    {
        translateZ -= 5;
        glutPostRedisplay();
    }

}

void keys(unsigned char key, int, int)
{
    glutSpecialFunc(specialKeys);
    switch (key)
    {
    case 'r': {
        cube1.small_turn(1, grad);
        break;
    }
    case 'L':
    {
        cube1.small_turn(3, grad);
        break;
    }
    case 'u':
    {
        cube1.small_turn(4, grad);
        break;
    }
    case 'D':
    {
        cube1.small_turn(2, grad);
        break;
    }
    case 'F':
    {
        cube1.small_turn(0, grad);
        break;
    }
    case 'b':
    {
        cube1.small_turn(5, grad);
        break;
    }
    case 'R': {
        cube1.small_turn(1, -grad);
        break;
    }
    case 'l':
    {
        cube1.small_turn(3, -grad);
        break;
    }
    case 'U':
    {
        cube1.small_turn(4, -grad);
        break;
    }
    case 'd':
    {
        cube1.small_turn(2, -grad);
        break;
    }
    case 'f':
    {
        cube1.small_turn(0, -grad);
        break;
    }
    case 'B':
    {
        cube1.small_turn(5, -grad);
        break;
    }
    case 'y':
    {
        cube1.small_turn(6, -grad);
        break;
    }
    case 's':
    {
        cube_sweep solver = cube1.solve();
        solution = solver.solver();
        break;
    }
    case 'g': {
        cube_sweep gen;
        gen.generation();
        cube cube2(gen, 13);
        cube1 = cube2;
        break;
    }
    case '[': {
        cube_sweep readed;
        readed.read();
        cube cube2(readed, 13);
        cube1 = cube2;
        break;
    }
    case ']': {
        cube_sweep written = cube1.solve();
        written.write();
        break;
    }
    default:
        break;
    }
display();
}

void mouse(int key, int state, int x, int y)
{
    if (key == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        timerOn = 1 - timerOn;
    }

    if (key == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        tmpx = x;
        tmpy = y;
        glutPostRedisplay();
    }
    if (key == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        tmpx = -1;
        tmpy = -1;
        glutPostRedisplay();
    }
}

void mousemove(int x, int y)
{
    if (tmpx > 0)
    {
        yRot += (x - tmpx);
        tmpx = x;
        if (yRot < 0)
            yRot += 360;
        if (yRot >= 360)
            yRot -= 360;
        glutPostRedisplay();
    }
    if (tmpy > 0)
    {
        xRot += (y - tmpy);
        tmpy = y;
        if (xRot < 0)
            xRot += 360;
        if (xRot >= 360)
            xRot -= 360;
        glutPostRedisplay();
    }
}

void timer(int)
{
    glutTimerFunc(TIMER, timer, 0);
    if (timerOn)
    {
        std::vector<char> comm = { 'r', 'l', 'u', 'd','f', 'b', 'R', 'L', 'U', 'D', 'F', 'B'};
        // Если включен автоматический поворот, и смотрим
        // если сейчас никакая грань не крутится, то начинаем крутить случайную,
        // иначе крутим текущую.
        if (cube1.rotated == -1)
            keys(comm[rand() % 12], 0, 0);
        else
            if (cube1.angle[cube1.rotated] > 90)
                cube1.small_turn(cube1.rotated, -grad);
            else
                cube1.small_turn(cube1.rotated, grad);
    }
    else
    {
        //СЕсли грань недокручено - докручиваем.
        if (cube1.rotated != -1) {
            if (cube1.angle[cube1.rotated]>90)
                cube1.small_turn(cube1.rotated, -grad);
            else
                cube1.small_turn(cube1.rotated, grad);
        }
        //Сборка из вектора решений.
        else if (it < solution.size()) {
            keys(solution[it], 0, 0);
            it++;
            if (it == solution.size())
            {
                solution.clear();
                it = 0;
            }
        }
    }
    display();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv); //Инициализация GLUT.
    //Для анимаций GLUT_DOUBLE(в одном поворачиваем, во втором меняем)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 700);
    glutInitWindowPosition(1, 1);
    glutCreateWindow("Cube");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keys);
    glutMouseFunc(mouse);
    glutMotionFunc(mousemove);
    glutTimerFunc(TIMER, timer, 0);
    glutSpecialFunc(specialKeys);
    //Основной цикл GLUT.
    glutMainLoop();
    return 0;
}