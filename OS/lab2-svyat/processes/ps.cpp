//
// Created by vadim on 23.10.20.
//

#include "ps.h"
#include <sstream>
#include <string>
#include <algorithm>
#include <string.h>
#include <list>

string Ps::get_ps() {
    int dir = open("/proc", O_DIRECTORY);
    DIR* proc_dir = fdopendir(dir);

    if (proc_dir == nullptr) {
        exit(0);
    }

    list<string> processes;

    dirent* direct = readdir(proc_dir);
    while (direct != nullptr) {
        string name = direct->d_name;
        if (name != "." && name != ".." && name != "curproc") {
            processes.push_back(name);
        }
        direct = readdir(proc_dir);
    }
    closedir(proc_dir);

    vector<vector<string>> processes_params;
    vector<string> parameters = {"Command name", "Process id",
                                 "Parent process id", "Process group id", "Session id",
                                 "TTY", "Flags", "Start time", "User time",
                                 "System time", "Wait channel", "Group id", "Jail"};
    processes_params.push_back(parameters);

    for (const auto& proc_id : processes) {
        processes_params.push_back(vector<string>());
        string path = "/proc/" + proc_id + "/status";
        int status = open(path.c_str(), O_RDONLY);
        if (status == -1) {
            continue;
        }

        char buffer[200];
        read(status, buffer, 200);
        stringstream parametersStream(buffer);
        string param;
        while (getline(parametersStream, param, ' ')) {
            processes_params.back().push_back(param);
        }
    }

    //output as a table
    string answer;
    vector<int> max_lengths(parameters.size());
    for (int column = 0; column < parameters.size(); column++) {
        max_lengths[column] = 0;
        for (auto& process_param: processes_params) {
            max_lengths[column] = max(max_lengths[column], int(process_param[column].size()));
        }
    }

    for (int row = 0; row < processes_params.size(); row++) {
        for (int column = 0; column < parameters.size(); column++) {
            for (int spaces_count = max_lengths[column] - processes_params[row][column].size(); spaces_count > 0; spaces_count--) {
                answer += " ";
            }
            answer += processes_params[row][column] + "|";
        }
        answer += "\n";
    }

    return answer;
}

int Ps::mount_proc() {
    int res = fork();
    if (res == 0) {
        execl("/sbin/mount", "mount", "-t", "procfs", "proc", "/proc", nullptr);
        exit(-1);
    }
    return 0;
}

void Ps::run(int &stdout_fd) {
    int pipe_fd[2];
    pipe(pipe_fd);
    int child_pid = fork();
    if (child_pid == 0) {
        close(pipe_fd[0]);
        string system_info = get_ps();
        char *sys_info = new char[system_info.size() + 1];
        strcpy(sys_info, system_info.c_str());
        write(pipe_fd[1], sys_info, system_info.size() + 1);
        close(pipe_fd[1]);
        exit(0);
    }
    close(pipe_fd[1]);
    stdout_fd = pipe_fd[0];
}

Ps::Ps() {
    mount_proc();
}