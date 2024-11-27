#pragma once
#include "./card.h"

typedef struct
{
    int amountCards;
    _Card showup;
    char leadRanks[SUIT_AMOUNT][3];
    _Card *leadCards[SUIT_AMOUNT];
} _Statu;

// Control State
void makeStuck(int _pointS);
void disCard(int _pointL);
void disStuck(int _pointS, int _pointL);
void Undo();
void EndGame();
