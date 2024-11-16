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
void showHelp(const char *);
void showDirectoryTree(char *);
void listDirectory(char *);
void removeFileOrDir(char *);
void addFileOrDir(char *);
void handleError();
const char **getFullOption(const char *);
void *getOptionHandler(const char *_option);
void executeOption(const char **);
