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

class CreateProcess {
public:
    int run(bool need_wait, int UID, const std::string& command,
            const std::vector<std::string>& arguments, int *stdout_fd, int *err_fd);
private:

};


#endif //LAB2_SVYAT_CREATE_PROCESS_H
