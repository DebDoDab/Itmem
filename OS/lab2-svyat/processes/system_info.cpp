//
// Created by vadim on 23.10.20.
//

#include "system_info.h"

string System_info::get_system_info() {
    std::string result, string_buffer;
    int buffer_num;
    char buffer[100];
    size_t len = sizeof(buffer);
    size_t num_len = sizeof(int);

    int parameters[] = {CTL_HW, HW_MACHINE};
    sysctl(parameters, 2, buffer, &len, nullptr, 0);
    string_buffer = buffer;
    result = "Machine type: " + string_buffer + "\n";

    parameters[1] = HW_MODEL;
    sysctl(parameters, 2, buffer, &len, nullptr, 0);
    string_buffer = buffer;
    result += "Machine model: " + string_buffer + "\n";

    parameters[1] = HW_MACHINE_ARCH;
    sysctl(parameters, 2, buffer, &len, nullptr, 0);
    string_buffer = buffer;
    result += "Machine architecture: " + string_buffer + "\n";

    parameters[1] = HW_PHYSMEM;
    sysctl(parameters, 2, &buffer_num, &num_len, nullptr, 0);
    result += "Physical memory: " + std::to_string(buffer_num) + " bytes\n";

    parameters[1] = HW_PAGESIZE;
    sysctl(parameters, 2, &buffer_num, &num_len, nullptr, 0);
    result += "Memory page size: " + std::to_string(buffer_num) + " bytes\n";
    return result;
}

void System_info::run(int& stdout_fd) {
    int pipe_fd[2];
    pipe(pipe_fd);
    int child_pid = fork();
    if (child_pid == 0) {
        close(pipe_fd[0]);
        string system_info = get_system_info();
        char *sys_info = new char[system_info.size() + 1];
        strcpy(sys_info, system_info.c_str());
        write(pipe_fd[1], sys_info, system_info.size() + 1);
        close(pipe_fd[1]);
        exit(0);
    }
    close(pipe_fd[1]);
    stdout_fd = pipe_fd[0];
}
