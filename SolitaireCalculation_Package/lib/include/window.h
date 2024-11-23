#pragma once

// login
#define INVAIL_MARK '/'
void loginWindow(const char **_optionv); // Setting Window

// escape sequence
#define T_CLEAR printf("\x1b[?25l\x1b[H\x1b[J") // hide cursor, move it to HOME and delete right of cousor pos
#define TR_CLEAR printf("\033[K")               //
#define TC_END printf("\x1b[?25h")              // show cursor
#define UP_CURSOR printf("\033[A")              // set cursor above currently line
#define DOWN_CURSOR printf("\033[D")            // set cursor below currently line

// Game Codinates
#define ROOF "_:=^=:_------_:=^=:_------_:=^=:_------_:=^=:_"
#define UPPER_BANS ".-----."
#define TOPPINGS '|'
#define UNDER_BANS "'-----'"
#define PILLAR '|'
#define CONNECTION_MARK '_'
#define STOCK_MARK '$'
#define STRING_POINT "point:"
#define STRING_LEAD "lead:"
#define STRING_STUCK "stuck:"

// To Enter Game
void SetWindowSize(int width, int height);
void setFontAttributes(int style, int foreground, int background);

// Show Game Table
void showTable();

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

*/
