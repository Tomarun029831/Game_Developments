#include <stdio.h>
#include <string.h> // strcmp
#include <stdlib.h> // exit, random
#include <time.h>   // time

#define OPTION_AMOUNT 6
#define OPTION_ALIAS 3

#define OPTION_NULL "NONOPTION"
#define OPTION_INVAIL NULL
#define OPTION_HELP {"-h", "help", "HELP"}          // help option
#define OPTION_TREE {"-t", "tree", "TREE"}          // show struct of path in data
#define OPTION_DIRECTOTY {"-d", "dir", "DIR"}       // show file or subdirectory in data
#define OPTION_REMOVE {"-rm", "remove", "REMOVE"}   // remove directory, file in data
#define OPTION_ADD {"-a", "add", "ADD"}             // create directory, file in data
#define OPTION_SETTING {"-s", "setting", "SETTING"} // User configs

const char *optionADD[] = OPTION_ADD;
const char *optionDIRECTORY[] = OPTION_DIRECTOTY;
const char *optionHELP[] = OPTION_HELP;
const char *optionREMOVE[] = OPTION_REMOVE;
const char *optionTREE[] = OPTION_TREE;
const char *optionSETTING[] = OPTION_SETTING;
const char **callOptions[] = {optionADD, optionDIRECTORY, optionHELP, optionREMOVE, optionTREE, optionSETTING};

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

// Options
void HELP(char *);
void TREE(char *);
void DIRECTORY(char *);
void REMOVE(char *);
void ADD(char *);
const char **CHECKOPTION(char *);
void *RETURN_FUNC_OPTION(char *);

// Setting Window
void SETTINGWINDOW();
void SETWINDOWSIZE(int, int);
void SETFONT(int, int, int);

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
        printf("\x1b[?25l\x1b[H\x1b[J"); // hide cursor, move it to HOME and delete right of cousor pos

        printf("\x1b[1;44;33m青文字、黄色背景\x1b[0m\n");
        printf("\x1b[44;1;33m青文字、黄色背景\x1b[0m\n");
        printf("\x1b[0;44;33m青文字、黄色背景\x1b[0m\n");

        printf("\x1b[1;31m太字の赤色文字\x1b[0m\n");
        printf("\x1b[4;32m下線付き緑色文字\x1b[0m\n");

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
    else if (fullOption == optionSETTING)
    {
        return SETTINGWINDOW;
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
         "-t <PATH>, tree <PATH>, TREE <PATH> - show grahical struct of directory",
         "-s, setting, SETTING - user configs"};

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
        else if (fullOption == optionSETTING)
        {
            printf("\t%s", describeOption[5]);
        }
    }
}

void TREE(char *path) { printf("TREE called with %s", path); }
void DIRECTORY(char *path) { printf("DIRECRORY called with %s", path); }
void REMOVE(char *path) { printf("REMOVE called with %s", path); }
void ADD(char *path) { printf("ADD called with %s", path); }

void SETTINGWINDOW() { printf("SETTING called"); }

void SETWINDOWSIZE(int width, int height)
{
}

/*
フォアグラウンド（文字色）コード
30  — 黒
31  — 赤
32  — 緑
33  — 黄
34  — 青
35  — マゼンタ
36  — シアン
37  — 白

バックグラウンド（背景色）コード
40  — 黒
41  — 赤
42  — 緑
43  — 黄
44  — 青
45  — マゼンタ
46  — シアン
47  — 白

明るいフォアグラウンド（文字色）コード
90  — 明るい黒（暗い灰色）
91  — 明るい赤
92  — 明るい緑
93  — 明るい黄
94  — 明るい青
95  — 明るいマゼンタ
96  — 明るいシアン
97  — 明るい白

明るいバックグラウンド（背景色）コード
100 — 明るい黒（暗い灰色）
101 — 明るい赤
102 — 明るい緑
103 — 明るい黄
104 — 明るい青
105 — 明るいマゼンタ
106 — 明るいシアン
107 — 明るい白


0 — リセット（Reset）
1 — 太字（Bold）
2 — 薄い文字（Faint）
3 — 斜体（Italic）
4 — 下線（Underline）
5 — 点滅（Blink）
6 — 速い点滅（Rapid Blink）
7 — 反転（Inverse）
8 — 非表示（Hidden）
9 — 打ち消し線（Strike-through）

*/

void SETFONT(int foreground, int background_color, int attritude)
{
}

void opERROR()
{
    puts("Usage: .\\SolitaireCalculation.exe <option>\noption - \"help\"");
    exit(EXIT_FAILURE);
}