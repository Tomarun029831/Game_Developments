#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#include <direct.h>
#include <dirent.h>

#include "../include/window.h"
#include "../include/settings.h"
#include "../include/options.h"

extern _Settings Settings;

const char *optionAdd[] = ALIAS_ADD;             // create directory, file in data
const char *optionDirectory[] = ALIAS_DIRECTORY; // show file or subdirectory in data
const char *optionHelp[] = ALIAS_HELP;           // help option
const char *optionRemove[] = ALIAS_REMOVE;       // remove directory, file in data
const char *optionSettings[] = ALIAS_SETTINGS;   // User configs
const char *optionTree[] = ALIAS_TREE;           // show struct of path in data
const char *optionHandler[] = {ORIGINAL_ADD, ORIGINAL_DIRECTORY, ORIGINAL_HELP, ORIGINAL_REMOVE, ORIGINAL_SETTINGS, ORIGINAL_TREE};
const char **optionAliasHandlers[] = {optionAdd, optionDirectory, optionHelp, optionRemove, optionTree, optionSettings};

int isDirectory(const char *path);
void copy_file(const char *source_filename, const char *destination_filename);

void showSettings()
{
    for (int i = 0; i < sizeof(optionHandler) / sizeof(optionHandler[0]); i++)
    {
        printf("%s\n", optionHandler[i]);
    }
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
        return addUserData;
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
                if (strcmp(_option, optionAliasHandlers[option][alias]) == 0)
                    return optionAliasHandlers[option];
            }
        }
        return OPTION_FAILURE;
    }
}

void showHelp(const char *_option)
{
    char *optionDescriptions[OPTION_AMOUNT] =
        {"ADD: ADD <NAME>, add <NAME>, -a <NAME> - create new file for saving processing of game",
         "DIR: DIR <PATH>, dir <PATH>, -d <PATH> - show files and subdirectories in directory of argument",
         "HELP: HELP <OPTION>, help <OPTION>, -h <OPTION> - show usage",
         "REMOVE: REMOVE <NAME>, remove <NAME>, -rm <NAME> - delete file of argument",
         "TREE: TREE <PATH>, tree <PATH>, -t <PATH> - show grahical struct of directory",
         "SETTINGS: SETTINGS <ATTR>, settings <ATTR>, -s <ATTR> - user configs"};

    char *settingsDescription[] =
        {"ID: Identification of user",
         "PASSWORD: User's password that exclude \'/\'",
         "WINDOW: Window-settings includes Font and Size",
         "FONT: Strings-Settings printed that includes Foreground, Background and Text-Style ",
         "SIZE: Terminal-Size",
         "WIDTH: :)",
         "HEIGHT: :)"};

    const char **matchingOption = getFullOption(_option);
    if (matchingOption == OPTION_FAILURE)
    {
        puts("Usage:");
        for (int i = 0; i < OPTION_AMOUNT; i++)
        {
            printf("\t%s\n", optionDescriptions[i]);
        }
    }
    else
    {
        puts("Usage:");
        for (int option = 0; option < OPTION_AMOUNT; option++)
        {
            if (matchingOption == optionAliasHandlers[option])
            {
                printf("\t%s", optionDescriptions[option]);
                break;
            }
        }
    }
}

#define VERTICAL_LINE L'│'   // │ (Unicode)
#define NODE_CHILD L'├'      // ├ (Unicode)
#define HORIZONTAL_LINE L'─' // ─ (Unicode)
#define LAST_NODE L'└'       // └ (Unicode)

void showDirectoryTree(char *path)
{
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        printf("Failed to open directory\n");
        exit(EXIT_FAILURE);
    }
    struct dirent *entry;
    printf("TREE called with %s\n", path);
    // wprintf(L"%lc %lc %lc %lc\n", vline, nodec, hline, LAST_NODE);
    closedir(dir);
}

void listDirectory(char *path)
{
    if (strchr(path, '\\') != NULL)
    {
        puts("Invail path: You cannot include \'\\\' in Path, but \'/\'\n");
        exit(EXIT_FAILURE);
    }
    path = path ? path : "./";
    char bufferPath[MAX_LENGTH_PATH];
    strcpy(bufferPath, path);
    char *strp = &bufferPath[strcspn(bufferPath, "\0")];

    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        printf("Failed to open directory\n");
        exit(EXIT_FAILURE);
    }
    struct dirent *entry;
    setFontAttributes(0, 92, 0);
    printf("Mode\tName\n----\t----\n");
    RESET_FONT;
    while ((entry = readdir(dir)) != NULL)
    {
        snprintf(bufferPath, sizeof(bufferPath), "%s/%s", path, entry->d_name);
        printf("%s\t%s\n", isDirectory(bufferPath) ? "d----" : "-a---", entry->d_name);
    }
    closedir(dir);
}

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

    if (isDirectory(path))
    {
        DIR *dir = opendir(path);
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

void copy_file(const char *source_filename, const char *destination_filename)
{
    FILE *source_file = fopen(source_filename, "rb");
    if (source_file == NULL)
    {
        perror("Error opening source file");
        return;
    }

    FILE *destination_file = fopen(destination_filename, "wb");
    if (destination_file == NULL)
    {
        perror("Error opening destination file");
        fclose(source_file);
        return;
    }

    const size_t buffer_size = 1024; // 1KB
    unsigned char buffer[buffer_size];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, buffer_size, source_file)) > 0)
    {
        size_t bytes_written = fwrite(buffer, 1, bytes_read, destination_file);
        if (bytes_written < bytes_read)
        {
            perror("Error writing to destination file");
            fclose(source_file);
            fclose(destination_file);
            return;
        }
    }

    fclose(source_file);
    fclose(destination_file);
}

void addUserData(char *_userName)
{
    const char *const defaultSettingsPath = "./data/defaults/Settings.txt";
    const char *const defaultFontPath = "./data/defaults/Font/default.txt";

    const char *const basePath = "./data/usr";
    char userDir[MAX_LENGTH_PATH];
    char tmpPath[MAX_LENGTH_PATH];
    FILE *fp;
    snprintf(userDir, sizeof(userDir), "%s/%s", basePath, _userName);

    _mkdir(userDir);
    snprintf(tmpPath, sizeof(tmpPath), "%s/%s", userDir, "Settings.txt");
    copy_file(defaultSettingsPath, tmpPath);

    _mkdir(strcat(strcpy(tmpPath, userDir), "/font"));
    snprintf(tmpPath, sizeof(tmpPath), "%s/%s", tmpPath, "font.txt");
    copy_file(defaultFontPath, tmpPath);
}

void createFontFile(char *_fontName, FILE *_fp)
{
    if (strcmp(_fontName, "default") == 0)
    {
    }
    else
    {
    }
}

void handleError()
{
    puts("Usage: .\\SolitaireCalculation.exe <option>\noption - \"help\"");
    exit(EXIT_FAILURE);
}
