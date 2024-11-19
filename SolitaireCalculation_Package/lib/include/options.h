#pragma once

#define OPTION_AMOUNT 6
#define OPTION_ALIAS 3
#define OPTION_FAILURE NULL
#define OPTION_ADD {"ADD", "add", "-a"}               // create directory, file in data
#define OPTION_DIRECTOTY {"DIR", "dir", "-d"}         // show file or subdirectory in data
#define OPTION_HELP {"HELP", "help", "-h"}            // help option
#define OPTION_REMOVE {"REMOVE", "remove", "-rm"}     // remove directory, file in data
#define OPTION_SETTING {"SETTINGS", "settings", "-s"} // User configs
#define OPTION_TREE {"TREE", "tree", "-t"}            // show struct of path in data

// Options
void showHelp(const char *_option);
void showDirectoryTree(char *path);
void showSettings();
void listDirectory(char *path);
void removeUserData(const char *const path);
void addUserData(char *path);
void createFontFilel(char *_fileName);
void handleError();
const char **getFullOption(const char *_option);
void *getOptionHandler(const char *_option);
void executeOption(const char **_optionv);