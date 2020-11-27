//
// Created by vadim on 23.10.20.
//

#ifndef LAB2_SVYAT_SYSTEM_INFO_H
#define LAB2_SVYAT_SYSTEM_INFO_H

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

using namespace std;

class System_info {
public:
    void run(int& stdout_fd);
    string get_system_info();
};


#endif //LAB2_SVYAT_SYSTEM_INFO_H
