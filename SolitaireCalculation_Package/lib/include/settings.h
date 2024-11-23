#pragma once

#include "./max_length_path.h"
#include "./font.h"

#define DEFAULT_PATH "/defaults"
#define NOTBUFFERABLE {ASSIGN_OPERATER, STARTBLOCK, ENDBLOCK, ' ', '\n', '\r', '\0'}
#define SETTINGS_ATTRITUDE {"ID", "PASSWORD", "FONT", "WIDTH", "HEIGHT"}

// loadSettings
#define LOAD_SUCCESS 0
#define LOAD_FAILURE -1

typedef struct
{
    _Font Font;
    int Width;
    int Height;
} _Window;

typedef struct _settings
{
    char Id[MAX_LENGTH_PATH];
    char Password[MAX_LENGTH_PATH];
    _Window Window;
} _Settings;

// load settings
int loadSettings(const char *const _userName, const char load_mode);

// analyze string
void analyzeSettings(char *_str, char _mode);

//
int count_figures(int n);