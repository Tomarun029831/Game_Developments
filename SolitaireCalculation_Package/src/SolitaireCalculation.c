#include <stdio.h>
#include <direct.h> // mkdir, rmdir
#include <dirent.h> // directory search
#include <string.h> // strcmp
#include <stdlib.h> // exit, random
#include <time.h>   // time
#include <locale.h> // UTF-8
#include "../lib/include/options.h"
#include "../lib/include/settings.h"
#include "../lib/include/window.h"
#include "../lib/include/card.h"

extern _Settings Settings;

// Initialize
void initializeWindow();
void initializeGame(_Card *deck);

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

// gcc ./src/SolitaireCalculation.c ./lib/src/*.c -o SolitaireCalculation && ./SolitaireCalculation

int main(int argc, char **argv)
{
    // initializeWindow();

    // StartWindow((const char **)&argv[1]);
    solitaireCalculation();

    RESET_FONT;
    return 0;
}

void solitaireCalculation()
{
    _Card deck[CARD_AMOUNT];
    initializeGame(deck);

    puts("SolitaireCalculation starts\n");
}

void initializeGame(_Card *deck)
{
    generateNewStock(deck);
    Shuffle(deck);
}

void initializeWindow()
{
    setlocale(LC_ALL, ".UTF-8");
    loadSettings("/defaults", 'r');
}
