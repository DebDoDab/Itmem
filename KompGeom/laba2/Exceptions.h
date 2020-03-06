//
// Created by vadim on 6.03.20.
//
#include <bits/stdc++.h>

using namespace std;

#ifndef LABA2_EXCEPTIONS_H
#define LABA2_EXCEPTIONS_H


class ArgsEsception: public exception {
    const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

class WrongSizeException : public exception {
    const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

class WrongFormatException : public exception {
    const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

#endif //LABA2_EXCEPTIONS_H
