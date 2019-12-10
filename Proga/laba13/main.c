//
// Created by Dmitry Kulazhenko on 2018-11-10.
//

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

void getSongFileName(int argc, char * argv[], char *fileName)
{
    int j = 0, i;
    for(i = 11; i < strlen(argv[1]); i++)
        fileName[j++] = argv[1][i];
    fileName[j] = '\0';
}

void getFrameIdFromARGV(char **argv, char *frameId)
{
    if(strlen(argv[2]) != 10)
    {
        puts("Incorrect frameId. Frame ID should have 4 char");
        return;
    }
    if(notCorrectSimbolOfIdTag(argv[2][6]) || notCorrectSimbolOfIdTag(argv[2][7]) ||
       notCorrectSimbolOfIdTag(argv[2][8]) || notCorrectSimbolOfIdTag(argv[2][9]))
    {
        puts("Incorrect frameId. Frame ID should be only of char 'A' - 'Z' and '0' - '9'");
    }
    frameId[0] = argv[2][6];
    frameId[1] = argv[2][7];
    frameId[2] = argv[2][8];
    frameId[3] = argv[2][9];
    frameId[4] = '\0';
}

void getFrameTextFromARGV(char **argv, char *frameText)
{
    int len = strlen(argv[3]);
    if(len < 9)
    {
        puts("Bad value, length should be more");
        return;
    }
    int i;
    for(i = 8; i < len; i++)
        frameText[i - 8] = argv[3][i];
    frameText[i - 8] = '\0';
}

int main(int argc, char * argv[])
{
    setlocale(LC_ALL, "RUS");
    if(argc == 4 && strlen(argv[3]) >= 8 && argv[3][2] == 't' && argv[3][3] == 'o' &&
       argv[3][4] == 'F' && argv[3][5] == 'i' && argv[3][6] == 'l' && argv[3][7] == 'e')
        freopen("out.txt", "w", stdout);
    int i;
    if(argc == 1)
    {
        char *metaData[256];
        char fileName[8] = {'t', 'e', 's', 't', '.', 'm', 'p', '3', '\0'};
        char frameId[5] = {'T', 'I', 'T', '2', '\0'};
        char frameText[5] = {'T', 'E', 'S', 'T', '\0'};
        updateFrameTextById(fileName, frameId, frameText);
        return 0;
    }
    if(argc < 2)
    {
        puts("Write all parametres, like sample");
        return 0;
    }
    char fileName[256];
    getSongFileName(argc, argv, fileName);
    puts("");
    if(argv[2][2] == 's' && argv[2][3] == 'h' && argv[2][4] == 'o' && argv[2][5] == 'w')
    {
        char *metaData[256];
        int len = getAllMetainformationFromFile(fileName, metaData);
        int i, j, maxLen = 0;
        for(i = 0; i < len; i += 2)
            maxLen = max(maxLen, strlen(metaData[i]));
        for(i = 0; i < len; i += 2)
        {
            printf("%s", metaData[i]);
            for(j = strlen(metaData[i]); j < maxLen; j++)
                printf(" ");
            printf(" | ");
            printf("%s\n", metaData[i + 1]);
        }
    }
    else if(argv[2][2] == 'g' && argv[2][3] == 'e' && argv[2][4] == 't')
    {
        char frameId[5];
        getFrameIdFromARGV(argv, frameId);
        printAllAboutFrame(fileName, frameId);
    }
    else if(argv[2][2] == 's' && argv[2][3] == 'e' && argv[2][4] == 't')
    {
        char frameId[5];
        char frameText[1024];
        getFrameIdFromARGV(argv, frameId);
        getFrameTextFromARGV(argv, frameText);
        updateFrameTextById(fileName, frameId, frameText);
    }
    else
        puts("Incorect comand");
    return 0;
}