//
// Created by vadim on 3.12.19.
//

#ifndef LABA15_FILES_H
#define LABA15_FILES_H

#pragma pack(push, 1)
typedef struct tagFile {
    int nameSize;
    char *name;
    int dataSize;
    char *data;
} File;
#pragma pack(pop)

File *readFile(char *name);
void writeFile(File *file);

#endif //LABA15_FILES_H
