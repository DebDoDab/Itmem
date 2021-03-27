//
// Created by vadim on 7.02.20.
//

template <typename T>
T pow_(const T& x, const int n) {
    T a = x;
    for (int i = 1; i < n; i++) {
        a *= x;
    }
    return a;
}