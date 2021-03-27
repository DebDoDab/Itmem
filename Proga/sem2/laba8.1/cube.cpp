#include <cstring>
#include "cube.h"


cube::cube(cube const &a)
        :size(a.size), rotated(a.rotated), sweep(a.sweep)
{
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++)
            for (int k = 0; k<3; k++)
                cubes[i][j][k] = a.cubes[i][j][k];
    for (int i = 0; i<6; i++) {
        angle[i] = a.angle[i];
        color[i] = a.color[i];
    }
    rotated = -1;
}

cube::cube(cube_sweep const &Cur, double _size)
{
    size = _size;
    for (auto& i : cubes)
        for (auto& j : i)
            for (auto& k : j) {
                k.size = double(_size) / 3 * 0.95; //Маленькие кубики(размер).
            }
    int i, j, k;
    size = _size;
    rotated = -1;
    std::vector<brink> br = Cur._cube;
    //Раскрашиваем кубик.
    for (i = 0; i<3; i++)
        for (j = 0; j<3; j++)
            cubes[i][j][2].set(4, _correct_color[br[4][2-j][i]]);
    for (i = 0; i<3; i++)
        for (j = 0; j<3; j++)
            cubes[i][j][0].set(2, _correct_color[br[2][j][i]]);
    for (k = 0; k<3; k++)
        for (j = 0; j<3; j++)
            cubes[k][0][j].set(0, _correct_color[br[0][2-j][k]]);
    for (k = 0; k<3; k++)
        for (j = 0; j<3; j++)
            cubes[k][2][j].set(5, _correct_color[br[5][2-j][2-k]]);
    for (i = 0; i<3; i++)
        for (k = 0; k<3; k++)
            cubes[0][i][k].set(3, _correct_color[br[3][2-k][2-i]]);
    for (i = 0; i<3; i++)
        for (k = 0; k<3; k++)
            cubes[2][i][k].set(1, _correct_color[br[1][2-k][i]]);
    //Считываем цвета с развёртки.
    for (int i = 0; i<6; i++) {
        color[i] = sweep._cube[i][1][1];
        angle[i] = 0;
    }
}

cube::cube(std::ifstream &F, double size)
{
    cube_sweep _new(F);
    sweep = _new;
    cube C(sweep, 13);
    *this = C;
    rotated = -1;
}

void cube::draw()
{
    //check показывает, находится ли в состоянии покоя деталь с координатами (i, j, k).
    memset(check, true, sizeof(check));
    //Крутится ли грань.
    if (rotated!=-1) {
        glPushMatrix();
        int i, j, k;
        int tmp1 = 2;
        if ((rotated==4) || (rotated==2))
            tmp1 = 0;
        if ((rotated==0) || (rotated==5))
            tmp1 = 1;
        if (rotated==6)
            tmp1 = 3;
        switch (tmp1) {
            case 0: {
                if (rotated==4)
                    k = 2;
                else k = 0;
                for (i = 0; i<3; i++)
                    for (j = 0; j<3; j++)
                        check[i][j][k] = false;
                //Теперь нужно покрутить грань под номером current на угол rotate[current]
                //относительно центра этой грани.
                //Для этого сдвинемся к центру, покрутим, сдвинемся обратно.
                glTranslated(size/2, size/2, 0); //Сдвигаемся к центру.
                glRotatef(angle[rotated], 0, 0, 1); //Крутим.
                glTranslated(-size/2, -size/2, 0); //Сдвигаемся обратно.
                //Рисуем.
                for (i = 0; i<3; i++)
                    for (j = 0; j<3; j++)
                        cubes[i][j][k].draw(size/3*i, size/3*j, size/3*k);
                break;
            }
            case 1: {
                if (rotated==5)
                    j = 2;
                else j = 0;
                for (i = 0; i<3; i++)
                    for (k = 0; k<3; k++)
                        check[i][j][k] = false;
                glTranslated(size/2, 0, size/2);
                glRotatef(angle[rotated], 0, 1, 0);
                glTranslated(-size/2, 0, -size/2);
                for (i = 0; i<3; i++)
                    for (k = 0; k<3; k++)
                        cubes[i][j][k].draw(size/3*i, size/3*j, size/3*k);
                break;
            }
            case 2: {
                if (rotated==1)
                    i = 2;
                else i = 0;
                for (j = 0; j<3; j++)
                    for (k = 0; k<3; k++)
                        check[i][j][k] = false;
                glTranslated(0, size/2, size/2);
                glRotatef(angle[rotated], 1, 0, 0);
                glTranslated(0, -size/2, -size/2);
                for (j = 0; j<3; j++)
                    for (k = 0; k<3; k++)
                        cubes[i][j][k].draw(size/3*i, size/3*j, size/3*k);
                break;
            }
            case 3: {
                for (i = 0; i<3; i++)
                    for (j = 0; j<3; j++)
                        for (k = 0; k<3; k++)
                            check[i][j][k] = false;
                glTranslated(size/2, size/2, 0);
                glRotatef(angle[rotated], 0, 0, 1);
                glTranslated(-size/2, -size/2, 0);
                for (i = 0; i<3; i++)
                    for (j = 0; j<3; j++)
                        for (k = 0; k<3; k++)
                            cubes[i][j][k].draw(size/3*i, size/3*j, size/3*k);
            }
        }
        glPopMatrix();
    }
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++)
            for (int k = 0; k<3; k++)
                if (check[i][j][k])
                    cubes[i][j][k].draw(size/3*i, size/3*j, size/3*k);
    //Теперь рисуем те детали, которые не поварачивались выше,
    //они отмечены check[i][j][k] = true.
    glPopMatrix();
}

void cube::full_turn(int idx, int sign)
{
    if (sign==-1)
        sign = 3;
    int k = 0, i = 0, j = 0;
    //sign задаётся в зависимости он направления.
    //sign = -1, sign = 1
    //если sign = -1, значит крутим 3 раза.
    int tmp1 = 2;
    if ((rotated==4) || (rotated==2))
        tmp1 = 0;
    if ((rotated==0) || (rotated==5))
        tmp1 = 1;
    switch (tmp1) {
        case 0: {
            for (int it = 0; it<sign; it++) {
                //Копируем повёрнутую на 90 градусов верхнюю/нижнюю грань.
                //В массив tmp, затем грани присваиваем tmp.
                //И не забываем повернуть каждую деталь этой грани.
                if (rotated==4)
                    k = 2;
                for (i = 0; i<3; i++)
                    for (j = 0; j<3; j++)
                        tmp[j][2-i] = cubes[i][j][k];
                for (i = 0; i<3; i++)
                    for (j = 0; j<3; j++)
                        tmp[i][j].XOY(), cubes[i][j][k] = tmp[i][j];
            }
            break;
        }
        case 1: {
            for (int it = 0; it<sign; it++) {
                if (rotated==5)
                    j = 2;
                for (i = 0; i<3; i++)
                    for (k = 0; k<3; k++)
                        tmp[k][2-i] = cubes[i][j][k];
                for (i = 0; i<3; i++)
                    for (k = 0; k<3; k++)
                        tmp[i][k].YOZ(), cubes[i][j][k] = tmp[i][k];
            }
            break;
        }
        case 2: {
            for (int it = 0; it<sign; it++) {
                if (rotated==1)
                    i = 2;
                for (j = 0; j<3; j++)
                    for (k = 0; k<3; k++)
                        tmp[k][2-j] = cubes[i][j][k];
                for (j = 0; j<3; j++)
                    for (k = 0; k<3; k++)
                        tmp[j][k].XOZ(), cubes[i][j][k] = tmp[j][k];
            }
            break;
        }
    }
}

void cube::small_turn(int idx, int _angle)
{
    //Мы пытаемся покрутить грань с номером idx,
    //значит нужно проверить что другая грань уже не крутится.
    if (rotated==-1 || rotated==idx) {
        //Обновляем поворот.
        angle[idx] += _angle;
        if (angle[idx]<0)
            angle[idx] += 360;
        if (angle[idx]%90!=0)
            rotated = idx;
        else {
            //Если угол стал кратным 90, то поварачиваем на массиве.
            if (rotated==6)
                swapper();
            if ((idx==0) || (idx==5)) {
                if (angle[idx]==90)
                    full_turn(idx, 1);
                else
                    full_turn(idx, -1);
            }
            else {
                if (angle[idx]==90)
                    full_turn(idx, -1);
                else
                    full_turn(idx, 1);
            }
            angle[idx] = 0;
            rotated = -1;
        }
    }
}

void cube::swapper()
{
    small_cube tmp1;
    int i, j, k;
    for (k = 0; k<3; k++) {
        tmp1 = cubes[0][0][k];
        cubes[0][0][k] = cubes[2][0][k];
        cubes[2][0][k] = cubes[2][2][k];
        cubes[2][2][k] = cubes[0][2][k];
        cubes[0][2][k] = tmp1;
        tmp1 = cubes[1][0][k];
        cubes[1][0][k] = cubes[2][1][k];
        cubes[2][1][k] = cubes[1][2][k];
        cubes[1][2][k] = cubes[0][1][k];
        cubes[0][1][k] = tmp1;
    }
    full_turn(3, -1);
    i = 0;
    for (j = 0; j<3; j++)
        for (k = 0; k<3; k++)
            cubes[i][j][k].YOZ();
    for (i = 1; i<3; i++)
        for (j = 0; j<3; j++)
            for (k = 0; k<3; k++)
                cubes[i][j][k].XOY();
    angle[6] = 0;
    rotated = -1;
    angle[6] = 0;
    rotated = -1;
}

cube_sweep cube::solve()
{
    int i, j, k;
    std::vector<brink> br(6);
    //Для каждой грани.
    for (i = 0; i<3; i++)
        for (j = 0; j<3; j++)
            switcher(br, 4, 2- j, i, i, j, 2);
    for (i = 0; i<3; i++)
        for (j = 0; j<3; j++)
            switcher(br, 2, j, i, i, j, 0);
    for (k = 0; k<3; k++)
        for (j = 0; j<3; j++)
            switcher(br, 0, 2-j, k, k, 0, j);
    for (k = 0; k<3; k++)
        for (j = 0; j<3; j++)
            switcher(br, 5, 2-j, 2-k, k, 2, j);
    for (i = 0; i<3; i++)
        for (k = 0; k<3; k++)
            switcher(br, 3, 2- k, 2 - i, 0, i, k);
    for (i = 0; i<3; i++)
        for (k = 0; k<3; k++)
            switcher(br, 1, 2 -k, i, 2, i, k);
    sweep._cube = br;
    return sweep;
}

void cube::switcher(std::vector<brink> &br, int a, int b, int c, int i, int j, int k)
{
    switch (cubes[i][j][k]._color[a])
    {
        case 0xFFFFFF:{br[a][b][c] = 0;
            break;
        }
        case  0xCD853F:{br[a][b][c] = 1;
            break;
        }
        case 0x000000FF:{br[a][b][c] = 2;
            break;
        }
        case 0xFF0000:{br[a][b][c] = 3;
            break;
        }
        case 0x00FF00:{br[a][b][c] = 4;
            break;
        }
        case 0xFFFF00:{br[a][b][c] = 5;
            break;
        }
    }
}
