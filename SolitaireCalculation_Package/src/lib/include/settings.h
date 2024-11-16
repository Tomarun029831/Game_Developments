#pragma once

#define MAX_LENGTH_PATH 256
#define ASSIGN_OPERATER ':'
#define STARTBLOCK '{'
#define ENDBLOCK '}'
#define BUFFERABLE target[0] != ASSIGN_OPERATER &&target[0] != STARTBLOCK &&target[0] != ENDBLOCK &&target[0] != ' ' && target[0] != '\n'
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

_Settings Settings;

// load settings
void loadSettings(const char *const _userName);
void loadFont(const char *const _font);
void colonOperater(char *, FILE *const);
void enterBlocks(char *, FILE *const);
void analyzeSettingsFile(FILE *const _fp);
