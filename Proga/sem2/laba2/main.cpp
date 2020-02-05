#include <iostream>
#include "SquarePolynomial.h"
using namespace std;

int main() {
    Polynom x = Polynom("123.124679234*x^2 -3* x");
    x.print();
    Polynom y = Polynom("123");
    y.print();
}
