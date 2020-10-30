//
// Created by vadim on 23.10.20.
//

#include <sstream>
#include "create_process.h"



int CreateProcess::run(bool foreground, int UID, const string& command, const string& arguments, int& stdout_fd, int& err_fd) {
    int pipe_fd[2];
    int pipe_err[2];
    int pipe_return[2];
    pipe(pipe_fd);
    pipe(pipe_return);
    pipe(pipe_err);
    int child_pid = fork();
    if (child_pid == 0) {
        close(pipe_fd[0]);
        close(pipe_return[0]);
        close(pipe_err[0]);

        write(pipe_err[1], " ", 1);
        int grand_child_pid = fork();
        if (grand_child_pid == 0) {
            setuid(UID);
            char* argv[10];
            argv[0] = (char*)command.c_str();
            stringstream argumentsStream(arguments);
            int i = 1;
            string arg;
            while (i < 10 && getline(argumentsStream, arg, ' ')) {
                argv[i++] = (char *)arg.c_str();
            }
            while (i < 10) {
                argv[i++] = nullptr;
            }
            int result = execvp(command.c_str(), argv);
            if (result != 0) {
                exit(-1);
            }
        }
        int code;
        if (foreground) {
            wait(&code);
            code = WEXITSTATUS(code);
            write(pipe_return[1], &code, 8);
        }
        close(pipe_fd[1]);
        close(pipe_return[1]);
        close(pipe_err[1]);
        exit(0);
    }
    int code;
    close(pipe_fd[1]);
    close(pipe_return[1]);
    close(pipe_err[1]);
    if (foreground) {
        read(pipe_return[0], &code, 8);
    }
    stdout_fd = pipe_fd[0];
    err_fd = pipe_err[0];
    if (foreground) {
        return code;
    } else {
        return 0;
    }
}
