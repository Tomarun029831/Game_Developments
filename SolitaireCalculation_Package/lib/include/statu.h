#pragma once
#include "./card.h"

typedef struct
{
    int amountCards;
    _Card showup;
    char leadRanks[SUIT_AMOUNT][3];
    _ChainCard *leadCards[SUIT_AMOUNT];
} _Statu;

// Control State
void Showup(_ChainCard *Node);
void MakeStuck(int _pointS);
void DisCard(int _pointL);
void DisStuck(int _pointS, int _pointL);
void Undo();
void EndGame();
