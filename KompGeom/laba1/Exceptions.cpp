//
// Created by vadim on 22.02.20.
//

#include "Exceptions.h"

const char *WrongSize::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {
    return "Wrong size of image\nCheck if image is correct";
}

const char *WrongCommand::what() const _GLIBCXX_NOTHROW {
    return "Wrong command\n";
}

const char *WrongFormat::what() const _GLIBCXX_NOTHROW {
    return "Wrong image format\n";
}

const char *WrongFile::what() const _GLIBCXX_NOTHROW {
    return "Wrong file name\n";
}
