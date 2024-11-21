#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../include/card.h"

void Shuffle(_Card *_stock)
{
    _Card tmpCard;
    srand(time(NULL));
    for (int i = CARD_AMOUNT - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        _Card temp = _stock[i];
        _stock[i] = _stock[j];
        _stock[j] = temp;
    }
}

void generateNewStock(_Card *_stock)
{
    for (int i = 0; i < CARD_AMOUNT; i++)
    {
        _stock[i].suit = cardSuits[i / RANK_AMOUNT];
        strcpy(_stock[i].rank, cardRanks[i % RANK_AMOUNT]);
    }
}
void printDeck(_Card *_stock)
{
    for (int i = 0; i < CARD_AMOUNT; i++)
    {
        printf("%d: %c-%s\n", i + 1, _stock[i].suit, _stock[i].rank);
    }
}