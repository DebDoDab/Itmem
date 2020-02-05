//
// Created by vadim on 3.12.19.
//

#ifndef LABA15_SETTINGS_H
#define LABA15_SETTINGS_H

#pragma pack(push, 1)
typedef struct tagSettings {
    char *archName;
    char create;
    char extract;
    char list;
    int filecount;
    char *fileNames[1000];
} Settings;
#pragma pack(pop)

Settings *setSettings(int argc, char **argv);

#endif //LABA15_SETTINGS_H
