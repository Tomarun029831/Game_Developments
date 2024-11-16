#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/settings.h"

#define DEFAULT_PATH "/defaults"
#define ASSIGN_OPERATER ':'
#define STARTBLOCK '{'
#define ENDBLOCK '}'
#define BUFFERABLE target[0] != ASSIGN_OPERATER &&target[0] != STARTBLOCK &&target[0] != ENDBLOCK &&target[0] != ' ' && target[0] != '\n'

extern _Settings Settings;

void colonOperater(char *, FILE *const);
void enterBlocks(char *, FILE *const);
void analyzeSettingsFile(FILE *const _fp);

// data\defaults\Settings.txt

void loadSettings(const char *const _userName)
{
    char userPath[MAX_LENGTH_PATH], bufferPath[MAX_LENGTH_PATH];
    const char *const basePath = (strcmp(_userName, DEFAULT_PATH) == 0) ? "../../data/defaults" : "../../data/usr";
    if (strcmp(_userName, DEFAULT_PATH) != 0)
        snprintf(userPath, sizeof(userPath), "%s/%s", basePath, _userName);
    else
        strcpy(userPath, basePath);
    strcpy(bufferPath, userPath);
    strcat(bufferPath, "/Settings.txt");
    FILE *fp = fopen("C:/Users/humti/OneDrive/ドキュメント/For_GitHub/Game_Developments/SolitaireCalculation_Package/data/defaults/Settings.txt", "r");
    printf("%s", bufferPath);
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