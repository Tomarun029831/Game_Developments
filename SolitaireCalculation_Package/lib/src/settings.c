#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "../include/settings.h"

#define ASSIGN_OPERATER ':'
#define STARTBLOCK '{'
#define ENDBLOCK '}'

_Settings Settings;
int isBufferAble(const char _c);
void analyzeSettings(char *_str, char load_mode);
void colonOperater(const char *const _attr, char **_loadPointer, const char _mode);
char *read_until_newline(const char **_loadPointer);
void forceInsertStr(char **_startPointer, const char *_source);

// :, {, },  , \n, \r
int isBufferAble(const char _c)
{
    const char notBufferAble[] = NOTBUFFERABLE;
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
    // printf("load called with %s %c\n", _userName, load_mode);
    if (load_mode != 'r' && load_mode != 's' || strcmp(_userName, "") == 0)
        return LOAD_FAILURE;

    char userPath[MAX_LENGTH_PATH];
    char bufferPath[MAX_LENGTH_PATH];
    const char *const basePath = (strcmp(_userName, DEFAULT_PATH) == 0) ? "./data/defaults" : "./data/usr";

    if (strcmp(_userName, DEFAULT_PATH) != 0)
        snprintf(userPath, sizeof(userPath), "%s/%s", basePath, _userName);
    else
        strcpy(userPath, basePath);

    strcpy(bufferPath, userPath);
    strcat(bufferPath, "/Settings.txt");

    FILE *fp = fopen(bufferPath, "rb");
    if (fp == NULL)
        return LOAD_FAILURE;

    fseek(fp, 0, SEEK_END);
    int fileSize = ftell(fp); // 117
    fseek(fp, 0, SEEK_SET);

    size_t c_size = sizeof(char);
    char *buffer = malloc(fileSize + 1);

    fread(buffer, c_size, fileSize, fp);
    buffer[fileSize] = '\0';

    analyzeSettings(buffer, load_mode);
    fclose(fp);

    if (load_mode == 's')
    {
        fp = fopen(bufferPath, "wb");
        fwrite(buffer, c_size, strlen(buffer), fp);
        fclose(fp);
    }

    if (buffer != NULL)
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
        // if (target[0] == '\n')
        //     printf("n\n");
        // else if (target[0] == '\r')
        //     printf("r");
        // else
        //     printf("|%c|", target[0]);

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
            colonOperater(buffer, &loadPointer, _mode);
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
    // printf("FIS called with %c %s\n", **_startPointer, _source);
    char *startPoint = *_startPointer;
    char *buffer = malloc((strlen(startPoint) + strlen(_source) + 1) * sizeof(char));
    strcpy(buffer, _source);
    *_startPointer += strcspn(startPoint, "\r\n");
    strcat(buffer, *_startPointer);
    strcpy(startPoint, buffer);
    *_startPointer = startPoint + strcspn(startPoint, "\n");

    free(buffer);
}

int count_figures(int n)
{
    int count = 0;
    if (n == 0)
        return 1;
    if (n < 0)
        n = -n;

    while (n != 0)
    {
        n /= 10;
        count++;
    }

    return count;
}

void colonOperater(const char *const _attr, char **_loadPointer, const char _mode)
{

    char *buffer = NULL;
    const char *settingsAttritude[] = SETTINGS_ATTRITUDE;
    void *settings_p[] = {
        Settings.Id, Settings.Password, Settings.Window.Font.name,
        &Settings.Window.Width, &Settings.Window.Height};

    for (int i = 0; i < sizeof(settingsAttritude) / sizeof(settingsAttritude[0]); ++i)
    {
        if (strcmp(_attr, settingsAttritude[i]) == 0)
        {
            switch (_mode)
            {
            case 'r':
                while (**_loadPointer == ' ')
                    ++*_loadPointer;
                buffer = read_until_newline((const char **)_loadPointer); // need free(return value)
                buffer[strcspn(buffer, "\r\n")] = '\0';
                if (i < 3)
                {
                    strcpy((char *)settings_p[i], buffer);
                    if (strcmp(_attr, "FONT") == 0)
                    {
                        loadFont(buffer);
                    }
                }
                else
                {
                    *((int *)settings_p[i]) = atoi(buffer);
                }
                break;
            case 's':
                if (i < 3)
                {
                    forceInsertStr(_loadPointer, (char *)settings_p[i]);
                }
                else
                {
                    buffer = malloc((count_figures(*((int *)settings_p[i])) + 1) * sizeof(char));
                    forceInsertStr(_loadPointer, itoa(*((int *)settings_p[i]), buffer, 10));
                }
                break;
            }
            break;
        }
    }
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