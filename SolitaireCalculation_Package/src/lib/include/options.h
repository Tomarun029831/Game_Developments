#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./window.h"

#define OPTION_AMOUNT 6
#define OPTION_ALIAS 3
#define OPTION_FAILURE NULL
#define OPTION_ADD {"-a", "add", "ADD"}               // create directory, file in data
#define OPTION_DIRECTOTY {"-d", "dir", "DIR"}         // show file or subdirectory in data
#define OPTION_HELP {"-h", "help", "HELP"}            // help option
#define OPTION_REMOVE {"-rm", "remove", "REMOVE"}     // remove directory, file in data
#define OPTION_SETTING {"-s", "settings", "SETTINGS"} // User configs
#define OPTION_TREE {"-t", "tree", "TREE"}            // show struct of path in data

const char *optionAdd[] = OPTION_ADD;             // create directory, file in data
const char *optionDirectory[] = OPTION_DIRECTOTY; // show file or subdirectory in data
const char *optionHelp[] = OPTION_HELP;           // help option
const char *optionRemove[] = OPTION_REMOVE;       // remove directory, file in data
const char *optionSettings[] = OPTION_SETTING;    // User configs
const char *optionTree[] = OPTION_TREE;           // show struct of path in data
const char **optionHandlers[] = {optionAdd, optionDirectory, optionHelp, optionRemove, optionTree, optionSettings};

// Options
void showHelp(const char *);
void showDirectoryTree(char *);
void listDirectory(char *);
void removeFileOrDir(char *);
void addFileOrDir(char *);
void handleError();
const char **getFullOption(const char *);
void *getOptionHandler(const char *_option);
void executeOption(const char **);

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
        return removeFileOrDir;
    }
    else if (matchingOption == optionTree)
    {
        return showDirectoryTree;
    }
    else if (matchingOption == optionSettings)
    {
        return showSettingsWindow;
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
void removeFileOrDir(char *path) { printf("REMOVE called with %s", path); }
void addFileOrDir(char *path) { printf("ADD called with %s", path); }

void handleError()
{
    puts("Usage: .\\SolitaireCalculation.exe <option>\noption - \"help\"");
    exit(EXIT_FAILURE);
}