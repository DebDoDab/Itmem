#include <bits/stdc++.h>
#include "functions.h"
#include "classes.h"

using namespace std;

int main() {
    int a = 3;
    double b = 1.2;
    cout << pow_(a, 3) << " : ";
    cout << pow_(b, 3) << " : ";
    cout << pow_(3.2, 2) << "\n";

    Matrix<int> x(3, 2);
    try {
        cout << x.get(1, 1) << "\n";
    } catch (const exception& ex) {
        cout << "Exception caught: " << ex.what() << endl;
    }

    try {
        cout << x.get(3, 3) << "\n";
    } catch (const exception& ex) {
        cout << "Exception caught: " << ex.what() << endl;
    }
}
