//
// Created by vadim on 18.03.20.
//
#include "classes.h"

const char *OutOfRangeException::what() const _GLIBCXX_NOTHROW {
    return exception::what();
}
