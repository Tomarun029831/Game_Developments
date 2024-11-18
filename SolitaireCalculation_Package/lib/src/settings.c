#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "../include/settings.h"

#define ASSIGN_OPERATER ':'
#define STARTBLOCK '{'
#define ENDBLOCK '}'
char notBufferAble[] = NOTBUFFERABLE;

extern _Settings Settings;
int isBufferAble(const char _c);
void analyzeSettings(char *_str, char load_mode);
void colonOperater(const char *const _attr, char *_str, char **_loadPointer, const char _mode);
char *read_until_newline(const char **_loadPointer);

// :, {, },  , \n
int isBufferAble(const char _c)
{
    int isbufferable = 1;
    int len = strlen(notBufferAble);

    for (int i = 0; i < len; i++)
    {
        if (_c == notBufferAble[i])
        {
            isbufferable = 0;
            break;
        }
    }

    return isbufferable;
}

// fopen に 相対パスを設定するとき .exe からの相対パスであることに注意

// _mode, 'r': Read-Only, 's': Save-Settings
int loadSettings(const char *const _userName, const char load_mode)
{
    printf("load called with %s %c\n", _userName, load_mode);
    if (load_mode != 'r' && load_mode != 's' || strcmp(_userName, "") == 0)
        return LOAD_FAILURE;

    int fileSize;
    char *buffer;
    char userPath[MAX_LENGTH_PATH];
    char bufferPath[MAX_LENGTH_PATH];
    const char *const basePath = (strcmp(_userName, DEFAULT_PATH) == 0) ? "./data/defaults" : "./data/usr";

    if (strcmp(_userName, DEFAULT_PATH) != 0)
        snprintf(userPath, sizeof(userPath), "%s/%s", basePath, _userName);
    else
        strcpy(userPath, basePath);

    strcpy(bufferPath, userPath);
    strcat(bufferPath, "/Settings.txt");

    FILE *fp = fopen(bufferPath, "r");
    if (fp == NULL)
        return LOAD_FAILURE;

    fseek(fp, 0, SEEK_END);
    fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    size_t c_size = sizeof(char);
    buffer = malloc(fileSize * c_size);
    fileSize = fread(buffer, c_size, fileSize, fp);
    free(buffer);

    fseek(fp, 0, SEEK_SET);
    buffer = malloc(fileSize * c_size);
    fread(buffer, c_size, fileSize, fp);

    analyzeSettings(buffer, load_mode);
    fclose(fp);

    if (load_mode == 's')
    {
        fp = fopen(bufferPath, "w");
        fwrite(buffer, c_size, strlen(buffer) + 1, fp);
        fclose(fp);
    }
    free(buffer);

    return LOAD_SUCCESS;
}

void analyzeSettings(char *_str, char _mode)
{
    int blockCount = 0;
    char *loadPointer = _str;
    char target[2] = "";
    char buffer[MAX_LENGTH_PATH] = "";
    while ((target[0] = *loadPointer) != '\0')
    {
        if (isBufferAble(target[0]))
            strcat(buffer, target);
        switch (target[0])
        {
        case STARTBLOCK:
            ++blockCount;
            strcpy(buffer, "");

            break;
        case ENDBLOCK:
            --blockCount;
            strcpy(buffer, "");
            break;
        case ASSIGN_OPERATER:
            ++loadPointer;
            colonOperater(buffer, _str, &loadPointer, _mode);
            strcpy(buffer, "");
            break;
        }
        ++loadPointer;
    }
    if (blockCount != 0)
    {
        printf("Syntax error: leak %d BLOCK-CHARACTER\n", blockCount);
    }
}

void forceInsertStr(char **_startPointer, const char *_source)
{
    char *startPoint = *_startPointer;
    *_startPointer += strcspn(startPoint, "\n");
    char *buffer = malloc((strlen(startPoint) + strlen(_source) + 1) * sizeof(char));
    strcpy(buffer, _source);
    strcat(buffer, *_startPointer);
    strcpy(startPoint, buffer);

    free(buffer);
}

void colonOperater(const char *const _attr, char *_str, char **_loadPointer, const char _mode)
{
    char *buffer;
    char *strp;
    int *intp;
    if (_mode == 'r')
    {
        while (**_loadPointer == ' ')
            ++*_loadPointer;
        buffer = read_until_newline((const char **)_loadPointer);
        buffer[strcspn(buffer, "\n")] = '\0';
    }
    if (strcmp(_attr, "ID") == 0 || strcmp(_attr, "PASSWORD") == 0 || strcmp(_attr, "FONT") == 0)
    {
        if (strcmp(_attr, "ID") == 0)
            strp = Settings.Id;
        else if (strcmp(_attr, "PASSWORD") == 0)
            strp = Settings.Password;
        else if (strcmp(_attr, "FONT") == 0)
            strp = Settings.Window.Font.name;
        switch (_mode)
        {
        case 'r':
            strcpy(strp, buffer);
            if (strcmp(_attr, "FONT") == 0)
                loadFont(buffer);
            break;
        case 's':
            forceInsertStr(_loadPointer, strp);
            break;
        }
    }
    else if (strcmp(_attr, "WIDTH") == 0 || strcmp(_attr, "HEIGHT") == 0)
    {
        if (strcmp(_attr, "WIDTH") == 0)
            intp = &Settings.Window.Width;
        else if (strcmp(_attr, "HEIGHT") == 0)
            intp = &Settings.Window.Height;
        switch (_mode)
        {
        case 'r':
            *intp = atoi(buffer);
            break;
        case 's':
            break;
        }
    }

    if (buffer != NULL)
        free(buffer);
}

void loadFont(const char *const _font)
{
}

char *read_until_newline(const char **_loadPointer)
{
    if (*_loadPointer == NULL)
    {
        return NULL;
    }

    int length = strcspn(*_loadPointer, "\n");

    char *result = (char *)malloc(length + 1);
    if (result == NULL)
    {
        return NULL;
    }

    strncpy(result, *_loadPointer, length);

    result[length] = '\0';
    *_loadPointer += length; // move pointer to a newline

    return result;
}