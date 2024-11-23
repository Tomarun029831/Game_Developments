#include <stdio.h>  // printf
#include <string.h> // strcpy
#include <stdlib.h> // rand
#include <time.h>   // time for srand
#include "../include/card.h"
#include "../include/font.h"
#include "../include/window.h"

void generateNewStock(_Card *_stock)
{
    char cardSuits[] = CARD_SUITS;
    char *cardRanks[] = CARD_RANKS;
    for (int i = 0; i < CARD_AMOUNT; i++)
    {
        _stock[i].suit = cardSuits[i / RANK_AMOUNT];
        strcpy(_stock[i].rank, cardRanks[i % RANK_AMOUNT]);
    }
}

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

void printDeck(_Card *_stock)
{
    for (int i = 0; i < CARD_AMOUNT; i++)
    {
        printf("%d: %c-%s\n", i + 1, _stock[i].suit, _stock[i].rank);
    }
}

void printCard(_Card card)
{
    printSuit(card.suit);
    setFontAttributes(-1, 33, -1);
    printf("%c", CONNECTTION_MARK);
    RESET_FONT;
    printRank(card.rank);
}

void printSuit(char _suit)
{
    setFontAttributes(-1, 36, -1);
    printf("%c", _suit);
    RESET_FONT;
}

void printRank(char *_rank)
{
    setFontAttributes(-1, 35, -1);
    printf("%2s", _rank);
    RESET_FONT;
}
