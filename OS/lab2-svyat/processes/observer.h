//
// Created by vadim on 23.10.20.
//

#ifndef LAB2_SVYAT_OBSERVER_H
#define LAB2_SVYAT_OBSERVER_H

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
#include <kvm.h>
#include <dirent.h>
#include <sys/sysctl.h>
#include <sys/socket.h>
#include <sys/proc.h>
#include <sys/param.h>
#include <libprocstat.h>
#include <sys/user.h>
#include <sys/poll.h>
#include <pthread.h>
#include "logger_wrapper.h"

class Observer {
public:
    Observer();
    void setObserver(Log& logger, int fulenum);
    void setObserver(int PID, Log& logger, int filenum);
    ~Observer();
private:
    struct Arg {
        Log* logger;
        int lognum;
        int PID;
    };
    static void *watch(void* arg);
    std::vector<pthread_t> threads;
};

bool need_watch;


#endif //LAB2_SVYAT_OBSERVER_H