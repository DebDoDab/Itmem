//
// Created by vadim on 23.10.20.
//

#include "ps.h"

string Ps::get_ps() {
    mount_proc();
    int dir = open("/proc", O_DIRECTORY);
    DIR* procdir = fdopendir(dir);
    set<string> processes_last;
    if (procdir == nullptr) {
        exit(0);
    }
    dirent* direct = readdir(procdir);
    while (direct != nullptr) {
        string name = direct->d_name;
        if (name != "." && name != ".." && name != "curproc") {
            processes_last.insert(name);
        }
        direct = readdir(procdir);
    }
    closedir(procdir);
    string answer;
    string parameters[] = {"Command name", "Process id",
                           "Parent process id", "Process group id", "Session id",
                           "TTY", "Flags", "Start time", "User time",
                           "System time", "Wait channel", "Gpoup id",
                           "Jail"};
    for (const auto& parameter : parameters) {
        answer += parameter + "\t";
    }
    for (const auto& proc_id : processes_last) {
        string path = "/proc/" + proc_id + "/status";
        int status = open(path.c_str(), O_RDONLY);
        if (status == -1) {
            continue;
        }
        char buffer[200];
        read(status, buffer, 200);
        answer += buffer;
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
