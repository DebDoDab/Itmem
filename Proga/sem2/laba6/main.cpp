#include <bits/stdc++.h>
#include "functions.h"

using namespace std;

bool foo(int x) {
    return x > 0;
}

bool bar(double x) {
    return x < 0;
}

bool lessInt(int x, int y) {
    return x < y;
}

bool lessDouble(double x, double y) {
    return x > y;
}

int main() {
    vector<int> A = {-2, 1, -3};
    set<double> B = {-2.5, -2.3, 3};

    cout << "allOf\t\t\t" << allOf(A, foo) << " : " << allOf(B, bar) << "\n";

    cout << "anyOf\t\t\t" << anyOf(A, foo) << " : " << anyOf(B, bar) << "\n";

    cout << "noneOf\t\t\t" << noneOf(A, foo) << " : " << noneOf(B, bar) << "\n";

    cout << "oneOf\t\t\t" << oneOf(A, foo) << " : " << oneOf(B, bar) << "\n";

    cout << "isSorted\t\t" << isSorted(A.begin(), A.end(), lessInt) << " : "
         << isSorted(B.rbegin(), B.rend(), lessDouble) << "\n";

    cout << "isPartitioned\t" << isPartitioned(A, foo) << " : " << isPartitioned(B, bar) << "\n";

    cout << "isPalindrome\t" << isPalindrome(A, foo) << " : " << isPalindrome(B, bar) << "\n";

    cout << "findNot\t\t\t" << findNot(A.begin(), A.end(), 1) << " : "
         << findNot(B.begin(), B.end(), 1.5) << "\n";

    cout << "findBackward\t" << findBackward(A.begin(), A.end(), 2) << " : "
         << findBackward(B.begin(), B.end(), -2.5) << "\n";

    cout << "findBackward\t" << findBackward(A.begin(), A.end(), 5) << " : "
         << findBackward(B.begin(), B.end(), 5.0) << "\n";
}
