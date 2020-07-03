#ifndef LAB8_BRINK_H
#define LAB8_BRINK_H

#include <vector>

//Грани.
//Нужна для сборки методом слоёв.
class brink
{
public:
    std::vector<std::vector<int>> _brink;

    explicit brink();

    explicit brink(std::vector<std::vector<int>> const &obj);

    void create(int);

    std::vector<int>& operator [](int);

    //Поворот грани по часовой.
    void right_wise();

    //Против часовой.
    void left_wise();

    bool operator ==(brink const &) const;

    ~brink() = default;
};

#endif