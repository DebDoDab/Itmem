#ifndef LAB8_CUBE_SWEEP_H
#define LAB8_CUBE_SWEEP_H

#include <random>
#include <ctime>
#include <vector>
#include <iostream>
#include <string>
#include "brink.h"

using namespace std;

//Обработка ошибок для проверки на корректность кубика.
class cube_exeption
{
public:
    explicit cube_exeption(std::string s);
    std::string get_error();
private:
    std::string _error;
};

//Развёртка кубика.
class cube_sweep
{
    friend  class cube_solver;
public:
    cube_sweep();
    cube_sweep(cube_sweep const &obj);
    void read(string filename = "../cube.out");
    void write(string filename = "../cube.out");
    explicit cube_sweep(std::vector<brink> const & v); //Массив из 6 граней.
    explicit cube_sweep(std::ifstream &F);
    void generation();
    bool is_correct(); //Проверка на то, собрался ли последний уровень.
    std::vector<char> solver();
    void print();
    std::vector<char> answer();

    //Вертим грани.
    void R();
    void R1();
    void L();
    void L1();
    void U();
    void U1();
    void F();
    void F1();
    void D();
    void D1();
    void B();
    void B1();
    //Поворот всего куба.
    void y();

    bool operator ==(cube_sweep const & a) const;
    std::vector<char> _ans;
    std::vector<brink> _cube;
};

#endif