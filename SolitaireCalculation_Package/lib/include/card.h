#pragma once

#define SUIT_AMOUNT 4
#define RANK_AMOUNT 13
#define CARD_AMOUNT 52

#define SPEAD 'S'
#define DIAMOND 'D'
#define HEART 'H'
#define CLUB 'C'
#define CARD_SUITS {SPEAD, DIAMOND, HEART, CLUB}
#define CARD_RANKS {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"}

typedef struct s_card _Card;

typedef struct s_card
{
    char suit;    // 'S', 'D', 'H', 'C'
    char rank[3]; // "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"
    _Card *next;
} _Card;

// Control Cards
void generateNewStock(_Card *_originNode);
void deleteStock(_Card *_originNode);
void ShuffleStock(_Card **_originNode);
void printDeck(_Card *_originNode);

// Print Cards
void printCard(_Card card, char mode);
