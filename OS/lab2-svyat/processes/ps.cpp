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
