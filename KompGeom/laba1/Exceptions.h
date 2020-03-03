//
// Created by vadim on 22.02.20.
//

#include <bits/stdc++.h>
using namespace std;

#ifndef LABA1_EXCEPTIONS_H
#define LABA1_EXCEPTIONS_H

class WrongFormat : public exception {
public:
    const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW;
};

class WrongCommand : public exception {
public:
    const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW;
};

class WrongSize : public exception {
public:
    const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW;
};

class WrongFile : public exception {
public:
    const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW;
};

#endif //LABA1_EXCEPTIONS_H
