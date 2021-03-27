//
// Created by Арсений Карпов on 21.05.2020.
//

#include "cube_sweep.h"

cube_exeption::cube_exeption(string s)
        : _error(move(s)) {}
string cube_exeption:: get_error()
{
    return _error;
}

cube_sweep::cube_sweep(Cube& x)
{
    _cube = x;

    //wobrgy
//     4
//    3015
//     2
    //wgrbyo
//     3
//    0245
//     1
//3 -> 4 -> 1 -> 2 -> 0
swap(_cube.cube[3], _cube.cube[4]);
swap(_cube.cube[1], _cube.cube[4]);
swap(_cube.cube[1], _cube.cube[2]);
swap(_cube.cube[0], _cube.cube[2]);
//1 -> 5 -> 4
swap(_cube.cube[1], _cube.cube[5]);
swap(_cube.cube[4], _cube.cube[5]);
//2 -> 3
swap(_cube.cube[2], _cube.cube[3]);

}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


cube_sweep::cube_sweep(cube_sweep const &obj)
{
    _cube = obj._cube;
}

cube_sweep::cube_sweep(vector<vector<vector<int>>> const & v)
{
    _cube.cube = v;
}

cube_sweep::cube_sweep(ifstream &F)
{
    try {
        _cube.cube.resize(6);
        string s;
        for (int i = 0; i<3; i++) {
            getline(F,s);
            if (s.length()!=6)
                throw cube_exeption("Incorrect string length");
            for (int j = 0; j<3; j++) {
                switch (s[j+3]) {
                case 'W':_cube.cube[4][i][j] = 0;
                    break;
                case 'O':_cube.cube[4][i][j] = 5;
                    break;
                case 'B':_cube.cube[4][i][j] = 3;
                    break;
                case 'R':_cube.cube[4][i][j] = 2;
                    break;
                case 'G':_cube.cube[4][i][j] = 1;
                    break;
                case 'Y':_cube.cube[4][i][j] = 4;
                    break;
                default:throw cube_exeption("Incorrect collor");
                }
            }
        }
        for (int i = 0; i<3; i++) {
            getline(F, s);
            if (s.length()!=12)
                throw cube_exeption("Incorrect string length");
            vector<int> n_brick{3, 0, 1, 5};
            for (int k = 0; k<4; k++)
                for (int j = 0; j<3; j++) {
                    switch (s[j+k*3]) {
                    case 'W':_cube.cube[n_brick[k]][i][j] = 0;
                        break;
                    case 'O':_cube.cube[n_brick[k]][i][j] = 5;
                        break;
                    case 'B':_cube.cube[n_brick[k]][i][j] = 3;
                        break;
                    case 'R':_cube.cube[n_brick[k]][i][j] = 2;
                        break;
                    case 'G':_cube.cube[n_brick[k]][i][j] = 1;
                        break;
                    case 'Y':_cube.cube[n_brick[k]][i][j] = 4;
                        break;
                    default:throw cube_exeption("Incorrect collor");
                    }
                }
        }
        for (int i = 0; i < 3; i++) {
            getline(F, s);
            if (s.length() != 6)
                throw cube_exeption("Incorrect string length");
            for (int j = 0; j < 3; j++) {
                switch (s[j+3]) {
                case 'W':_cube.cube[4][i][j] = 0;
                    break;
                case 'O':_cube.cube[4][i][j] = 5;
                    break;
                case 'B':_cube.cube[4][i][j] = 3;
                    break;
                case 'R':_cube.cube[4][i][j] = 2;
                    break;
                case 'G':_cube.cube[4][i][j] = 1;
                    break;
                case 'Y':_cube.cube[4][i][j] = 4;
                    break;
                default:throw cube_exeption("Incorrect collor");
                }
            }
        }
    }
    catch (cube_exeption &ex) {
        cerr << ex.get_error() << endl;
        _cube.cube.resize(0);
    }
}

void cube_sweep::generation()
{
    mt19937 gen(time(0));
    uniform_int_distribution<int> v(0, 3);
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

bool cube_sweep:: is_correct()
{
    cube_sweep full;
    if (full == *this)
        return true;
    cube_solver solve(this);
    return solve._solve();
}

vector<char> cube_sweep::solver()
{
    cube_solver solve(this);
    try {
        if (!solve._solve())
            throw cube_exeption("Incorrect state");
        return _ans;
    }
    catch (cube_exeption ex)
    {
        cerr << ex.get_error();
        exit(1);
    }
}

void cube_sweep::print()
{
    try {
        if (_cube.cube.empty())
            throw cube_exeption("Cube is empty");
        string s = "WOBRGY";
        for (int i = 0; i < 3; i++) {
            cout << "   ";
            for (int j = 0; j < 3; j++)
                 cout << s[_cube.cube[4][i][j]];
            cout<<  endl;
        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
                cout << s[_cube.cube[3][i][j]];
            for (int j = 0; j < 3; j++)
                cout << s[_cube.cube[0][i][j]];
            for (int j = 0; j < 3; j++)
                cout << s[_cube.cube[1][i][j]];
            for (int j = 0; j < 3; j++)
                cout << s[_cube.cube[5][i][j]];
            cout << endl;
        }
        for (int i = 0; i < 3; i++) {
            cout << "   ";
            for (int j = 0; j < 3; j++)
                 cout << s[_cube.cube[2][i][j]];
            cout << endl;
        }
    }
    catch (cube_exeption ex)
    {
        cerr << ex.get_error() << endl;
    }
}

vector<char> cube_sweep::answer()
{
    return _ans;
}

void cube_sweep::R()
{
    _ans.push_back('R');
    vector<int> tmp = {_cube.cube[0][0][2], _cube.cube[0][1][2], _cube.cube[0][2][2]};
    for (int i = 0; i < 3; i++) {
        _cube.cube[0][i][2] = _cube.cube[2][i][2];
        _cube.cube[2][i][2] = _cube.cube[5][2 - i][0];
        _cube.cube[5][2 - i][0] = _cube.cube[4][i][2];
        _cube.cube[4][i][2] = tmp[i];
    }
    tmp.resize(0);
    _cube.rightwise(1);
}

void cube_sweep::R1()
{
    _ans.push_back('r');
    vector<int> tmp = {_cube.cube[0][0][2], _cube.cube[0][1][2], _cube.cube[0][2][2]};
    for (int i = 0; i < 3; i++) {
        _cube.cube[0][i][2] = _cube.cube[4][i][2];
        _cube.cube[4][i][2] = _cube.cube[5][2 - i][0];
        _cube.cube[5][2 - i][0] = _cube.cube[2][i][2];
        _cube.cube[2][i][2] = tmp[i];
    }
    tmp.resize(0);
    _cube.leftwise(1);
}

void cube_sweep::L()
{
    _ans.push_back('L');
    vector<int> tmp = {_cube.cube[0][0][0], _cube.cube[0][1][0], _cube.cube[0][2][0]};
    tmp.push_back(_cube.cube[0][0][0]);
    tmp.push_back(_cube.cube[0][1][0]);
    tmp.push_back(_cube.cube[0][2][0]);
    for (int i = 0; i < 3; i++) {
        _cube.cube[0][i][0] = _cube.cube[4][i][0];
        _cube.cube[4][i][0] = _cube.cube[5][2 - i][2];
        _cube.cube[5][2 - i][2] = _cube.cube[2][i][0];
        _cube.cube[2][i][0] = tmp[i];
    }
    tmp.resize(0);
    _cube.rightwise(3);
}

void cube_sweep::L1()
{
    _ans.push_back('l');
    vector<int> tmp = {_cube.cube[0][0][0], _cube.cube[0][1][0], _cube.cube[0][2][0]};
    for (int i = 0; i < 3; i++) {
        _cube.cube[0][i][0] = _cube.cube[2][i][0];
        _cube.cube[2][i][0] = _cube.cube[5][2 - i][2];
        _cube.cube[5][2 - i][2] = _cube.cube[4][i][0];
        _cube.cube[4][i][0] = tmp[i];
    }
    tmp.resize(0);
    _cube.leftwise(3);
}

void cube_sweep::U()
{
    _ans.push_back('U');
    vector<int> tmp = {_cube.cube[0][0][0], _cube.cube[0][0][1], _cube.cube[0][0][2]};
    for (int i = 0; i < 3; i++) {
        _cube.cube[0][0][i] = _cube.cube[1][0][i];
        _cube.cube[1][0][i] = _cube.cube[5][0][i];
        _cube.cube[5][0][i] = _cube.cube[3][0][i];
        _cube.cube[3][0][i] = tmp[i];
    }
    tmp.resize(0);
    _cube.rightwise(4);
}

void cube_sweep::U1()
{
    _ans.push_back('u');
    vector<int> tmp = {_cube.cube[0][0][0], _cube.cube[0][0][1], _cube.cube[0][0][2]};
    for (int i = 0; i < 3; i++) {
        _cube.cube[0][0][i] = _cube.cube[3][0][i];
        _cube.cube[3][0][i] = _cube.cube[5][0][i];
        _cube.cube[5][0][i] = _cube.cube[1][0][i];
        _cube.cube[1][0][i] = tmp[i];
    }
    tmp.resize(0);
    _cube.leftwise(4);
}

void cube_sweep::F()
{
    _ans.push_back('F');
    vector<int> tmp = {_cube.cube[3][0][2], _cube.cube[3][1][2], _cube.cube[3][2][2]};
    for (int i = 0; i < 3; i++) {
        _cube.cube[3][i][2] = _cube.cube[2][0][i];
        _cube.cube[2][0][i] = _cube.cube[1][2 - i][0];
        _cube.cube[1][2 - i][0] = _cube.cube[4][2][2 - i];
        _cube.cube[4][2][2 - i] = tmp[i];
    }
    tmp.resize(0);
    _cube.rightwise(0);
}

void cube_sweep::F1()
{
    _ans.push_back('f');
    vector<int> tmp = {_cube.cube[3][0][2], _cube.cube[3][1][2], _cube.cube[3][2][2]};
    for (int i = 0; i < 3; i++) {
        _cube.cube[3][i][2] = _cube.cube[4][2][2 - i];
        _cube.cube[4][2][2 - i] = _cube.cube[1][2 - i][0];
        _cube.cube[1][2 - i][0] = _cube.cube[2][0][i];
        _cube.cube[2][0][i] = tmp[i];
    }
    tmp.resize(0);
    _cube.leftwise(0);
}

void cube_sweep::D()
{
    _ans.push_back('D');
    vector<int> tmp = {_cube.cube[0][2][0], _cube.cube[0][2][1], _cube.cube[0][2][2]};
    for (int i = 0; i < 3; i++) {
        _cube.cube[0][2][i] = _cube.cube[3][2][i];
        _cube.cube[3][2][i] = _cube.cube[5][2][i];
        _cube.cube[5][2][i] = _cube.cube[1][2][i];
        _cube.cube[1][2][i] = tmp[i];
    }
    tmp.resize(0);
    _cube.rightwise(2);
}

void cube_sweep::D1()
{
    _ans.push_back('d');
    vector<int> tmp = {_cube.cube[0][2][0], _cube.cube[0][2][1], _cube.cube[0][2][2]};
    for (int i = 0; i < 3; i++) {
        _cube.cube[0][2][i] = _cube.cube[1][2][i];
        _cube.cube[1][2][i] = _cube.cube[5][2][i];
        _cube.cube[5][2][i] = _cube.cube[3][2][i];
        _cube.cube[3][2][i] = tmp[i];
    }
    tmp.resize(0);
    _cube.leftwise(2);
}

void cube_sweep::B()
{
    _ans.push_back('B');
    vector<int> tmp = {_cube.cube[3][0][0], _cube.cube[3][1][0], _cube.cube[3][2][0]};
    for (int i = 0; i < 3; i++) {
        _cube.cube[3][i][0] = _cube.cube[4][0][2 - i];
        _cube.cube[4][0][2 - i] = _cube.cube[1][2 - i][2];
        _cube.cube[1][2 - i][2] = _cube.cube[2][2][i];
        _cube.cube[2][2][i] = tmp[i];
    }
    tmp.resize(0);
    _cube.rightwise(5);
}

void cube_sweep::B1()
{
    _ans.push_back('b');
    vector<int> tmp = {_cube.cube[3][0][0], _cube.cube[3][1][0], _cube.cube[3][2][0]};
    for (int i = 0; i < 3; i++) {
        _cube.cube[3][i][0] = _cube.cube[2][2][i];
        _cube.cube[2][2][i] = _cube.cube[1][2 - i][2];
        _cube.cube[1][2 - i][2] = _cube.cube[4][0][2 - i];
        _cube.cube[4][0][2 - i] = tmp[i];
    }
    tmp.resize(0);
    _cube.leftwise(5);
}

void cube_sweep::y()
{
    _ans.push_back('y');
    swap(_cube.cube[0], _cube.cube[1]);
    swap(_cube.cube[5], _cube.cube[1]);
    swap(_cube.cube[5], _cube.cube[3]);
    _cube.rightwise(4);
    _cube.leftwise(2);
}

bool cube_sweep:: operator ==(cube_sweep const&a) const
{
    return a._cube.cube == _cube.cube;
}