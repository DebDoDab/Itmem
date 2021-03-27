#include <bits/stdc++.h>
#include "Square.h"
#include "Array.h"

using namespace std;

int main() {
    Square a;
    Square b(1, 2, 3, 4);
    Square c;

    cout << "a "; a.print(); cout << "b "; b.print(); cout << "c "; c.print();
    c = a * 3.14;
    cout << "a "; a.print(); cout << "b "; b.print(); cout << "c "; c.print();
    c = a.operator*(3.14);
    cout << "a "; a.print(); cout << "b "; b.print(); cout << "c "; c.print();
    c = a + make_pair(1, 2);
    cout << "a "; a.print(); cout << "b "; b.print(); cout << "c "; c.print();
    c = a.operator+(make_pair(2, 1));
    cout << "a "; a.print(); cout << "b "; b.print(); cout << "c "; c.print();

    cout << "a == b\t->\t" << (a == b) << " : " << a.operator==(b) << "\n";
    cout << "a != b\t->\t" << (a != b) << " : " << a.operator!=(b) << "\n";
    cout << "a < b\t->\t" << (a < b) << " : " << a.operator<(b) << "\n";
    cout << "a > b\t->\t" << (a > b) << " : " << a.operator>(b) << "\n";


    cout << "\n\n\n";


    Array d;
    Array e({1, 2, 3, 4, 5});
    Array f;

    cout << "d "; d.print(); cout << "e "; e.print(); cout << "f "; f.print();
    f = d + e;
    cout << "d "; d.print(); cout << "e "; e.print(); cout << "f "; f.print();


    cout << "d == e\t->\t" << (d == e) << " : " << d.operator==(e) << "\n";
    cout << "d != e\t->\t" << (d != e) << " : " << d.operator!=(e) << "\n";
    cout << "d < e\t->\t" << (d < e) << " : " << d.operator<(e) << "\n";
    cout << "d > e\t->\t" << (d > e) << " : " << d.operator>(e) << "\n";
}
