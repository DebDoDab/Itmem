//
// Created by vadim on 12.12.19.
//

#ifndef LABA15_SETTINGS_H
#define LABA15_SETTINGS_H

#pragma pack(push, 1)
typedef struct tagSettings {
    char *fileName;
    char show;
    char get;
    char set;
    char *metaName;
    char *value;
} Settings;
#pragma pack(pop)

Settings *setSettings(int argc, char **argv);

#endif //LABA15_SETTINGS_H
