#include <iostream>
#include "SquarePolynomial.h"
using namespace std;

int main() {
    for (int i = 0; i < 5; i++) {
        cout << "Enter polynom\n";
        string s;
        getline(cin, s);
        Polynom x = Polynom(s);
        x.print();
        float solveCoordinate = 2;
        cout << "x = " << solveCoordinate << ", y = " << x.solve(solveCoordinate) << "\n";

        cout << "Roots quantity = " << x.solveCount() << "\n";

        auto p = x.solve();
        cout << "Roots: ";
        for (auto &ans : p) {
            cout << ans << ", ";
        }
        cout << "\n";

        cout << "min = " << x.findMin() << "\n" << "max = " << x.findMax() << "\n";
    }

}
