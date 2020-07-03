//
// Created by vadim on 6.03.20.
//
#include <bits/stdc++.h>

using namespace std;

#ifndef LABA3_1_EXCEPTIONS_H
#define LABA3_1_EXCEPTIONS_H


class ArgsException: public exception {
    const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

class WrongSizeException : public exception {
    const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

class WrongFormatException : public exception {
    const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

#endif //LABA3_1_EXCEPTIONS_H
