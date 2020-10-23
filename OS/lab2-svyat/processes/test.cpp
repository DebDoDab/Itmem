//
// Created by vadim on 23.10.20.
//

#include "system_info.h"
#include "ps.h"
#include <iostream>


int main() {
    auto * ps = new Ps();
    cout << ps->get_ps() << endl;
}
