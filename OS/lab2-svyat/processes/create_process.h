//
// Created by vadim on 23.10.20.
//

#ifndef LAB2_SVYAT_CREATE_PROCESS_H
#define LAB2_SVYAT_CREATE_PROCESS_H

#include <unistd.h>
#include <string>
#include <stdio.h>
#include <sys/wait.h>
#include <vector>

using namespace std;

class CreateProcess {
public:
    int run(bool foreground, int UID, const string& command, const string& arguments, int& stdout_fd, int& err_fd);
private:

};


#endif //LAB2_SVYAT_CREATE_PROCESS_H
