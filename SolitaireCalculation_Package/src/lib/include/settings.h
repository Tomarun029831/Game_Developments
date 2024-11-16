#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./settings.h"

#define MAX_LENGTH_PATH 256
#define ASSIGN_OPERATER ':'
#define STARTBLOCK '{'
#define ENDBLOCK '}'
#define BUFFERABLE target[0] != ASSIGN_OPERATER &&target[0] != STARTBLOCK &&target[0] != ENDBLOCK &&target[0] != ' ' && target[0] != '\n'
#define RESET_FONT setFontAttributes(-1, -1, -1)

typedef struct
{
    char *Style;
    char *Foreground;
    char *Background;
} ColorAttritude;

typedef struct
{
    char *name;
    ColorAttritude ShowUp;
    ColorAttritude Makestack;
    ColorAttritude Discard;
    ColorAttritude Disstack;
    ColorAttritude Undo;
    ColorAttritude Endgame;
} _Font;

typedef struct
{
    _Font Font;
    int Width;
    int Height;
} _Window;

typedef struct
{
    char Id[MAX_LENGTH_PATH];
    char Password[MAX_LENGTH_PATH];
    _Window Window;
} _Settings;

_Settings Settings;

// load settings
void loadSettings(const char *const _userName);
void loadFont(const char *const _font);
void colonOperater(char *, FILE *const);
void enterBlocks(char *, FILE *const);
void analyzeSettingsFile(FILE *const _fp);

void loadSettings(const char *const _userName)
{
    char userPath[MAX_LENGTH_PATH], bufferPath[MAX_LENGTH_PATH];
    const char *const basePath = (strcmp(_userName, "/defaultUser") == 0) ? "../data/base" : "../data/usr";
    (strcmp(_userName, "/defaultUser") == 0) ? snprintf(userPath, sizeof(userPath), "%s%s", basePath, _userName) : snprintf(userPath, sizeof(userPath), "%s/%s", basePath, _userName);
    strcpy(bufferPath, userPath);
    FILE *fp = fopen(strcat(bufferPath, "/Settings.txt"), "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    analyzeSettingsFile(fp);

    fclose(fp);
}

void analyzeSettingsFile(FILE *const _fp)
{
    char target[2] = "";
    char buffer[MAX_LENGTH_PATH] = "";
    while ((target[0] = fgetc(_fp)) != EOF)
    {
        if (BUFFERABLE)
            strcat(buffer, target);
        switch (target[0])
        {
        case ASSIGN_OPERATER:
            colonOperater(buffer, _fp);
            break;
        case STARTBLOCK:
            enterBlocks(buffer, _fp);
            break;
        }
    }
}

void enterBlocks(char *_buffer, FILE *const _fp)
{
    char target[2] = "";
    char buffer[MAX_LENGTH_PATH] = "";
    while ((target[0] = fgetc(_fp)) != ENDBLOCK)
    {
        if (BUFFERABLE)
            strcat(buffer, target);

        switch (target[0])
        {
        case ASSIGN_OPERATER:

            colonOperater(buffer, _fp);
            break;
        case STARTBLOCK:

            enterBlocks(buffer, _fp);
            break;
        }
    }
}

void colonOperater(char *_attr, FILE *const _fp)
{
    char buffer[MAX_LENGTH_PATH] = "";
    if (strcmp(_attr, "ID") == 0)
    {
        while ((buffer[0] = fgetc(_fp)) == ' ')
            ;
        if (fgets(&buffer[1], sizeof(buffer), _fp))
        {
            buffer[strchr(buffer, '\n') - buffer] = '\0';
            strcpy(Settings.Id, buffer);
        }
    }
    else if (strcmp(_attr, "PASSWORD") == 0)
    {
        while ((buffer[0] = fgetc(_fp)) == ' ')
            ;
        if (fgets(&buffer[1], sizeof(buffer), _fp))
        {
            buffer[strchr(buffer, '\n') - buffer] = '\0';
            strcpy(Settings.Password, buffer);
        }
    }
    else if (strcmp(_attr, "FONT") == 0)
    {
        while ((buffer[0] = fgetc(_fp)) == ' ')
            ;
        if (fgets(&buffer[1], sizeof(buffer), _fp))
        {
            loadFont(buffer);
        }
    }
    else if (strcmp(_attr, "WIDTH") == 0)
    {
        while ((buffer[0] = fgetc(_fp)) == ' ')
            ;
        if (fgets(&buffer[1], sizeof(buffer), _fp))
        {
            buffer[strchr(buffer, '\n') - buffer] = '\0';
            Settings.Window.Width = atoi(buffer);
        }
    }
    else if (strcmp(_attr, "HEIGHT") == 0)
    {
        while ((buffer[0] = fgetc(_fp)) == ' ')
            ;
        if (fgets(&buffer[1], sizeof(buffer), _fp))
        {
            buffer[strchr(buffer, '\n') - buffer] = '\0';
            Settings.Window.Height = atoi(buffer);
        }
    }
    strcpy(_attr, "");
}

void loadFont(const char *const _font)
{
}