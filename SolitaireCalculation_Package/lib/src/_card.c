#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../include/card.h"
#include "../include/font.h"

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
    // 'S', 'D', 'H', 'C'
    char cardSuits[] = CARD_SUITS;
    // 'A', '2', '3', '4', '5', '6', '7', '8', '9', "10", 'J', 'Q', 'K'
    char *cardRanks[] = CARD_RANKS;
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

void printCard(_Card card)
{
    printSuit(card);
    setFontAttributes(-1, 33, -1);
    printf("%c", CONNECTTION_MARK);
    RESET_FONT;
    printRank(card);
}

void printRank(_Card card)
{
    setFontAttributes(-1, 35, -1);
    printf("%2s", card.rank);
    RESET_FONT;
}

void printSuit(_Card card)
{
    setFontAttributes(-1, 36, -1);
    printf("%c", card.suit);
    RESET_FONT;
}