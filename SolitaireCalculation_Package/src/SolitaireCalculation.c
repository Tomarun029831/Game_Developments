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
    initializeWindow();

    // loginWindow((const char **)&argv[1]);
    solitaireCalculation();

    RESET_FONT;
    return 0;
}

void solitaireCalculation()
{
    _Card *originNode = malloc(sizeof(_Card));
    initializeGame(originNode);

    puts("SolitaireCalculation starts\n");
}

void initializeGame(_Card *originNode)
{
    generateNewStock(originNode);
    ShuffleStock(&originNode);
    printDeck(originNode);
    deleteStock(originNode);
}

void initializeWindow()
{
    setlocale(LC_ALL, ".UTF-8");
    loadSettings("/defaults", 'r');
}
