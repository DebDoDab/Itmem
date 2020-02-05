//
// Created by vadim on 3.12.19.
//

#include "files.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

File *readFile(char *name) {
    File *file = (File *)malloc(sizeof(File));
    file->nameSize = strlen(name) + 1;
    file->name = (char *)malloc(sizeof(char) * file->nameSize);
    strcpy(file->name, name);
    FILE *input = fopen(name, "r");
    fseek(input, 0, SEEK_END);
    file->dataSize = ftell(input);
    fseek(input, 0, SEEK_SET);
    file->data = (char *)malloc(sizeof(char) * file->dataSize);
    fread(file->data, file->dataSize, 1, input);
    fclose(input);
    return file;
}

void writeFile(File *file) {
    FILE *output = fopen(file->name, "w");
    fwrite(file->data, file->dataSize, 1, output);
    fclose(output);
}