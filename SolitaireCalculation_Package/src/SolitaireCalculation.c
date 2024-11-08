#include <stdio.h>
#include <string.h> // strcmp
#include <stdlib.h> // exit, random
#include <time.h>   // time

#define OPTION_AMOUNT 5
#define OPTION_ALIAS 3

#define OPTION_NULL "noOption"
#define OPTION_HELP {"-h", "help", "HELP"}        // help option
#define OPTION_TREE {"-t", "tree", "TREE"}        // show struct of path in data
#define OPTION_DIRECTOTY {"-d", "dir", "DIR"}     // show file or subdirectory in data
#define OPTION_REMOVE {"-rm", "remove", "REMOVE"} // remove directory, file in data
#define OPTION_ADD {"-a", "add", "ADD"}           // create directory, file in data

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
void HELP(char *option);
void TREE(char *path);
void DIRECTORY(char *path);
void REMOVE(char *path);
void ADD(char *path);

// To Enter Game
int StartWindow(int, char **);
void OPTION_ERROR();

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
    if (argc < 4)
    {
        for (int line = 1; line < argc; line++) // focus cmdline
        {
            for (int option = 0; option < OPTION_AMOUNT; option++) // compare options
            {
                for (int alias = 0; alias < OPTION_ALIAS; alias++) // check all aliases
                {
                    if (strcmp(argv[line], callOptions[option][alias]) == 0) // found option
                    {
                        printf("find cmd: %s\n", callOptions[option][alias]);
                        HELP(OPTION_NULL);
                        exit(EXIT_SUCCESS);
                    }
                }
            }
            OPTION_ERROR(); // Not found option
        }
        return 0; // normal
    }
    else
    {
        OPTION_ERROR();
    }
}

void HELP(char *option)
{
    char *callOptions[][OPTION_ALIAS] = {OPTION_ADD, OPTION_DIRECTOTY, OPTION_HELP, OPTION_REMOVE, OPTION_TREE};
    char *describeOption[OPTION_AMOUNT] =
        {"ADD <NAME> - create new file for saving processing of game",
         "DIR <PATH> - show files and subdirectories in directory of argument",
         "HELP - show usage",
         "REMOVE <PATH> - delete file of argument",
         "TREE <PATH> - show grahical struct of directory"};

    if (strcmp(OPTION_NULL, option) == 0)
    {
        puts("Usage:");
        for (int option = 0; option < OPTION_AMOUNT; option++)
        {
            putchar('\t');
            for (int alias = 0; alias < OPTION_ALIAS; alias++)
            {
                printf("%s", callOptions[option][alias]);
                printf(", "); // padding
            }
            printf("%s\n", describeOption[option]);
        }
    }
    else
    {
    }
}

void TREE(char *path) {}
void DIRECTORY(char *path) {}
void REMOVE(char *path) {}
void ADD(char *path) {}

void OPTION_ERROR()
{
    puts("Usage: .\\SolitaireCalculation.exe <option>\noption - \"help\"");
    exit(EXIT_FAILURE);
}