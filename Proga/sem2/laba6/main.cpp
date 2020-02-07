#include <bits/stdc++.h>
#include "functions.h"

using namespace std;

bool foo(int x) {
    return x > 0;
}

int main() {
    vector<int> A = {1, 2, 3};
    set<double> B = {1., 2., 3.};
    cout << allOf(A, foo) << " : " << allOf(B, foo) << "\n";
    cout << anyOf(A, foo) << " : " << anyOf(B, foo) << "\n";
    cout << noneOf(A, foo) << " : " << noneOf(B, foo) << "\n";
    cout << oneOf(A, foo) << " : " << oneOf(B, foo) << "\n";
    cout << isSorted(A, foo) << " : " << isSorted(B, foo) << "\n";
    cout << isPartitioned(A, foo) << " : " << isPartitioned(B, foo) << "\n";
    cout << isPalindrom(A, foo) << " : " << isPalindrom(B, foo) << "\n";
    cout << findNot(A.begin(), A.end(), 1) << " : " << findNot(B.begin(), B.end(), 1) << "\n";
    cout << findBackward(A.begin(), A.end(), 2) << " : " << findBackward(B.begin(), B.end(), 2) << "\n";
    cout << findBackward(A.begin(), A.end(), 5) << " : " << findBackward(B.begin(), B.end(), 5) << "\n";
}
