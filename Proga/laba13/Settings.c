//
// Created by vadim on 12.12.19.
//

#include "Settings.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

Settings *setSettings(int argc, char **argv) {
    Settings *settings = (Settings *)malloc(sizeof(Settings));

    for (int i = 1; i < argc; i++) {
        if (!strcmp("--filepath", argv[i])) {
            settings->fileName = argv[++i];
        } else if (!strcmp("--show", argv[i])) {
            settings->show = 1;
        } else if (!strcmp("--get", argv[i])) {
            settings->get = 1;
            settings->metaName = argv[++i];
        } else if (!strcmp("--set", argv[i])) {
            settings->set = 1;
            settings->metaName = argv[++i];
        } else if (!strcmp("--value", argv[i])) {
            settings->value = argv[++i];
        }
    }

    return settings;
}