#include "cube_solver.h"

bool cube_solver::_solve()
{
    _c -> _ans.clear();
    cross();
    first_layer();
    second_layer();
    bool tmp = true;
    last_layer(tmp);
    return tmp;
}

void cube_solver::cross()
{
    int color = _c -> _cube[2][1][1];
    int c;
    for (int i = 0; i < 4; i++) {
        c = 1;
        while (c != 0) {
            c = 0;
            if (_c -> _cube[0][0][1]==color) {
                _c -> F();
                while (_c -> _cube[4][1][2]==color)
                    _c -> U();
                _c -> R();
                c++;
            }
            if (_c -> _cube[0][1][0]==color) {
                while (_c -> _cube[4][1][0]==color)
                    _c -> U();
                _c -> L1();
                c++;
            }
            if (_c -> _cube[0][1][2]==color) {
                while (_c -> _cube[4][1][2]==color)
                    _c -> U();
                _c -> R();
                c++;
            }
            if (_c -> _cube[0][2][1]==color) {
                while (_c -> _cube[4][2][1]==color)
                    _c -> U();
                _c -> F1();
                _c -> U1();
                _c -> R();
                c++;
            }
            if (_c -> _cube[2][0][1]==color) {
                while (_c -> _cube[4][2][1]==color)
                    _c -> U();
                _c -> F();
                _c -> F();
                c++;
            }
            _c -> y();
        }
    }
    for (int i = 0; i < 4; i++)
    {
        while((_c -> _cube[0][0][1] != _c -> _cube[0][1][1]) || (_c -> _cube[4][2][1] != color))
            _c -> U();
        _c -> F();
        _c -> F();
        _c -> y();
    }
}

void cube_solver::first_layer()
{
    int color = _c -> _cube[2][1][1];
    for (int i = 0; i < 2; i++) {
        if ((_c -> _cube[2][0][0]==color) || (_c -> _cube[0][2][0] == color) || (_c -> _cube[3][2][2] == color)) {
            while ((_c -> _cube[0][0][0] == color) || (_c -> _cube[3][0][2]==color) || (_c -> _cube[4][2][0]==color))
                _c -> U();
            left_pif_paf();
        }
        if ((_c -> _cube[2][0][2]==color) || (_c -> _cube[0][2][2] == color) || (_c -> _cube[1][2][0] == color)) {
            while ((_c -> _cube[0][0][2] == color) || (_c -> _cube[1][0][0] == color) || (_c -> _cube[4][2][2] == color))
                _c -> U();
            pif_paf();
        }
        _c -> y();
        _c -> y();
    }
    bool t;
    for (int i = 0; i < 4; i++)
    {
        t = false;
        while (!t)
        {
            if ((_c -> _cube[0][0][2] == _c -> _cube[0][1][1]) && (_c -> _cube[1][0][0] == color) && (_c -> _cube[4][2][2] == _c -> _cube[1][1][1]))
                t = true;
            if ((_c -> _cube[0][0][2] == color) && (_c -> _cube[1][0][0] == _c -> _cube[1][1][1]) && (_c -> _cube[4][2][2] == _c -> _cube[0][1][1]))
                t = true;
            if ((_c -> _cube[0][0][2] == _c -> _cube[1][1][1]) && (_c -> _cube[1][0][0] == _c -> _cube[0][1][1]) && (_c -> _cube[4][2][2] == color))
                t = true;
            if (t)
            {
                while (_c -> _cube[2][0][2] != color) {
                    pif_paf();
                }
                _c -> y();
            }
            else
                _c -> U();
        }
    }
}

void cube_solver::second_layer()
{
    int color = _c -> _cube[4][1][1];
    for (int i = 0; i < 4; i++)
    {
        while ((_c -> _cube[0][1][2] != color) && (_c -> _cube[1][1][0] != color))
            raise_ribs();
        _c -> y();

    }
    bool t;
    for (int i = 0;i < 4; i++)
    {
        t = false;
        while(!t)
        {
            if ((_c -> _cube[1][0][1] == _c -> _cube[1][1][1]) && (_c -> _cube[4][1][2] == _c -> _cube[0][1][1])) {
                edge_to_right();
                t = true;
            }
            if ((_c -> _cube[0][0][1] == _c -> _cube[0][1][1]) && (_c -> _cube[4][2][1] == _c -> _cube[1][1][1])) {
                edge_to_left();
                t = true;
            }
            if (t)
                _c -> y();
            else
                _c -> U();
        }
    }
}

void cube_solver::last_layer(bool &tmp)
{
    last_cross(tmp);
    if (tmp) {
        right_cross(tmp);
        if (tmp)
        {
            swap_corners(tmp);
            if (tmp)
                flip_corners();
        }
    }
}

void cube_solver::last_cross(bool &tmp)
{
    int c = 0;
    int color = _c -> _cube[4][1][1];
    if (_c -> _cube[4][1][0] == color)
        c++;
    if (_c -> _cube[4][0][1] == color)
        c++;
    if (_c -> _cube[4][1][2] == color)
        c++;
    if (_c -> _cube[4][2][1] == color)
        c++;
    switch (c) {
        case 0:
            _c -> F();
            pif_paf();
            _c -> F1();
            nine_hours(color);
            break;
        case 1:
            tmp = false;
            break;
        case 2:
            while (_c -> _cube[4][1][0]!=color)
                _c -> U();
            if (_c -> _cube[4][1][2]==color)
                line(color);
            else
                nine_hours(color);
            break;
        case 3:
            tmp = false;
            break;
        default:
            break;
    }
}

void cube_solver::right_cross(bool &tmp)
{
    int color = _c -> _cube[2][1][1];
    int c = 0;
    bool check = true;
    int max = 0;
    max = 0;
    c = 0;
    for (int i = 0; i<4; i++) {
        c = 0;
        max = std::max(max, count_edge(color, c));
        if ((c==2) && (max==c)) {
            if ((_c->_cube[3][0][1]==_c->_cube[3][1][1]) && (_c->_cube[1][0][1]==_c->_cube[1][1][1]))
                check = false;
            if ((_c->_cube[0][0][1]==_c->_cube[0][1][1]) && (_c->_cube[5][0][1]==_c->_cube[5][1][1]))
                check = false;
        }
        if (c==4)
            break;
        _c->U();

    }
    switch (max) {
        case 2:
            if (check)
                edge_near(color);
            else
                edge_opposite(color);
            break;
        case 4:
            while (_c->_cube[3][0][1]!=_c->_cube[3][1][1])
                _c->U();
            break;
        default:tmp = false;
    }
}

void cube_solver::swap_corners(bool &tmp)
{
    int color = _c -> _cube[4][1][1];
    bool t;
    int count = count_corners(color);
    switch (count)
    {
        case 0:
            switch_corner();
            one_corner(color);
            break;
        case 1:
            one_corner(color);
            break;
        case 4:
            break;
        default:
            tmp = false;
    }
}

void cube_solver::pif_paf()
{
    _c -> R();
    _c -> U();
    _c -> R1();
    _c -> U1();
}

void cube_solver::left_pif_paf()
{
    _c -> L1();
    _c -> U1();
    _c -> L();
    _c -> U();
}

void cube_solver::raise_ribs()
{
    pif_paf();
    _c -> F1();
    _c -> U1();
    _c -> F();
    _c -> U();
}


void cube_solver::edge_to_left()
{
    _c -> U();
    _c -> R();
    _c -> U1();
    _c -> R1();
    _c -> U1();
    _c -> F1();
    _c -> U();
    _c -> F();
}

void cube_solver::edge_to_right()
{
    _c -> U1();
    _c -> F1();
    _c -> U();
    _c -> F();
    _c -> U();
    _c -> R();
    _c -> U1();
    _c -> R1();
}

void cube_solver::nine_hours(int color)
{
    while ((_c -> _cube[4][1][0] != color) || (_c -> _cube[4][0][1] != color))
        _c -> U();
    _c -> F();
    pif_paf();
    _c -> F1();
    line(color);
}

void cube_solver::line(int color)
{
    while (_c -> _cube[4][1][0] != color)
        _c -> U();
    _c -> F();
    pif_paf();
    _c -> F1();
}

int cube_solver::count_edge(int color, int &c)
{
    int max = 0;
    if (_c -> _cube[3][0][1]==_c -> _cube[3][1][1])
        c++;
    if (_c -> _cube[0][0][1]==_c -> _cube[0][1][1])
        c++;
    if (_c -> _cube[1][0][1]==_c -> _cube[1][1][1])
        c++;
    if (_c -> _cube[5][0][1]==_c -> _cube[5][1][1])
        c++;
    max = std::max(max, c);
    return max;
}

void cube_solver::edge_near(int color)
{
    int c = 0;
    while (count_edge(color, c)!=2) {
        _c->U();
        c = 0;
    }
    while ((_c->_cube[5][0][1]!=_c->_cube[5][1][1]) || (_c->_cube[1][0][1]!=_c->_cube[1][1][1]))
        _c->y();
    _c->R();
    _c->U();
    _c->R1();
    _c->U();
    _c->R();
    _c->U();
    _c->U();
    _c->R1();
    _c->U();
}

void cube_solver::edge_opposite(int color)
{
    int c = 0;
    while (count_edge(color, c) != 2) {
        _c -> U();
        c = 0;
    }
    while ((_c -> _cube[5][0][1] != _c -> _cube[5][1][1]) || (_c -> _cube[0][0][1] != _c -> _cube[0][1][1]))
        _c -> y();
    _c -> R();
    _c -> U();
    _c -> R1();
    _c -> U();
    _c -> R();
    _c -> U();
    _c -> U();
    _c -> R1();
    edge_near(color);
}

void cube_solver::switch_corner()
{
    _c -> R();
    _c -> U1();
    _c -> L1();
    _c -> U();
    _c -> R1();
    _c -> U1();
    _c -> L();
    _c -> U();
}

int cube_solver::count_corners(int color)
{
    bool t;
    int count = 0;
    for (int i = 0; i < 4; i++)
    {
        t = false;
        if ((_c -> _cube[0][0][0] == _c -> _cube[0][1][1]) && (_c -> _cube[3][0][2] == _c -> _cube[3][1][1]) && (_c -> _cube[4][2][0] == color))
            t = true;
        if ((_c -> _cube[0][0][0] == color) && (_c -> _cube[3][0][2] == _c -> _cube[0][1][1]) && (_c -> _cube[4][2][0] == _c -> _cube[3][1][1]))
            t = true;
        if ((_c -> _cube[0][0][0] == _c -> _cube[3][1][1]) && (_c -> _cube[3][0][2] == color) && (_c -> _cube[4][2][0] == _c -> _cube[0][1][1]))
            t = true;
        if (t)
            count++;
        _c -> y();

    }
    return count;
}

void cube_solver::one_corner(int color)
{
    bool t;
    while (count_corners(color) != 4) {
        t = false;
        while (!t) {
            if ((_c -> _cube[0][0][0]==_c -> _cube[0][1][1]) && (_c -> _cube[3][0][2]==_c -> _cube[3][1][1]) && (_c -> _cube[4][2][0]==color))
                t = true;
            if ((_c -> _cube[0][0][0]==color) && (_c -> _cube[3][0][2]==_c -> _cube[0][1][1]) && (_c -> _cube[4][2][0]==_c -> _cube[3][1][1]))
                t = true;
            if ((_c -> _cube[0][0][0]==_c -> _cube[3][1][1]) && (_c -> _cube[3][0][2]==color) && (_c -> _cube[4][2][0]==_c -> _cube[0][1][1]))
                t = true;
            if (!t)
                _c -> y();
        }
        switch_corner();
    }
}

void cube_solver::flip_corner()
{
    _c -> L();
    _c -> D();
    _c -> L1();
    _c -> D1();
}

void cube_solver::flip_corners()
{
    for (int i = 0; i < 4; i++)
    {
        while (_c -> _cube[4][2][0] != _c -> _cube[4][1][1])
            flip_corner();
        _c -> U();
    }
}