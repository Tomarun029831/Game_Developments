#pragma once

#define MAX_LENGTH_PATH 256
#define RESET_FONT setFontAttributes(-1, -1, -1)

typedef struct
{
    char *Style;
    char *Foreground;
    char *Background;
} ColorAttritude;

typedef struct
{
    char *name;
    ColorAttritude ShowUp;
    ColorAttritude Makestack;
    ColorAttritude Discard;
    ColorAttritude Disstack;
    ColorAttritude Undo;
    ColorAttritude Endgame;
} _Font;

typedef struct
{
    _Font Font;
    int Width;
    int Height;
} _Window;

typedef struct
{
    char Id[MAX_LENGTH_PATH];
    char Password[MAX_LENGTH_PATH];
    _Window Window;
} _Settings;

// load settings
void loadSettings(const char *const _userName);
void loadFont(const char *const _font);
