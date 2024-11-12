#include <stdio.h>
#include <string.h> // strcmp
#include <stdlib.h> // exit, random
#include <time.h>   // time

#define OPTION_AMOUNT 6
#define OPTION_ALIAS 3
#define OPTION_NULL "NONOPTION"
#define OPTION_INVAIL NULL
#define OPTION_ADD {"-a", "add", "ADD"}               // create directory, file in data
#define OPTION_DIRECTOTY {"-d", "dir", "DIR"}         // show file or subdirectory in data
#define OPTION_HELP {"-h", "help", "HELP"}            // help option
#define OPTION_REMOVE {"-rm", "remove", "REMOVE"}     // remove directory, file in data
#define OPTION_SETTING {"-s", "settings", "SETTINGS"} // User configs
#define OPTION_TREE {"-t", "tree", "TREE"}            // show struct of path in data

#define RESET_FONT setFontAttributes(-1, -1, -1)

const char *optionAdd[] = OPTION_ADD;             // create directory, file in data
const char *optionDirectory[] = OPTION_DIRECTOTY; // show file or subdirectory in data
const char *optionHelp[] = OPTION_HELP;           // help option
const char *optionRemove[] = OPTION_REMOVE;       // remove directory, file in data
const char *optionSettings[] = OPTION_SETTING;    // User configs
const char *optionTree[] = OPTION_TREE;           // show struct of path in data
const char **optionHandlers[] = {optionAdd, optionDirectory, optionHelp, optionRemove, optionTree, optionSettings};

// 'S', 'D', 'H', 'C'
int cardRanks[] = {'S', 'D', 'H', 'C'};
// 'A', '2', '3', '4', '5', '6', '7', '8', '9', "10", 'J', 'Q', 'K'
int cardSuits[] = {'A', 2, 3, 4, 5, 6, 7, 8, 9, 10, 'J', 'Q', 'K'};
typedef struct
{
    char *suit; // 'S', 'D', 'H', 'C'
    char *rank; // 'A', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K'
} Card;
typedef struct
{
    Card *next;
} Stock;

// Initialize
void initializeWindow();

void initializeGame();

void initializeSettings();

// Options
void showHelp(char *);
void showDirectoryTree(char *);
void listDirectory(char *);
void removeFileOrDir(char *);
void addFileOrDir(char *);
const char **getOption(char *);
void *getOptionHandler(char *);

// Setting Window
void showSettingsWindow();
void SetWindowSize(int, int);
void setFontAttributes(int, int, int);

// To Enter Game
int StartWindow(int, char **);
void handleError();

// Enter Game
void solitaireCalculation();

/*

                                       turn_  1
             .------_:=^=:_------_:=^=:_------_:=^=:_------_:=^=:_------.
point:              |  1  |      |  2  |      |  3  |      |  4  |
    lead:     .-----.      .-----.      .-----.      .-----.
$ C_ K        |   2 | S_ A |   4 | D_ 2 |   6 | H_ 3 |   8 | C_ 4
              '-----'      '-----'      '-----'      '-----'
    stuck:

ms (1~4):makestack stuckpoint
dc (1~4):discard leadpoint
ds (1~4) (1~4):disstuck stuckpoint leadpoint
ud :undo
ed :endgame

ed

    puts("\x1b[?25l\x1b[H\x1b[J"); // hide cursor, move it to HOME and delete right of cousor pos


    puts("\x1b[?25h"); // show cursor

*/

int main(int argc, char **argv)
{
    StartWindow(argc, argv);
    solitaireCalculation();

    RESET_FONT;
    return 0;
}

void solitaireCalculation()
{
    puts("SolitaireCalculation starts");
}

int StartWindow(int argc, char **argv)
{
    void (*pfunc)() = getOptionHandler(argv[1]);
    // found option
    if (argc == 1)
    {
        printf("\x1b[?25l\x1b[H\x1b[J"); // hide cursor, move it to HOME and delete right of cousor pos

        // setFontAttributes(0, 31, 42);
        // printf("aaa\n");
        // RESET_FONT;

        printf("\x1b[?25h"); // show cursor
        return 0;            // Enter Game
    }
    else if (argc == 2)
    {
        pfunc(OPTION_NULL);
        exit(EXIT_SUCCESS);
    }
    else if (argc == 3)
    {
        pfunc(argv[2]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        puts("Warning: Too many arguments");
        pfunc(argv[2]);
        exit(EXIT_FAILURE);
    }
}

const char **getOption(char *_option)
{
    if (_option == OPTION_INVAIL)
    {
        return OPTION_INVAIL;
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
        return OPTION_INVAIL;
    }
}

void *getOptionHandler(char *_fullOption)
{
    const char **matchingOption = getOption(_fullOption);
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

void initializeWindow()
{
}

void initializeGame()
{
}

void initializeSettings()
{
}

void showHelp(char *_option)
{
    const char *optionDescriptions[OPTION_AMOUNT] =
        {"-a <NAME>, add <NAME>, ADD <NAME> - create new file for saving processing of game",
         "-d <PATH>, dir <PATH>, DIR <PATH> - show files and subdirectories in directory of argument",
         "-h <OPTION>, help <OPTION>, HELP <OPTION> - show usage",
         "-rm <PATH>, remove <PATH>, REMOVE <PATH> - delete file of argument",
         "-t <PATH>, tree <PATH>, TREE <PATH> - show grahical struct of directory",
         "-s, settings, SETTINGS - user configs"};

    const char **matchingOption = getOption(_option);
    if (matchingOption == OPTION_INVAIL)
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
        if (matchingOption == optionAdd)
        {
            printf("\t%s", optionDescriptions[0]);
        }
        else if (matchingOption == optionDirectory)
        {
            printf("\t%s", optionDescriptions[1]);
        }
        else if (matchingOption == optionHelp)
        {
            printf("\t%s", optionDescriptions[2]);
        }
        else if (matchingOption == optionRemove)
        {
            printf("\t%s", optionDescriptions[3]);
        }
        else if (matchingOption == optionTree)
        {
            printf("\t%s", optionDescriptions[4]);
        }
        else if (matchingOption == optionSettings)
        {
            printf("\t%s", optionDescriptions[5]);
        }
    }
}

void showDirectoryTree(char *path) { printf("TREE called with %s", path); }
void listDirectory(char *path) { printf("DIRECRORY called with %s", path); }
void removeFileOrDir(char *path) { printf("REMOVE called with %s", path); }
void addFileOrDir(char *path) { printf("ADD called with %s", path); }

void showSettingsWindow()
{
}

void SetWindowSize(int width, int height)
{
}

// 0 <= style <= 9, 30 <= foreground <= 37 or 90 <= foreground <= 97, 40 <= background <= 47 or 100 <= background <= 107
void setFontAttributes(int style, int foreground, int background)
{
    int isStyleValid = (style >= 0 && style <= 9);
    int isForegroundValid = ((30 <= foreground && foreground <= 39) || (90 <= foreground && foreground <= 97));
    int isBackgroundValid = ((40 <= background && background <= 49) || (100 <= background && background <= 107));

    if (style == -1 && foreground == -1 && background == -1)
    {
        printf("\x1b[0m");
        return;
    }

    printf("\x1b[");

    if (isStyleValid)
        printf("%d", style);

    if (isForegroundValid)
    {
        if (isStyleValid)
            printf(";");
        printf("%d", foreground);
    }

    if (isBackgroundValid)
    {
        if (isStyleValid || isForegroundValid)
            printf(";");
        printf("%d", background);
    }

    printf("m");
}

void handleError()
{
    puts("Usage: .\\SolitaireCalculation.exe <option>\noption - \"help\"");
    exit(EXIT_FAILURE);
}