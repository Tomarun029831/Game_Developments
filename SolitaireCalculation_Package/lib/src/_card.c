#include <stdio.h>  // printf
#include <string.h> // strcpy
#include <stdlib.h> // rand
#include <time.h>   // time for srand

#include "../include/card.h"

#include "../include/font.h"
#include "../include/window.h"

extern _Font Font;

void generateNewStock(_ChainCard *_originNode)
{
    char cardSuits[] = CARD_SUITS;
    char *cardRanks[] = CARD_RANKS;
    _ChainCard *node = _originNode;
    for (int i = 0; i < CARD_AMOUNT; i++)
    {
        node->card.suit = cardSuits[i / RANK_AMOUNT];
        strcpy(node->card.rank, cardRanks[i % RANK_AMOUNT]);
        if (i != CARD_AMOUNT - 1)
        {
            node->next = malloc(sizeof(_ChainCard));
            node = node->next;
        }
    }
    node->next = NULL;
}

void deleteStock(_ChainCard *_originNode)
{
    _ChainCard *currentNode = _originNode;
    _ChainCard *nextNode;
    while (currentNode != NULL)
    {
        nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;
    }
    _originNode = NULL;
}

void ShuffleStock(_ChainCard **_originNode)
{
    _ChainCard *p_card[CARD_AMOUNT];
    p_card[0] = *_originNode;
    int i = 0;

    while (p_card[i++]->next != NULL)
        p_card[i] = p_card[i - 1]->next;

    srand(time(NULL));
    for (int i = CARD_AMOUNT - 1; i > 0; i--)
    {
        int index = rand() % (i + 1);
        _ChainCard *tmp = p_card[i];
        p_card[i] = p_card[index];
        p_card[index] = tmp;
    }

    for (int i = 0; i < CARD_AMOUNT - 1; i++)
        p_card[i]->next = p_card[i + 1];
    p_card[CARD_AMOUNT - 1]->next = NULL;

    *_originNode = p_card[0];
}

void printDeck(_ChainCard *_originNode)
{
    _ChainCard *currentNode = _originNode;
    while (currentNode != NULL)
    {
        printChainCard(*currentNode, 'c');
        puts("");
        currentNode = currentNode->next;
    }
}

// mode - 'c': card, 's': suit, 'r': rank
void printChainCard(_ChainCard card, char mode)
{
    _ColorAttritude ColorAttr;

    Font.Card.Suit.Spead.Background = 33;
    Font.Card.Suit.Spead.Foreground = 96;
    Font.Card.Suit.Spead.Style = 33;

    Font.Card.Suit.Diamond.Background = 33;
    Font.Card.Suit.Diamond.Foreground = 31;
    Font.Card.Suit.Diamond.Style = 33;

    Font.Card.Suit.Heart.Background = 33;
    Font.Card.Suit.Heart.Foreground = 31;
    Font.Card.Suit.Heart.Style = 33;

    Font.Card.Suit.Club.Background = 33;
    Font.Card.Suit.Club.Foreground = 96;
    Font.Card.Suit.Club.Style = 33;

    Font.Card.ConnectionMark.Style = 33;
    Font.Card.ConnectionMark.Foreground = 33;
    Font.Card.ConnectionMark.Background = 33;

    switch (card.card.suit)
    {
    case SPEAD:
        ColorAttr.Background = Font.Card.Suit.Spead.Background;
        ColorAttr.Foreground = Font.Card.Suit.Spead.Foreground;
        ColorAttr.Style = Font.Card.Suit.Spead.Style;
        break;
    case DIAMOND:
        ColorAttr.Background = Font.Card.Suit.Diamond.Background;
        ColorAttr.Foreground = Font.Card.Suit.Diamond.Foreground;
        ColorAttr.Style = Font.Card.Suit.Diamond.Style;
        break;
    case HEART:
        ColorAttr.Background = Font.Card.Suit.Heart.Background;
        ColorAttr.Foreground = Font.Card.Suit.Heart.Foreground;
        ColorAttr.Style = Font.Card.Suit.Heart.Style;
        break;
    case CLUB:
        ColorAttr.Background = Font.Card.Suit.Club.Background;
        ColorAttr.Foreground = Font.Card.Suit.Club.Foreground;
        ColorAttr.Style = Font.Card.Suit.Club.Style;
        break;
    }

    if (mode == 'c' || mode == 's')
    {
        setFontAttributes(ColorAttr.Style, ColorAttr.Foreground, ColorAttr.Background);
        printf("%c", card.card.suit);
        RESET_FONT;
    }

    if (mode == 'c')
    {
        setFontAttributes(Font.Card.ConnectionMark.Style, Font.Card.ConnectionMark.Foreground, Font.Card.ConnectionMark.Background);
        printf("%c", CONNECTION_MARK);
        RESET_FONT;
    }

    if (mode == 'c' || mode == 'r')
    {
        setFontAttributes(ColorAttr.Style, ColorAttr.Foreground, ColorAttr.Background);
        printRank(card.card.rank);
        RESET_FONT;
    }
}

// mode - 'c': card, 's': suit, 'r': rank
void printCard(_Card card, char mode)
{
    _ColorAttritude ColorAttr;

    Font.Card.Suit.Spead.Background = 33;
    Font.Card.Suit.Spead.Foreground = 96;
    Font.Card.Suit.Spead.Style = 33;

    Font.Card.Suit.Diamond.Background = 33;
    Font.Card.Suit.Diamond.Foreground = 31;
    Font.Card.Suit.Diamond.Style = 33;

    Font.Card.Suit.Heart.Background = 33;
    Font.Card.Suit.Heart.Foreground = 31;
    Font.Card.Suit.Heart.Style = 33;

    Font.Card.Suit.Club.Background = 33;
    Font.Card.Suit.Club.Foreground = 96;
    Font.Card.Suit.Club.Style = 33;

    Font.Card.ConnectionMark.Style = 33;
    Font.Card.ConnectionMark.Foreground = 33;
    Font.Card.ConnectionMark.Background = 33;

    switch (card.suit)
    {
    case SPEAD:
        ColorAttr.Background = Font.Card.Suit.Spead.Background;
        ColorAttr.Foreground = Font.Card.Suit.Spead.Foreground;
        ColorAttr.Style = Font.Card.Suit.Spead.Style;
        break;
    case DIAMOND:
        ColorAttr.Background = Font.Card.Suit.Diamond.Background;
        ColorAttr.Foreground = Font.Card.Suit.Diamond.Foreground;
        ColorAttr.Style = Font.Card.Suit.Diamond.Style;
        break;
    case HEART:
        ColorAttr.Background = Font.Card.Suit.Heart.Background;
        ColorAttr.Foreground = Font.Card.Suit.Heart.Foreground;
        ColorAttr.Style = Font.Card.Suit.Heart.Style;
        break;
    case CLUB:
        ColorAttr.Background = Font.Card.Suit.Club.Background;
        ColorAttr.Foreground = Font.Card.Suit.Club.Foreground;
        ColorAttr.Style = Font.Card.Suit.Club.Style;
        break;
    }

    if (mode == 'c' || mode == 's')
    {
        setFontAttributes(ColorAttr.Style, ColorAttr.Foreground, ColorAttr.Background);
        printf("%c", card.suit);
        RESET_FONT;
    }

    if (mode == 'c')
    {
        setFontAttributes(Font.Card.ConnectionMark.Style, Font.Card.ConnectionMark.Foreground, Font.Card.ConnectionMark.Background);
        printf("%c", CONNECTION_MARK);
        RESET_FONT;
    }

    if (mode == 'c' || mode == 'r')
    {
        setFontAttributes(ColorAttr.Style, ColorAttr.Foreground, ColorAttr.Background);
        printRank(card.rank);
        RESET_FONT;
    }
}

void printRank(char *_rank)
{
    printf("%2s", _rank);
}
