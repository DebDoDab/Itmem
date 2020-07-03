#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
#include "brink.h"
#include "cube_sweep.h"
#include "cube_solver.h"

cube_exeption::cube_exeption(std::string s)
        : _error(std::move(s)) {}

std::string cube_exeption:: get_error()
{
    return _error;
}

cube_sweep::cube_sweep()
{
    brink a;
    for (int i = 0; i < 6; i++)
    {
        a.create(i);
        _cube.push_back(a);
    }
}


cube_sweep::cube_sweep(cube_sweep const &obj)
{
    _cube = obj._cube;
}

cube_sweep::cube_sweep(std::vector<brink> const & v)
{
    _cube = v;
}

//Записываем данные в развёртку.
cube_sweep::cube_sweep(std::ifstream &F)
{
    try {
        _cube.resize(6);
        std::string s;
        for (int i = 0; i<3; i++) {
            getline(F,s);
            if (s.length()!=6)
                throw cube_exeption("Incorrect string length");
            for (int j = 0; j<3; j++) {
                switch (s[j+3]) {
                case 'W':_cube[4][i][j] = 0;
                    break;
                case 'O':_cube[4][i][j] = 1;
                    break;
                case 'B':_cube[4][i][j] = 2;
                    break;
                case 'R':_cube[4][i][j] = 3;
                    break;
                case 'G':_cube[4][i][j] = 4;
                    break;
                case 'Y':_cube[4][i][j] = 5;
                    break;
                default:throw cube_exeption("Incorrect color");
                }
            }
        }
        for (int i = 0; i<3; i++) {
            getline(F, s);
            if (s.length()!=12)
                throw cube_exeption("Incorrect string length");
            std::vector<int> n_brick{3, 0, 1, 5};
            for (int k = 0; k<4; k++)
                for (int j = 0; j<3; j++) {
                    switch (s[j+k*3]) {
                    case 'W':_cube[n_brick[k]][i][j] = 0;
                        break;
                    case 'O':_cube[n_brick[k]][i][j] = 1;
                        break;
                    case 'B':_cube[n_brick[k]][i][j] = 2;
                        break;
                    case 'R':_cube[n_brick[k]][i][j] = 3;
                        break;
                    case 'G':_cube[n_brick[k]][i][j] = 4;
                        break;
                    case 'Y':_cube[n_brick[k]][i][j] = 5;
                        break;
                    default:throw cube_exeption("Incorrect color");
                    }
                }
        }
        for (int i = 0; i < 3; i++) {
            getline(F, s);
            if (s.length() != 6)
                throw cube_exeption("Incorrect string length");
            for (int j = 0; j < 3; j++) {
                switch (s[j+3]) {
                case 'W':_cube[2][i][j] = 0;
                    break;
                case 'O':_cube[2][i][j] = 1;
                    break;
                case 'B':_cube[2][i][j] = 2;
                    break;
                case 'R':_cube[2][i][j] = 3;
                    break;
                case 'G':_cube[2][i][j] = 4;
                    break;
                case 'Y':_cube[2][i][j] = 5;
                    break;
                default:throw cube_exeption("Incorrect color");
                }
            }
        }
    }
    catch (cube_exeption &ex) {
        std::cerr << ex.get_error() << std::endl;
        _cube.resize(0);
    }
}

//Генерация рандомного кубика.
void cube_sweep::generation()
{
    std::mt19937 gen(time(0));
    std::uniform_int_distribution<int> v(0, 3);
    int num = v(gen);
    for (int i = 0; i < num; i++)
        R();
    num = v(gen);
    for (int i = 0; i < num; i++)
        U();
    num = v(gen);
    for (int i = 0; i < num; i++)
        L();
    num = v(gen);
    for (int i = 0; i < num; i++)
        F();
    num = v(gen);
    for (int i = 0; i < num; i++)
        D();
    num = v(gen);
    for (int i = 0; i < num; i++)
        B();
}

//Сборка последнего слоя.
bool cube_sweep:: is_correct()
{
    cube_sweep full;
    if (full == *this)
        return true;
    cube_solver solve(this);
    return solve._solve();
}

//Проверка последнего слоя на сборку.
std::vector<char> cube_sweep::solver()
{
    cube_solver solve(this);
    try {
        if (!solve._solve())
            throw cube_exeption("Incorrect state");
        return _ans;
    }
    catch (cube_exeption ex)
    {
        std::cerr << ex.get_error();
        exit(1);
    }
}

void cube_sweep::print()
{
    try {
        if (_cube.empty())
            throw cube_exeption("Cube is empty");
        std::string s = "WOBRGY";
        for (int i = 0; i < 3; i++) {
            std::cout << "   ";
            for (int j = 0; j < 3; j++)
                std:: cout << s[_cube[4][i][j]];
            std::cout<< std:: endl;
        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
                std::cout << s[_cube[3][i][j]];
            for (int j = 0; j < 3; j++)
                std::cout << s[_cube[0][i][j]];
            for (int j = 0; j < 3; j++)
                std::cout << s[_cube[1][i][j]];
            for (int j = 0; j < 3; j++)
                std::cout << s[_cube[5][i][j]];
            std::cout << std::endl;
        }
        for (int i = 0; i < 3; i++) {
            std::cout << "   ";
            for (int j = 0; j < 3; j++)
                std:: cout << s[_cube[2][i][j]];
            std::cout<< std:: endl;
        }
    }
    catch (cube_exeption ex)
    {
        std::cerr << ex.get_error() << std::endl;
    }
}

std::vector<char> cube_sweep::answer()
{
    return _ans;
}

void cube_sweep::R()
{
    _ans.push_back('R');
    std::vector<int> tmp = {_cube[0][0][2], _cube[0][1][2], _cube[0][2][2]};
    for (int i = 0; i < 3; i++) {
        _cube[0][i][2] = _cube[2][i][2];
        _cube[2][i][2] = _cube[5][2 - i][0];
        _cube[5][2 - i][0] = _cube[4][i][2];
        _cube[4][i][2] = tmp[i];
    }
    tmp.resize(0);
    _cube[1].right_wise();
}

void cube_sweep::R1()
{
    _ans.push_back('r');
    std::vector<int> tmp = {_cube[0][0][2], _cube[0][1][2], _cube[0][2][2]};
    for (int i = 0; i < 3; i++) {
        _cube[0][i][2] = _cube[4][i][2];
        _cube[4][i][2] = _cube[5][2 - i][0];
        _cube[5][2 - i][0] = _cube[2][i][2];
        _cube[2][i][2] = tmp[i];
    }
    tmp.resize(0);
    _cube[1].left_wise();
}

void cube_sweep::L()
{
    _ans.push_back('L');
    std::vector<int> tmp = {_cube[0][0][0], _cube[0][1][0], _cube[0][2][0]};
    tmp.push_back(_cube[0][0][0]);
    tmp.push_back(_cube[0][1][0]);
    tmp.push_back(_cube[0][2][0]);
    for (int i = 0; i < 3; i++) {
        _cube[0][i][0] = _cube[4][i][0];
        _cube[4][i][0] = _cube[5][2 - i][2];
        _cube[5][2 - i][2] = _cube[2][i][0];
        _cube[2][i][0] = tmp[i];
    }
    tmp.resize(0);
    _cube[3].right_wise();
}

void cube_sweep::L1()
{
    _ans.push_back('l');
    std::vector<int> tmp = {_cube[0][0][0], _cube[0][1][0], _cube[0][2][0]};
    for (int i = 0; i < 3; i++) {
        _cube[0][i][0] = _cube[2][i][0];
        _cube[2][i][0] = _cube[5][2 - i][2];
        _cube[5][2 - i][2] = _cube[4][i][0];
        _cube[4][i][0] = tmp[i];
    }
    tmp.resize(0);
    _cube[3].left_wise();
}

void cube_sweep::U()
{
    _ans.push_back('U');
    std::vector<int> tmp = {_cube[0][0][0], _cube[0][0][1], _cube[0][0][2]};
    for (int i = 0; i < 3; i++) {
        _cube[0][0][i] = _cube[1][0][i];
        _cube[1][0][i] = _cube[5][0][i];
        _cube[5][0][i] = _cube[3][0][i];
        _cube[3][0][i] = tmp[i];
    }
    tmp.resize(0);
    _cube[4].right_wise();
}

void cube_sweep::U1()
{
    _ans.push_back('u');
    std::vector<int> tmp = {_cube[0][0][0], _cube[0][0][1], _cube[0][0][2]};
    for (int i = 0; i < 3; i++) {
        _cube[0][0][i] = _cube[3][0][i];
        _cube[3][0][i] = _cube[5][0][i];
        _cube[5][0][i] = _cube[1][0][i];
        _cube[1][0][i] = tmp[i];
    }
    tmp.resize(0);
    _cube[4].left_wise();
}

void cube_sweep::F()
{
    _ans.push_back('F');
    std::vector<int> tmp = {_cube[3][0][2], _cube[3][1][2], _cube[3][2][2]};
    for (int i = 0; i < 3; i++) {
        _cube[3][i][2] = _cube[2][0][i];
        _cube[2][0][i] = _cube[1][2 - i][0];
        _cube[1][2 - i][0] = _cube[4][2][2 - i];
        _cube[4][2][2 - i] = tmp[i];
    }
    tmp.resize(0);
    _cube[0].right_wise();
}

void cube_sweep::F1()
{
    _ans.push_back('f');
    std::vector<int> tmp = {_cube[3][0][2], _cube[3][1][2], _cube[3][2][2]};
    for (int i = 0; i < 3; i++) {
        _cube[3][i][2] = _cube[4][2][2 - i];
        _cube[4][2][2 - i] = _cube[1][2 - i][0];
        _cube[1][2 - i][0] = _cube[2][0][i];
        _cube[2][0][i] = tmp[i];
    }
    tmp.resize(0);
    _cube[0].left_wise();
}

void cube_sweep::D()
{
    _ans.push_back('D');
    std::vector<int> tmp = {_cube[0][2][0], _cube[0][2][1], _cube[0][2][2]};
    for (int i = 0; i < 3; i++) {
        _cube[0][2][i] = _cube[3][2][i];
        _cube[3][2][i] = _cube[5][2][i];
        _cube[5][2][i] = _cube[1][2][i];
        _cube[1][2][i] = tmp[i];
    }
    tmp.resize(0);
    _cube[2].right_wise();
}

void cube_sweep::D1()
{
    _ans.push_back('d');
    std::vector<int> tmp = {_cube[0][2][0], _cube[0][2][1], _cube[0][2][2]};
    for (int i = 0; i < 3; i++) {
        _cube[0][2][i] = _cube[1][2][i];
        _cube[1][2][i] = _cube[5][2][i];
        _cube[5][2][i] = _cube[3][2][i];
        _cube[3][2][i] = tmp[i];
    }
    tmp.resize(0);
    _cube[2].left_wise();
}

void cube_sweep::B()
{
    _ans.push_back('B');
    std::vector<int> tmp = {_cube[3][0][0], _cube[3][1][0], _cube[3][2][0]};
    for (int i = 0; i < 3; i++) {
        _cube[3][i][0] = _cube[4][0][2 - i];
        _cube[4][0][2 - i] = _cube[1][2 - i][2];
        _cube[1][2 - i][2] = _cube[2][2][i];
        _cube[2][2][i] = tmp[i];
    }
    tmp.resize(0);
    _cube[5].right_wise();
}

void cube_sweep::B1()
{
    _ans.push_back('b');
    std::vector<int> tmp = {_cube[3][0][0], _cube[3][1][0], _cube[3][2][0]};
    for (int i = 0; i < 3; i++) {
        _cube[3][i][0] = _cube[2][2][i];
        _cube[2][2][i] = _cube[1][2 - i][2];
        _cube[1][2 - i][2] = _cube[4][0][2 - i];
        _cube[4][0][2 - i] = tmp[i];
    }
    tmp.resize(0);
    _cube[5].left_wise();
}

void cube_sweep::y()
{
    _ans.push_back('y');
    brink _brink;
    _brink = _cube[0];
    _cube[0] = _cube[1];
    _cube[1] = _cube[5];
    _cube[5] = _cube[3];
    _cube[3] = _brink;
    _cube[4].right_wise();
    _cube[2].left_wise();
}

bool cube_sweep:: operator ==(cube_sweep const&a) const
{
    return a._cube == _cube;
}

void cube_sweep::read(string filename) {
    ifstream fin(filename);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                fin >> _cube[i][j][k];
            }
        }
    }
    fin.close();
}

void cube_sweep::write(string filename) {
    ofstream fout(filename);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                fout << _cube[i][j][k] << " ";
            }
            fout << endl;
        }
        fout << endl;
    }
    fout.close();
}
