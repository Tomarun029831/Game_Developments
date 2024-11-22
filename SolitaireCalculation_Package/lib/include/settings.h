#pragma once

#define INVAIL_MARK '/'
#define DEFAULT_PATH "/defaults"
#define MAX_LENGTH_PATH 256
#define NOTBUFFERABLE {ASSIGN_OPERATER, STARTBLOCK, ENDBLOCK, ' ', '\n', '\r', '\0'}
#define SETTINGS_ATTRITUDE {"ID", "PASSWORD", "FONT", "WIDTH", "HEIGHT"}
#define FONT_POSITION \
    {                 \
    }
#define FONT_ATTRITUDE {"FOREGROUND", "BACKGROUND", "STYLE"}

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
int loadSettings(const char *const _userName, const char load_mode);
void loadFont(const char *const _font);

// analyze string
void analyzeSettings(char *_str, char _mode);

//
int count_figures(int n);