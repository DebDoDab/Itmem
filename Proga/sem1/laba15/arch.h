//
// Created by vadim on 3.12.19.
//

#ifndef LABA15_ARCH_H
#define LABA15_ARCH_H

#include "files.h"

#include "settings.h"

#pragma pack(push, 1)
typedef struct tagArch {
    int fileCount;
    File **files;
} Arch;
#pragma pack(pop)

Arch *readArch(Settings *settings);
void create(Settings *settings);
void extract(Settings *settings);
void list(Settings *settings);

#endif //LABA15_ARCH_H
