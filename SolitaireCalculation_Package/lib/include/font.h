#pragma once
#include "./settings.h"
#define FONT_POSITION \
    {                 \
    }
#define FONT_ATTRITUDE {"FOREGROUND", "BACKGROUND", "STYLE"}

typedef struct
{
    int Style;
    int Foreground;
    int Background;
} ColorAttritude;

typedef struct
{
    ColorAttritude Spead;
    ColorAttritude Diamond;
    ColorAttritude Heart;
    ColorAttritude Clover;
} _suitFont;

typedef struct
{
    _suitFont Suit;
} _cardFont;

typedef struct
{
    char name[MAX_LENGTH_PATH];
    ColorAttritude Turn;
    ColorAttritude Roof;
    ColorAttritude Point;
    ColorAttritude Pillar;
    ColorAttritude Number_BP;
    ColorAttritude Lead;
    ColorAttritude Upper_bans;
    ColorAttritude Showup;
    ColorAttritude Toppings;
    ColorAttritude Under_bans;
    ColorAttritude Stuck;
    ColorAttritude Makestuck;
    ColorAttritude Discard;
    ColorAttritude Disstuck;
    ColorAttritude Undo;
    ColorAttritude Endgame;
    _cardFont Card;
} _Font;

void loadFont(const char *const _font);

// 0 <= style <= 9, 30 <= foreground <= 37 or 90 <= foreground <= 97, 40 <= background <= 47 or 100 <= background <= 107
void setFontAttributes(int style, int foreground, int background);

#define RESET_FONT setFontAttributes(-1, -1, -1)
