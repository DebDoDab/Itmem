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
    if (arguments->PID == -1) {
        int dir = open("/proc", O_DIRECTORY);
        std::set<std::string> processes_last, processes_new;
        std::vector<std::string> created_processes, died_processes;

        DIR* procdir = fdopendir(dir);
        if (procdir == nullptr) {
            exit(0);
        }
        dirent* direct = readdir(procdir);
        while (direct != nullptr) {
            std::string name = direct->d_name;
            if (name != "." && name != ".." && name != "curproc") {
                processes_last.insert(name);
            }
            direct = readdir(procdir);
        }
        closedir(procdir);

        dir = open("/proc", O_DIRECTORY);
        procdir = fdopendir(dir);
        while (need_watch) {
            direct = readdir(procdir);
            while (direct != nullptr) {
                std::string name = direct->d_name;
                if (name != "." && name != ".." && name != "curproc") {
                    processes_new.insert(name);
                    if (processes_last.find(name) != processes_last.end()) {
                        created_processes.emplace_back(name);
                    }
                }
                direct = readdir(procdir);
            }
            for (const auto& process : processes_last) {
                if (processes_new.find(process) != processes_new.end()) {
                    died_processes.emplace_back(process);
                }
            }


            if (!created_processes.empty()) {
                std::string message = "\nCreated process:\n";
                for (const auto& process : created_processes) {
                    message+="\t";
                    message+=process;
                    message+="\n";
                }
                arguments->logger->write_message(message, arguments->lognum);
            }

            if (!died_processes.empty()) {
                std::string message = "\nDied process:\n";
                for (const auto& process : processes_last) {
                    message+="\t";
                    message+=process;
                    message+="\n";
                }
                arguments->logger->write_message(message, arguments->lognum);
            }
            died_processes.clear();
            created_processes.clear();
            processes_new.clear();
        }
    } else {
        std::string path = "/proc/" + std::to_string(arguments->PID) + "/status";
        int status = open(path.c_str(), O_RDONLY);
        if (status == -1) {
            exit(-1);
        }
        std::string last_val, new_val;
        char buffer[200];
        read(status, buffer, 200);
        last_val = buffer;
        while (need_watch) {
            std::string parameters[] = {"Command name", "Process id",
                                        "Parent process id", "Process group id", "Session id",
                                        "TTY", "Flags", "Start time", "User time",
                                        "System time", "Wait channel", "Group id",
                                        "Jail"};
            int result = read(status, buffer, 200);
            new_val = buffer;
            if (result == -1) {
                arguments->logger->write_message("PROCESS " + std::to_string(arguments->PID) + " TERMINATED\n", arguments->lognum);
                exit(0);
            }

            if (new_val != last_val) {
                int argnum = 0;
                int last_arg_start_index = 0;
                for (int i = 0; i < new_val.size() && i < last_val.size(); i++) {
                    if (new_val[i] == last_val[i]) {
                        if (new_val[i] == ' ') {
                            argnum++;
                            last_arg_start_index = i + 1;
                        }
                    } else {
                        break;
                    }
                }
                int changed_arg_end_index = new_val.find(' ', last_arg_start_index);
                if (changed_arg_end_index == -1) {
                    changed_arg_end_index = new_val.size();
                }
                std::string new_arg_value = new_val.substr(last_arg_start_index, changed_arg_end_index - last_arg_start_index);
                arguments->logger->write_message( "Parameter \"" + parameters[argnum] + "\" new value is: " + new_arg_value + "\n" , arguments->lognum);
            }
            lseek(status, 0, SEEK_SET);
            last_val = new_val;
        }
    }
    exit(0);
}

Observer::~Observer() {
    need_watch = false;
    for (auto thread : threads) {
        pthread_join(thread, nullptr);
    }
}