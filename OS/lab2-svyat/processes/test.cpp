//
// Created by vadim on 23.10.20.
//

#include "create_process.h"
#include <iostream>


int main() {
    auto create_process = new CreateProcess();
    int fd, err;
    int result = create_process->run(true, 228228, "ps", {}, &fd, &err);
    char buffer_out[100] = {};
    char buffer_err[100] = {};
    std::string out, erro, buff;
    while (read(fd, buffer_out, 100) != 0)
    {
        buff = buffer_out;
        out += buff;
        read(fd, buffer_out, 100);
    }
    while(read(err, buffer_err, 100) != 0)
    {
        buff = buffer_err;
        erro += buff;
        read(err, buffer_out, 100);
    }
    //printf("%d %.100s\n", result,  buffer);
    printf("ERR: %s\nSTDOUT: %s\n", erro.c_str(), out.c_str());
    printf("Exit code: %d\n", result);
    return result;
}
