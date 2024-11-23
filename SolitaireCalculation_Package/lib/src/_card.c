#include <stdio.h>  // printf
#include <string.h> // strcpy
#include <stdlib.h> // rand
#include <time.h>   // time for srand

#include "../include/card.h"

#include "../include/font.h"
#include "../include/window.h"

extern _Font Font;

void generateNewStock(_Card *_originNode)
{
    char cardSuits[] = CARD_SUITS;
    char *cardRanks[] = CARD_RANKS;
    _Card *node = _originNode;
    for (int i = 0; i < CARD_AMOUNT; i++)
    {
        node->suit = cardSuits[i / RANK_AMOUNT];
        strcpy(node->rank, cardRanks[i % RANK_AMOUNT]);
        if (i != CARD_AMOUNT - 1)
        {
            node->next = malloc(sizeof(_Card));
            node = node->next;
        }
    }
    node->next = NULL;
}

void deleteStock(_Card *_originNode)
{
    _Card *currentNode = _originNode;
    _Card *nextNode;
    while (currentNode != NULL)
    {
        nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;
    }
}

void Shuffle(_Card *_originNode)
{
}

void printDeck(_Card *_originNode)
{
    _Card *currentNode = _originNode;
    while (currentNode != NULL)
    {
        printCard(*currentNode, 'c');
        puts("");
        currentNode = currentNode->next;
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
        printf("%s", card.rank);
        RESET_FONT;
    }
}
