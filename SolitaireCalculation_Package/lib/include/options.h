#pragma once

#define OPTION_AMOUNT 6
#define OPTION_ALIAS 3
#define OPTION_FAILURE NULL

#define ORIGINAL_ADD "ADD"
#define ORIGINAL_DIRECTORY "DIR"
#define ORIGINAL_HELP "HELP"
#define ORIGINAL_REMOVE "REMOVE"
#define ORIGINAL_SETTINGS "SETTINGS"
#define ORIGINAL_TREE "TREE"

#define ALIAS_ADD {ORIGINAL_ADD, "add", "-a"} // create directory, file in data

#define ALIAS_DIRECTORY {ORIGINAL_DIRECTORY, "dir", "-d"}    // show file or subdirectory in data
#define ALIAS_HELP {ORIGINAL_HELP, "help", "-h"}             // help option
#define ALIAS_REMOVE {ORIGINAL_REMOVE, "remove", "-rm"}      // remove directory, file in data
#define ALIAS_SETTINGS {ORIGINAL_SETTINGS, "settings", "-s"} // User configss
#define ALIAS_TREE {ORIGINAL_TREE, "tree", "-t"}             // show struct of path in data

// Options
void showHelp(const char *_option);
void showDirectoryTree(char *path);
void showSettings();
void listDirectory(char *path);
void removeUserData(const char *const path);
void addUserData(char *path);
void createFontFile(char *_fontName);
void handleError();
const char **getFullOption(const char *_option);
void *getOptionHandler(const char *_option);
void executeOption(const char **_optionv);