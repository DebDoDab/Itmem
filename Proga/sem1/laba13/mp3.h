//
// Created by vadim on 12.12.19.
//

#ifndef LABA13_MP3_H
#define LABA13_MP3_H

#import "Settings.h"
#import <stdlib.h>
#import <stdio.h>

typedef union tagTAGHEADER
{
    char buffer[12];                  // 12 total

    struct {
        unsigned short  empty;        // 2
        unsigned char   version[3];   // 3
        unsigned char   v1;           // 1
        unsigned char   v2;           // 1
        unsigned char   flags;        // 1
        unsigned int    size;         // 4
    } data;
} TAGHEADER;

typedef union tagFRAMEHEADER
{
    char buffer[10];                  // 10 total

    struct {
        unsigned char   name[4];      // 4
        unsigned int    size;         // 4
        unsigned short  flags;        // 2
    } data;
} FRAMEHEADER;

typedef struct tagMP3 {
    FILE *file;
    unsigned int tagSize;
    TAGHEADER *tagHeader;
    char frameName[4];
} MP3;

void show(Settings *settings);
void get(Settings *settings);
void set(Settings *settings);

#endif //LABA13_MP3_H
