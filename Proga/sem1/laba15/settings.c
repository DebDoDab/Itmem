//
// Created by vadim on 3.12.19.
//

#include <string.h>
#include <stdlib.h>
#include "settings.h"

Settings *setSettings(int argc, char **argv) {
    Settings *settings = (Settings *)malloc(sizeof(Settings));
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--file") == 0) {
            settings->archName = (char *)malloc(sizeof(char) * strlen(argv[++i]));
            strcpy(settings->archName, argv[i]);
        } else if (strcmp(argv[i], "--create") == 0) {
            settings->create = 1;
        } else if (strcmp(argv[i], "--extract") == 0) {
            settings->extract = 1;
        } else if (strcmp(argv[i], "--list") == 0) {
            settings->list = 1;
        } else {
            settings->fileNames[settings->filecount] = (char *)malloc(sizeof(char) * strlen(argv[i]));
            strcpy(settings->fileNames[settings->filecount++], argv[i]);
        }
    }
    return settings;
}