#include <stdio.h>
#include <direct.h> // mkdir, rmdir
#include <dirent.h> // directory search
#include <string.h> // strcmp
#include <stdlib.h> // exit, random
#include <time.h>   // time
#include <locale.h> // UTF-8

#include "../lib/include/card.h"
#include "../lib/include/font.h"
#include "../lib/include/options.h"
#include "../lib/include/settings.h"
#include "../lib/include/statu.h"
#include "../lib/include/window.h"

extern _Settings Settings;
extern _Statu Statu;

// Initialize
void initializeWindow();
void initializeGame(_ChainCard *deck);

// Enter Game
void solitaireCalculation();

// Check Action
int isAction(char *_action);

// Input
char *InputGuard(char *_input);
void convertInputToAction(char *_input);

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

// gcc ./src/SolitaireCalculation.c ./lib/src/*.c -o SolitaireCalculation && ./SolitaireCalculation

int main(int argc, char **argv)
{
    initializeWindow();

    // loginWindow((const char **)&argv[1]);
    solitaireCalculation();

    RESET_FONT;
    return 0;
}

void solitaireCalculation()
{
    _ChainCard *originNode = malloc(sizeof(_ChainCard));
    initializeGame(originNode);

    do
    {
        Showup(originNode);
        showTable();
        break;
    } while (Statu.leadRanks[0] == Statu.leadRanks[1] &&
             Statu.leadRanks[1] == Statu.leadRanks[2] &&
             Statu.leadRanks[2] == Statu.leadRanks[3] &&
             Statu.leadRanks[3] == NULL);

    puts("SolitaireCalculation starts\n");
    char *input = malloc(sizeof(char) * 5);
    convertInputToAction(InputGuard(input));
    free(input);
    deleteStock(originNode);
    originNode = NULL;
}

void initializeGame(_ChainCard *originNode)
{
    generateNewStock(originNode);
    ShuffleStock(&originNode);
}

void initializeWindow()
{
    setlocale(LC_ALL, ".UTF-8");
    loadSettings("/defaults", 'r');
}

#define MAKESTUCK "ms"
#define DISCARD "dc"
#define DISSTUCK "ds"
#define UNDO "ud"
#define ENDGAME "ed"

#define ACTION_ALIAS {MAKESTUCK, DISCARD, DISSTUCK, UNDO, ENDGAME};
// "ms", "dc", "ds", "ud", "ed"
char *actionAlias[] = ACTION_ALIAS;

int isAction(char *_action)
{
    for (int i = 1; i <= 5; i++)
        if (strcmp(_action, actionAlias[i - 1]) == 0)
            return 1;
    return 0;
}

char *InputGuard(char *_input)
{
    char action[3];
    int len;
    do
    {
        TR_CLEAR;
        printf("Action: ");
        scanf("%s", _input);
        UP_CURSOR;
        if (strcmp(UNDO, _input) == 0)
            return _input;
        else if (strcmp(ENDGAME, _input) == 0)
            return _input;

        len = strlen(_input);
        strncpy(action, _input, 2);

        if (len == 2)
        {
            getchar();
            printf("\033[12G");
            _input[2] = getchar();
            UP_CURSOR;
            _input[3] = '\0';
            if (strcmp(MAKESTUCK, action) == 0 || strcmp(DISCARD, action) == 0)
                return _input;
            ++len;
        }

        if (len == 3 && strcmp(DISSTUCK, action) == 0)
        {
            getchar();
            printf("\033[14G");
            _input[3] = getchar();
            UP_CURSOR;
            _input[4] = '\0';
            ++len;
        }
    } while (!isAction(action) ||
             !(2 <= len && len <= 4) ||
             !('1' <= _input[2] && _input[2] <= '4') ||
             !('1' <= _input[3] && _input[3] <= '4'));
    DOWN_CURSOR;
    return _input;
}

void convertInputToAction(char *_input)
{
    char action[3];
    strncpy(action, _input, 2);
    if (strcmp(MAKESTUCK, action) == 0)
    {
        char point_S[2];
        strncpy(point_S, &_input[2], 1);
        MakeStuck(atoi(point_S));
    }
    else if (strcmp(DISCARD, action) == 0)
    {
        char point_L[2];
        strncpy(point_L, &_input[2], 1);
        DisCard(atoi(point_L));
    }
    else if (strcmp(DISSTUCK, action) == 0)
    {
        char point_S[2], point_L[2];

        strncpy(point_S, &_input[2], 1);
        strncpy(point_L, &_input[3], 1);
        DisStuck(atoi(point_S), atoi(point_L));
    }
    else if (strcmp(UNDO, action) == 0)
    {
        Undo();
    }
    else if (strcmp(ENDGAME, action) == 0)
    {
        EndGame();
    }
}
