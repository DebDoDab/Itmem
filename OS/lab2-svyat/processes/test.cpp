//
// Created by vadim on 23.10.20.
//

#include "system_info.h"
#include <iostream>


int main() {
    auto * system_info = new System_info();
    std::cout << system_info->get_system_info() << "\n";
}
