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

typedef struct s_chain_card _ChainCard;
typedef struct s_card _Card;

typedef struct s_card
{
    char suit;    // 'S', 'D', 'H', 'C'
    char rank[3]; // "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"
} _Card;

typedef struct s_chain_card
{
    _Card card;
    _ChainCard *next;
} _ChainCard;

// Control Cards
void generateNewStock(_ChainCard *_originNode);
void deleteStock(_ChainCard *_originNode);
void ShuffleStock(_ChainCard **_originNode);
// Print Cards
void printChainCard(_ChainCard card, char mode);
void printCard(_Card card, char mode);
void printDeck(_ChainCard *_originNode);
void printRank(char *_rank);
