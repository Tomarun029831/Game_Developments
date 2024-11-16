#pragma once
#include <stdio.h>
#include "./options.h"
#include "./settings.h"

#define T_CLEAR printf("\x1b[?25l\x1b[H\x1b[J") // hide cursor, move it to HOME and delete right of cousor pos
#define TC_END printf("\x1b[?25h")              // show cursor

// To Enter Game
void StartWindow(const char **);
// Setting Window
void showSettingsWindow();
void SetWindowSize(int, int);
void setFontAttributes(int, int, int);

void StartWindow(const char **_optionv)
{
    // found option
    if (_optionv[0] == OPTION_FAILURE)
    {
        T_CLEAR;

        // User ID Input and Password
        // Play or Settings

        TC_END;
        return; // Enter Game
    }
    else
    {
        executeOption(_optionv);
    }
}

void showSettingsWindow()
{
    T_CLEAR;
    // FILE fp;
    char *s;
    printf("ID:%s\nPassword:%s\nFont:%s\nWight:%d\nHeight:%d\n",
           Settings.Id, Settings.Password, Settings.Window.Font, Settings.Window.Width, Settings.Window.Height);
    printf("<Option> <Object>\tPut a SPACE between <Option> and <Object>\n");
    TC_END;

    scanf_s("%s", s);
}

void SetWindowSize(int width, int height)
{
}

// 0 <= style <= 9, 30 <= foreground <= 37 or 90 <= foreground <= 97, 40 <= background <= 47 or 100 <= background <= 107
void setFontAttributes(int style, int foreground, int background)
{
    int isStyleValid = (style >= 0 && style <= 9);
    int isForegroundValid = ((30 <= foreground && foreground <= 39) || (90 <= foreground && foreground <= 97));
    int isBackgroundValid = ((40 <= background && background <= 49) || (100 <= background && background <= 107));

    if (style == -1 && foreground == -1 && background == -1)
    {
        printf("\x1b[0m");
        return;
    }

    printf("\x1b[");

    if (isStyleValid)
        printf("%d", style);

    if (isForegroundValid)
    {
        if (isStyleValid)
            printf(";");
        printf("%d", foreground);
    }

    if (isBackgroundValid)
    {
        if (isStyleValid || isForegroundValid)
            printf(";");
        printf("%d", background);
    }

    printf("m");
}