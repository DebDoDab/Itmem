//
// Created by vadim on 7.01.21.
//

#ifndef LAB4_EXCEPTIONS_H
#define LAB4_EXCEPTIONS_H

#include "bits/stdc++.h"

class exceptionPE: public std::exception
{
private:
    std::string problem;

public:

    exceptionPE(std::string problem){
        this->problem = std::move(problem);
    }

    const char * what() const noexcept override {
        return problem.c_str();
    }
};

#endif //LAB4_EXCEPTIONS_H
