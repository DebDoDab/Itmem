#include <bits/stdc++.h>
#include "functional.h"
using namespace std;

int main() {
    float a = 3.123, b = 4.1234;
//    cin >> a >> b;

    floor_(a); cout << a << "\t";
    floor_(&b); cout << b << "\n\n";


    a = -3.123;
//    cin >> a;
    int c = -3;
//    cin >> c;

    inv(a); cout << a << "\t";
    inv(&a); cout << a << "\t\t";
    inv(c); cout << c << "\t";
    inv(&c); cout << c << "\n\n";


    float r = 3.1, x = 1.2, y = 2.3;
//    cin >> r >> x >> y;
    Circle d = Circle(r, x, y);
    float delta_x = 0.1, delta_y = 0.2;
//    cin >> delta_x >> delta_y;

    d.print();
    move(d, delta_x, delta_y);
    d.print();
    move(&d, &delta_x, &delta_y);
    d.print();


    Matrix e = Matrix();
    int delta = 3;
//    cin >> delta;

    e.print();
    mult(e, delta);
    e.print();
    mult(&e, &delta);
    e.print();

}
