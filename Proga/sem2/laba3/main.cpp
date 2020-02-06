#include <iostream>
#include "Matrix.h"
using namespace std;

int main() {
    Matrix a({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix b({{3, 2, 1}, {6, 5, 4}, {9, 8, 7}});
    Matrix c;
    cout << "a "; a.print(); cout << "b "; b.print(); cout << "c "; c.print();
    c = a * b;
    cout << "a "; a.print(); cout << "b "; b.print(); cout << "c "; c.print();
    c = a + b;
    cout << "a "; a.print(); cout << "b "; b.print(); cout << "c "; c.print();
    c = a - b;
    cout << "a "; a.print(); cout << "b "; b.print(); cout << "c "; c.print();

    cout << "a == b\t->\t" << (a == b) << "\n";
    cout << "a != b\t->\t" << (a != b) << "\n";
    cout << "a < b\t->\t" << (a < b) << "\n";
    cout << "a > b\t->\t" << (a > b) << "\n";
}
