//
// Created by vadim on 6.03.20.
//

#include "Exceptions.h"

const char *ArgsEsception::what() const _GLIBCXX_NOTHROW {
    return "Incorrect count of arguments.\nArguments format: CompGeomGraphics <input file name>"
           " <output file name> <brightness> <thickness> <x0> <y0> <x1> <y1> [<gamma>].\n";
}

const char *WrongSizeException::what() const _GLIBCXX_NOTHROW {
    return "Wrong image size.\n";
}

const char *WrongFormatException::what() const _GLIBCXX_NOTHROW {
    return "Wrong image size.\n";
}
