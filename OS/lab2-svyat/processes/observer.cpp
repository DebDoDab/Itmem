//
// Created by vadim on 23.10.20.
//

#include <dirent.h>
#include <set>
#include <sys/event.h>
#include "observer.h"

Observer::Observer() {
    int res = fork();
    need_watch = true;
    if (res == 0) {
        execl("/sbin/mount", "mount", "-t", "procfs", "proc", "/proc", nullptr);
        exit(-1);
    }
    wait(nullptr);
}

void Observer::setObserver(Log& logger, int filenum) {
    pthread_t thread;
    static Arg arguments = {&logger, filenum, -1};
    int new_thread = pthread_create(&thread, nullptr, watch, &arguments);
    if (new_thread != 0) {
        return;
    }
    threads.push_back(thread);
}

void Observer::setObserver(int PID, Log& logger, int filenum) {
    pthread_t thread;
    static Arg arguments = {&logger, filenum, PID};
    int new_thread = pthread_create(&thread, nullptr, watch, &arguments);
    if(new_thread != 0) {
        return;
    }
    threads.push_back(thread);
}

void *Observer::watch(void* arg) {
    Arg* arguments = (Arg*)arg;
    if(arguments->PID == -1) {
        int dir = open("/proc", O_DIRECTORY);
        DIR* procdir = fdopendir(dir);
        std::set<std::string> processes_last, processes_new, processes_last_buffer, processes_new_buffer;
        if (procdir == nullptr) {
            exit(0);
        }
        dirent* direct = readdir(procdir);
        while(direct != nullptr) {
            std::string name = direct->d_name;
            if ((name != ".")&&(name != "..")&&(name != "curproc")) {
                processes_last.insert(name);
            }
            direct = readdir(procdir);
        }
        closedir(procdir);
        dir = open("/proc", O_DIRECTORY);
        procdir = fdopendir(dir);
        while(need_watch) {
            direct = readdir(procdir);
            while(direct != nullptr) {
                std::string name = direct->d_name;
                if ((name != ".")&&(name != "..")&&(name != "curproc")) {
                    processes_new.insert(name);
                }
                direct = readdir(procdir);
            }
            closedir(procdir);
            dir = open("/proc", O_DIRECTORY);
            procdir = fdopendir(dir);
            processes_new_buffer = processes_new;
            processes_last_buffer = processes_last;
            for (const auto& process : processes_last) {
                if (processes_new.find(process) != processes_new.end()) {
                    processes_new.erase(processes_new.find(process));
                }
            }
            if (!processes_new.empty()) {
                if (!processes_new.empty()) {
                    std::string message = "\nNew process:\n";
                    for (const auto& process : processes_new) {
                        message+="\t";
                        message+=process;
                        message+="\n";
                    }
                    arguments->logger->write_message(message, arguments->lognum);
                }
            }
            processes_new = processes_new_buffer;
            processes_last = processes_last_buffer;
            for (const auto& process : processes_new) {
                if (processes_last.find(process) != processes_last.end()) {
                    processes_last.erase(processes_last.find(process));
                }
            }
            if (!processes_last.empty()) {
                if (!processes_last.empty()) {
                    std::string message = "\nDied process:\n";
                    for (const auto& process : processes_last) {
                        message+="\t";
                        message+=process;
                        message+="\n";
                    }
                    arguments->logger->write_message(message, arguments->lognum);
                }
            }
            processes_last = processes_new_buffer;
            processes_new.clear();
            processes_new_buffer.clear();
            processes_last_buffer.clear();
        }
    } else {
        std::string path;
        path = "/proc/" + std::to_string(arguments->PID) + "/status";
        int status = open(path.c_str(), O_RDONLY);
        if (status == -1) {
            exit(-1);
        }
        std::string last_val, new_val, last_val_buff, new_val_buff;
        char buffer[200];
        read(status, buffer, 200);
        last_val = buffer;
        while (need_watch) {
            std::string parameters[] = {"Command name", "Process id",
                                        "Parent process id", "Process group id", "Session id",
                                        "TTY", "Flags", "Start time", "User time",
                                        "System time", "Wait channel", "Gpoup id",
                                        "Jail"};
            int result = read(status, buffer, 200);
            new_val = buffer;
            if (result == -1) {
                arguments->logger->write_message("PROCESS " + std::to_string(arguments->PID) + " TERMINATED\n", arguments->lognum);
                exit(0);
            }
            last_val_buff = last_val;
            new_val_buff = new_val;
            if (new_val != last_val) {
                int argnum = 0;
                int min_len = std::min(new_val.size(), last_val.size());
                for (int i = 0; i < min_len; i++) {
                    if (new_val[0] == last_val[0]) {
                        if (new_val[0] == ' ') {
                            argnum++;
                        }
                        new_val.erase(0, 1);
                        last_val.erase(0, 1);
                    } else {
                        break;
                    }
                }
                new_val = new_val.substr(0, new_val.find(' '));
                arguments->logger->write_message( "Parameter \"" + parameters[argnum] + "\" new value is: " + new_val + "\n" , arguments->lognum);
            }
            lseek(status, 0, SEEK_SET);
            last_val = new_val_buff;
        }
    }
    exit(0);
    return nullptr;
}

Observer::~Observer() {
    need_watch = false;
    for (auto thread : threads) {
        pthread_join(thread, nullptr);
    }
}