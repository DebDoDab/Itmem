#ifndef LAB8_CUBE_SOLVER_H
#define LAB8_CUBE_SOLVER_H

#include "cube_sweep.h"

class cube_solver
{
    friend class cube_sweep;
public:
    bool _solve();
    cube_solver () = default;
    explicit cube_solver (cube_sweep *a)
            : _c(a) {}
private:
    cube_sweep* _c;

    //Сборка креста для первого слоя.
    void cross();

    //Первый слой.
    void first_layer();

    //Второй слой.
    void second_layer();

    //Последний слой.
    void last_layer(bool &tmp);

    //Крест в последнем слое.
    void last_cross(bool &tmp);

    //Правильный крест в последнем слое.
    //1.Ребра совпадают рядом.
    //2.Ребра совпадают напротив.
    //3.Уже правильный.
    void right_cross(bool &tmp);

    //Расстановка углов в последнем слое.
    void swap_corners(bool &tmp);

    //Средний и последний уровень.
    //Вверх-вправо-вниз-влево
    void pif_paf();

    //Левой рукой.
    void left_pif_paf();

    //Поднять ребра.
    void raise_ribs();

    //Ребро идет вправо.
    void edge_to_left();

    //Ребро идет влево.
    void edge_to_right();

    //Точка → пол креста (девять часов) → палка → крест.
    void nine_hours(int color);

    //F (пиф-паф) F'.
    void line(int color);

    //Подсчёт цветов рёбер для определения ситуации, как совпадают рёбра.
    int count_edge(int color, int &c);

    //Ребра совпадают рядом.
    void edge_near(int color);

    //Ребра совпадают напротив.
    void edge_opposite(int color);

    //Для расстановки углов.
    void switch_corner();

    //Подсчёт цветов на грани, чтобы определить нужно ли нам собирать крест.
    int count_corners(int color);

    //Для расстановки углов в последнем слое.
    void one_corner(int color);

    //Разворот угла.
    void flip_corner();

    //Разворот углов последнего слоя.
    void flip_corners();
};

#endif

