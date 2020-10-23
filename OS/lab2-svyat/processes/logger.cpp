//
// Created by vadim on 23.10.20.
//

#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <string>
#include <vector>
#include <unordered_set>


volatile bool newEvent = false;
bool finish = false;
int *last_shm_memory;
void sighandler(int number) {
    newEvent = true;
}

void terminator(int number) {
    finish = true;
}


struct LogObject {
    std::string shm_name;
    std::string file_name;
    int fd;
    void* memory;
};
std::vector<LogObject> logs;

int main(int argc, char** argv) {
    signal(SIGUSR1, sighandler);
    signal(SIGTERM, terminator);
    const int LAST_SIZE = 8;
    const int NAMES_SIZE = 1024;
    const char* namesMemory = "/LOG_NAMES";
    const char* lastMemory = "/LOG_LAST";
    const char* baseName = "/LOG_";
    char lineBuffer[1024];
    int last_shm_fd, names_shm_fd;
    char *names_shm_memory;
    int self_log = open("self.log",O_CREAT | O_TRUNC | O_APPEND | O_WRONLY, 0777);
    close(0);
    close(2);
    last_shm_fd = shm_open(lastMemory, O_CREAT | O_RDWR, 0666);
    write(self_log, "INIT ", 5);
    ftruncate(last_shm_fd, LAST_SIZE);
    last_shm_memory = (int*)mmap(0, LAST_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, last_shm_fd, 0);
    names_shm_fd = shm_open(namesMemory, O_CREAT | O_RDWR, 0666);
    ftruncate(names_shm_fd, NAMES_SIZE);
    names_shm_memory = (char*)mmap(0, NAMES_SIZE, PROT_READ, MAP_SHARED, names_shm_fd, 0);

    logs.clear();
    std::string names(strcpy(lineBuffer, names_shm_memory));
    std::vector<std::string> name;
    size_t position = 0;
    while (position != std::string::npos) {
        std::string buffer;
        write(self_log, "NAME_LOOP ", 10);
        buffer = names.substr(position, names.find('\n', position) - position);
        if (!buffer.empty())
            name.push_back(buffer);
        position = names.find('\n', position) + 1;
        if(position >= names.size())
            break;
    }
    shm_unlink(namesMemory);
    std::unordered_set<std::string> opened_files;
    for (int i = 0; i < name.size(); i++) {
        int fd = open(name[i].c_str(), O_CREAT | O_TRUNC | O_APPEND | O_WRONLY, 0777);
        LogObject buffer;
        buffer.file_name = name[i];
        buffer.fd = fd;
        void* memory;
        std::string shm_name(baseName);
        int shm_fd;
        shm_fd = shm_open((shm_name + std::to_string(i + 1)).c_str(), O_CREAT | O_RDWR, 0666);
        buffer.shm_name = shm_name + std::to_string(i + 1);
        ftruncate(shm_fd, 1024);
        memory = mmap(0, 1024, PROT_READ, MAP_SHARED, shm_fd, 0);
        buffer.memory = memory;
        opened_files.insert(buffer.file_name);
        logs.push_back(buffer);
    }
    write(self_log, "INITEND ", 8);
    while (signal(SIGUSR1, sighandler)!= sighandler) {

    }
    int f_res = fork();
    if (f_res != 0) {
        write(1, &f_res, 4);
        return 0;
    }
    close(1);
    setsid();
    while (true) {
        if (newEvent) {
            write(self_log, "GOOD LOOP ", 10);
            int eventNumber = *last_shm_memory;

            write(self_log, "LAST ", 5);
            if (eventNumber == 0) {
                *last_shm_memory = 255;
                newEvent = false;
                continue;
            }
            LogObject buffer = logs[eventNumber - 1];
            char line[1000];
            write(self_log, "BEFOR MEM ", 10);
            memcpy(line, (char*)buffer.memory, 1000);
            write(buffer.fd, line, strlen(line));
            *last_shm_memory = 0;
            newEvent = false;
        }
        if (finish) {
            shm_unlink("/LOG_LAST");
            write(self_log, "FIN LOOP ", 9);
            for (auto & log : logs) {
                close(log.fd);
                shm_unlink(log.shm_name.c_str());
            }
            return 0;
        }
        pause();
    }
}