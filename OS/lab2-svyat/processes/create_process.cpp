//
// Created by vadim on 23.10.20.
//

#include <sstream>
#include "create_process.h"
#include <string>
#include <string.h>



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
        dup2(pipe_fd[1], STDOUT_FILENO);
        dup2(pipe_err[1], STDERR_FILENO);

        int grand_child_pid = fork();
        if (grand_child_pid == 0) {
            setuid(UID);
            char* argv[10];
            argv[0] = new char[command.size() + 1];
            strcpy(argv[0], command.c_str());
            stringstream argumentsStream(arguments);
            int i = 1;
            string arg;
            while (i < 10 && getline(argumentsStream, arg, ' ')) {
                argv[i] = new char[arg.size() + 1];
                strcpy(argv[i], arg.c_str());
                i++;
            }
            while (i < 10) {
                argv[i++] = nullptr;
            }
            int result = execvp(command.c_str(), argv);
            if (result != 0) {
                fprintf(STDERR_FILENO, "%s\n", explain_execvp(command.c_str(), argv));
            }
        }
        int code;
        if (foreground) {
            wait(&code);
            code = WEXITSTATUS(code);
            write(pipe_return[1], &code, 8);
        }
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
