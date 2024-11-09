#include <stdio.h>
#include <string.h> // strcmp
#include <stdlib.h> // exit, random
#include <time.h>   // time

#define OPTION_AMOUNT 5
#define OPTION_ALIAS 3

#define OPTION_NULL "NONOPTION"
#define OPTION_INVAIL NULL
#define OPTION_HELP {"-h", "help", "HELP"}        // help option
#define OPTION_TREE {"-t", "tree", "TREE"}        // show struct of path in data
#define OPTION_DIRECTOTY {"-d", "dir", "DIR"}     // show file or subdirectory in data
#define OPTION_REMOVE {"-rm", "remove", "REMOVE"} // remove directory, file in data
#define OPTION_ADD {"-a", "add", "ADD"}           // create directory, file in data

const char *optionADD[] = OPTION_ADD;
const char *optionDIRECTORY[] = OPTION_DIRECTOTY;
const char *optionHELP[] = OPTION_HELP;
const char *optionREMOVE[] = OPTION_REMOVE;
const char *optionTREE[] = OPTION_TREE;
const char **callOptions[] = {optionADD, optionDIRECTORY, optionHELP, optionREMOVE, optionTREE};

// 'S', 'D', 'H', 'C'
int ranks[] = {'S', 'D', 'H', 'C'};
// 'A', '2', '3', '4', '5', '6', '7', '8', '9', "10", 'J', 'Q', 'K'
int suits[] = {'A', 2, 3, 4, 5, 6, 7, 8, 9, 10, 'J', 'Q', 'K'};
typedef struct
{
    char *suit; // 'S', 'D', 'H', 'C'
    char *rank; // 'A', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K'
} Card;
typedef struct
{
    Card *next;
} Stock;

// Option
void HELP(char *);
void TREE(char *);
void DIRECTORY(char *);
void REMOVE(char *);
void ADD(char *);
const char **CHECKOPTION(char *);
void *RETURN_FUNC_OPTION(char *);

// To Enter Game
int StartWindow(int, char **);
void opERROR();

// Enter Game
void SolitaireCalculation();

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
    SolitaireCalculation();

    return 0;
}

void SolitaireCalculation()
{
    puts("SolitaireCalculation starts");
}

int StartWindow(int argc, char **argv)
{
    char *callOptions[][OPTION_ALIAS] = {OPTION_ADD, OPTION_DIRECTOTY, OPTION_HELP, OPTION_REMOVE, OPTION_TREE};
    void (*pfunc)() = RETURN_FUNC_OPTION(argv[1]);
    // found option
    if (argc == 1)
    {
        return 0; // normal
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

const char **CHECKOPTION(char *_option)
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
                if (strcmp(_option, callOptions[option][alias]) == 0)
                    return callOptions[option];
            }
        }
        return OPTION_INVAIL;
    }
}

void *RETURN_FUNC_OPTION(char *_fullOption)
{
    const char **fullOption = CHECKOPTION(_fullOption);
    if (fullOption == optionADD)
    {
        return ADD;
    }
    else if (fullOption == optionDIRECTORY)
    {
        return DIRECTORY;
    }
    else if (fullOption == optionHELP)
    {
        return HELP;
    }
    else if (fullOption == optionREMOVE)
    {
        return REMOVE;
    }
    else if (fullOption == optionTREE)
    {
        return TREE;
    }
    return opERROR;
}

void HELP(char *_option)
{
    const char *describeOption[OPTION_AMOUNT] =
        {"-a <NAME>, add <NAME>, ADD <NAME> - create new file for saving processing of game",
         "-d <PATH>, dir <PATH>, DIR <PATH> - show files and subdirectories in directory of argument",
         "-h <OPTION>, help <OPTION>, HELP <OPTION> - show usage",
         "-rm <PATH>, remove <PATH>, REMOVE <PATH> - delete file of argument",
         "-t <PATH>, tree <PATH>, TREE <PATH> - show grahical struct of directory"};

    const char **fullOption = CHECKOPTION(_option);
    if (fullOption == OPTION_INVAIL)
    {
        puts("Usage:");
        for (int option = 0; option < OPTION_AMOUNT; option++)
        {
            printf("\t%s\n", describeOption[option]);
        }
    }
    else
    {
        puts("Usage:");
        if (fullOption == optionADD)
        {
            printf("\t%s", describeOption[0]);
        }
        else if (fullOption == optionDIRECTORY)
        {
            printf("\t%s", describeOption[1]);
        }
        else if (fullOption == optionHELP)
        {
            printf("\t%s", describeOption[2]);
        }
        else if (fullOption == optionREMOVE)
        {
            printf("\t%s", describeOption[3]);
        }
        else if (fullOption == optionTREE)
        {
            printf("\t%s", describeOption[4]);
        }
    }
}

void TREE(char *path) { printf("TREE called with %s", path); }
void DIRECTORY(char *path) { printf("DIRECRORY called with %s", path); }
void REMOVE(char *path) { printf("REMOVE called with %s", path); }
void ADD(char *path) { printf("ADD called with %s", path); }

void opERROR()
{
    puts("Usage: .\\SolitaireCalculation.exe <option>\noption - \"help\"");
    exit(EXIT_FAILURE);
}