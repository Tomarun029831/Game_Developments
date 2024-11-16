#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <dirent.h>
#include "../include/window.h"
#include "../include/settings.h"
#include "../include/options.h"

extern _Settings Settings;

const char *optionAdd[] = OPTION_ADD;             // create directory, file in data
const char *optionDirectory[] = OPTION_DIRECTOTY; // show file or subdirectory in data
const char *optionHelp[] = OPTION_HELP;           // help option
const char *optionRemove[] = OPTION_REMOVE;       // remove directory, file in data
const char *optionSettings[] = OPTION_SETTING;    // User configs
const char *optionTree[] = OPTION_TREE;           // show struct of path in data
const char **optionHandlers[] = {optionAdd, optionDirectory, optionHelp, optionRemove, optionTree, optionSettings};

int isDirectory(const char *path);

void showSettings()
{
    T_CLEAR;
    // FILE fp;
    char *s;
    printf("ID:%s\nPassword:%s\nFont:%s\nWight:%d\nHeight:%d\n",
           Settings.Id, Settings.Password, Settings.Window.Font, Settings.Window.Width, Settings.Window.Height);
    printf("<Option> <Object>\tPut a SPACE between <Option> and <Object>\n");
    TC_END;

    scanf_s("%s", s);
}

void executeOption(const char **_optionv)
{
    void (*handler)() = getOptionHandler(_optionv[0]);
    if (_optionv[1] == OPTION_FAILURE)
    {
        handler(OPTION_FAILURE);
        exit(EXIT_SUCCESS);
    }
    else if (_optionv[2] == OPTION_FAILURE)
    {
        handler(_optionv[1]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        handleError();
    }
}

void *getOptionHandler(const char *_option)
{
    const char **matchingOption = getFullOption(_option);
    if (matchingOption == optionAdd)
    {
        return addFileOrDir;
    }
    else if (matchingOption == optionDirectory)
    {
        return listDirectory;
    }
    else if (matchingOption == optionHelp)
    {
        return showHelp;
    }
    else if (matchingOption == optionRemove)
    {
        return removeUserData;
    }
    else if (matchingOption == optionTree)
    {
        return showDirectoryTree;
    }
    else if (matchingOption == optionSettings)
    {
        return showSettings;
    }
    return handleError;
}

const char **getFullOption(const char *_option)
{
    if (_option == OPTION_FAILURE)
    {
        return OPTION_FAILURE;
    }
    else
    {
        for (int option = 0; option < OPTION_AMOUNT; option++)
        {
            for (int alias = 0; alias < OPTION_ALIAS; alias++)
            {
                if (strcmp(_option, optionHandlers[option][alias]) == 0)
                    return optionHandlers[option];
            }
        }
        return OPTION_FAILURE;
    }
}

void showHelp(const char *_option)
{
    char *optionDescriptions[OPTION_AMOUNT] =
        {"-a <NAME>, add <NAME>, ADD <NAME> - create new file for saving processing of game",
         "-d <PATH>, dir <PATH>, DIR <PATH> - show files and subdirectories in directory of argument",
         "-h <OPTION>, help <OPTION>, HELP <OPTION> - show usage",
         "-rm <PATH>, remove <PATH>, REMOVE <PATH> - delete file of argument",
         "-t <PATH>, tree <PATH>, TREE <PATH> - show grahical struct of directory",
         "-s, settings, SETTINGS - user configs"};

    const char **matchingOption = getFullOption(_option);
    if (matchingOption == OPTION_FAILURE)
    {
        puts("Usage:");
        for (int option = 0; option < OPTION_AMOUNT; option++)
        {
            printf("\t%s\n", optionDescriptions[option]);
        }
    }
    else
    {
        puts("Usage:");
        for (int i = 0; i < OPTION_AMOUNT; i++)
        {
            if (matchingOption == optionHandlers[i])
            {
                printf("\t%s", optionDescriptions[i]);
            }
        }
    }
}

void showDirectoryTree(char *path) { printf("TREE called with %s", path); }

void listDirectory(char *path) { printf("DIRECRORY called with %s", path); }

int isDirectory(const char *path)
{
    DIR *dir = opendir(path);
    if (dir)
    {
        closedir(dir);
        return 1;
    }
    return 0;
}

void removeUserData(const char *const _userName)
{
    const char *const basePath = "./data/usr";
    char path[MAX_LENGTH_PATH];
    snprintf(path, sizeof(path), "%s/%s", basePath, _userName);

    DIR *dir = NULL;
    if (isDirectory(path))
    {
        dir = opendir(path);
        if (dir == NULL)
        {
            printf("Failed to open directory\n");
            exit(EXIT_FAILURE);
        }

        struct dirent *entry;
        char tmpPath[MAX_LENGTH_PATH];

        while ((entry = readdir(dir)) != NULL)
        {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue; // skip routine

            snprintf(tmpPath, sizeof(tmpPath), "%s/%s", _userName, entry->d_name);
            removeUserData(tmpPath);
        }

        closedir(dir);

        if (_rmdir(path) == -1)
        {
            printf("Failed to remove directory\n");
        }
    }
    else
    {
        if (remove(path) == -1)
        {
            printf("Failed to remove file\n");
        }
    }
}

void addFileOrDir(char *path) { printf("ADD called with %s", path); }

void handleError()
{
    puts("Usage: .\\SolitaireCalculation.exe <option>\noption - \"help\"");
    exit(EXIT_FAILURE);
}
