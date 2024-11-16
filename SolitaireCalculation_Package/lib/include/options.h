#pragma once

#define OPTION_AMOUNT 6
#define OPTION_ALIAS 3
#define OPTION_FAILURE NULL
#define OPTION_ADD {"-a", "add", "ADD"}               // create directory, file in data
#define OPTION_DIRECTOTY {"-d", "dir", "DIR"}         // show file or subdirectory in data
#define OPTION_HELP {"-h", "help", "HELP"}            // help option
#define OPTION_REMOVE {"-rm", "remove", "REMOVE"}     // remove directory, file in data
#define OPTION_SETTING {"-s", "settings", "SETTINGS"} // User configs
#define OPTION_TREE {"-t", "tree", "TREE"}            // show struct of path in data

// Options
void showHelp(const char *path);
void showDirectoryTree(char *path);
void showSettings();
void listDirectory(char *path);
void removeUserData(const char *const path);
void addFileOrDir(char *path);
void handleError();
const char **getFullOption(const char *_option);
void *getOptionHandler(const char *_option);
void executeOption(const char **_optionv);