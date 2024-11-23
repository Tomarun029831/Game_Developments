#pragma once

#include "./max_length_path.h"

#define FONT_POSITION {"Turn",       \
                       "Roof",       \
                       "Point",      \
                       "Pillar",     \
                       "Number_BP",  \
                       "Lead",       \
                       "Upper_bans", \
                       "Showup",     \
                       "Toppings",   \
                       "Under_bans", \
                       "Stuck",      \
                       "Makestuck",  \
                       "Discard",    \
                       "Disstuck",   \
                       "Undo",       \
                       "Endgame",    \
                       "Card"}

#define FONT_ATTRITUDE {"FOREGROUND", "BACKGROUND", "STYLE"}

typedef struct
{
    int Style;
    int Foreground;
    int Background;
} _ColorAttritude;

typedef struct
{
    _ColorAttritude Spead;
    _ColorAttritude Diamond;
    _ColorAttritude Heart;
    _ColorAttritude Club;
} _suitFont;

typedef struct
{
    _suitFont Suit;
    _ColorAttritude ConnectionMark;
} _cardFont;

typedef struct _font
{
    char name[MAX_LENGTH_PATH];
    _ColorAttritude Turn;
    _ColorAttritude Roof;
    _ColorAttritude Point;
    _ColorAttritude Pillar;
    _ColorAttritude Number_BP;
    _ColorAttritude Lead;
    _ColorAttritude Upper_bans;
    _ColorAttritude Showup;
    _ColorAttritude Toppings;
    _ColorAttritude Under_bans;
    _ColorAttritude Stuck;
    _ColorAttritude Makestuck;
    _ColorAttritude Discard;
    _ColorAttritude Disstuck;
    _ColorAttritude Undo;
    _ColorAttritude Endgame;
    _cardFont Card;
} _Font;

void loadFont(const char *const _font);

// 0 <= style <= 9, 30 <= foreground <= 37 or 90 <= foreground <= 97, 40 <= background <= 47 or 100 <= background <= 107
void setFontAttributes(int style, int foreground, int background);

#define RESET_FONT setFontAttributes(-1, -1, -1)
