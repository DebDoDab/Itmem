//
// Created by vadim on 3.12.19.
//

#include "arch.h"
#include "settings.h"
#include <stdio.h>
#include <stdlib.h>

Arch *readArch(Settings *settings) {
    FILE *input = fopen(settings->archName, "r");
    Arch *arch = (Arch *)malloc(sizeof(Arch));
    fread(&arch->fileCount, sizeof(arch->fileCount), 1, input);
    arch->files = (File **)malloc(sizeof(File *) * arch->fileCount);
    for (int i = 0; i < arch->fileCount; i++) {
        arch->files[i] = (File *)malloc(sizeof(File));
        fread(&arch->files[i]->nameSize, sizeof(arch->files[i]->nameSize), 1, input);
        arch->files[i]->name = (char *)malloc(sizeof(char) * arch->files[i]->nameSize);
        fread(arch->files[i]->name, arch->files[i]->nameSize, 1, input);
        fread(&arch->files[i]->dataSize, sizeof(arch->files[i]->dataSize), 1, input);
        arch->files[i]->data = (char *)malloc(sizeof(char) * arch->files[i]->dataSize);
        fread(arch->files[i]->data, arch->files[i]->dataSize, 1, input);
    }
    return arch;
}

void create(Settings *settings) {
    Arch *arch = malloc(sizeof(Arch));
    arch->fileCount = settings->filecount;
    arch->files = malloc(sizeof(File *) * arch->fileCount);
    for (int i = 0; i < arch->fileCount; i++) {
        arch->files[i] = malloc(sizeof(File));
        arch->files[i] = readFile(settings->fileNames[i]);
    }

    FILE *output = fopen(settings->archName, "w");
    fwrite(&arch->fileCount, sizeof(arch->fileCount), 1, output);
    for (int i = 0; i < arch->fileCount; i++) {
        fwrite(&arch->files[i]->nameSize, sizeof(arch->files[i]->nameSize), 1, output);
        fwrite(arch->files[i]->name, arch->files[i]->nameSize, 1, output);
        fwrite(&arch->files[i]->dataSize, sizeof(arch->files[i]->dataSize), 1, output);
        fwrite(arch->files[i]->data, arch->files[i]->dataSize, 1, output);
    }
    fclose(output);
}

void extract(Settings *settings) {
    Arch *arch = readArch(settings);
    for (int i = 0; i < arch->fileCount; i++) {
        writeFile(arch->files[i]);
    }
}

void list(Settings *settings) {
    Arch *arch = readArch(settings);
    for (int i = 0; i < arch->fileCount; i++) {
        printf("%s ", arch->files[i]->name);
    }
    printf("\n");
}
