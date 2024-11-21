#pragma once

#define SUIT_AMOUNT 4
#define RANK_AMOUNT 13
#define CARD_AMOUNT 52

#define CARD_SUITS {'S', 'D', 'H', 'C'}
#define CARD_RANKS {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"}

typedef struct
{
    char suit;    // 'S', 'D', 'H', 'C'
    char rank[3]; // 'A', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K'
} _Card;

void generateNewStock(_Card *_stock);
void Shuffle(_Card *_stock);
// void printDeck(_Card *_stock);