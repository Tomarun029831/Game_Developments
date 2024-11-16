#include <stdio.h>
#include <direct.h> // mkdir, rmdir
#include <dirent.h> // directory search
#include <string.h> // strcmp
#include <stdlib.h> // exit, random
#include <time.h>   // time
#include "../lib/include/options.h"
#include "../lib/include/settings.h"
#include "../lib/include/window.h"

// 'S', 'D', 'H', 'C'
int cardRanks[] = {'S', 'D', 'H', 'C'};
// 'A', '2', '3', '4', '5', '6', '7', '8', '9', "10", 'J', 'Q', 'K'
int cardSuits[] = {'A', 2, 3, 4, 5, 6, 7, 8, 9, 10, 'J', 'Q', 'K'};
_Settings Settings;

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
    // loadSettings("/defaults");
    loadSettings("USER0");
    initializeWindow();

    StartWindow((const char **)&argv[1]);
    solitaireCalculation();

    RESET_FONT;
    return 0;
}

void solitaireCalculation()
{
    initializeGame();

    puts("SolitaireCalculation starts\n");
}

void initializeGame()
{
}

void initializeWindow()
{
}
