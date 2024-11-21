#pragma once
#include "./card.h"

typedef struct
{
    int amountCards;
    _Card showup;
    _Card leadCards[SUIT_AMOUNT];
} _Statu;