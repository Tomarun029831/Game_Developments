#pragma once

#define INVAIL_MARK '/'
#define DEFAULT_PATH "/defaults"
#define MAX_LENGTH_PATH 256
#define RESET_FONT setFontAttributes(-1, -1, -1)

// loadSettings
#define LOAD_SUCCESS 0
#define LOAD_FAILURE -1

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
int loadSettings(const char *const _userName);
void loadFont(const char *const _font);
