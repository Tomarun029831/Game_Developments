#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/options.h"
#include "../include/settings.h"
#include "../include/window.h"

_Settings Settings;

void StartWindow(const char **_optionv)
{
    char userID[MAX_LENGTH_PATH] = "";
    char password[MAX_LENGTH_PATH] = "";
    // found option
    if (_optionv[0] == OPTION_FAILURE)
    {
        // T_CLEAR;
        // TC_END;
        printf("ID:%s\nPassword:%s\nFont:%s\nWight:%d\nHeight:%d\n",
               Settings.Id, Settings.Password, Settings.Window.Font, Settings.Window.Width, Settings.Window.Height);

        printf("please input userId and password\n");

        while (loadSettings(userID, 'r') != LOAD_SUCCESS)
        {
            printf("userID: ");
            scanf_s("%s", userID, sizeof(userID));
            // if (strchr(userID, INVAIL_MARK) != NULL)
            //     exit(EXIT_FAILURE);
        }

        while (strcmp(password, Settings.Password) != 0)
        {
            printf("password: ");
            scanf_s("%s", password, sizeof(password));
            if (strchr(password, INVAIL_MARK) != NULL)
                exit(EXIT_FAILURE);
        }

        // strcpy(Settings.Id, "one");
        // loadSettings("/defaults", 's');

        printf("ID:%s\nPassword:%s\nFont:%s\nWight:%d\nHeight:%d\n",
               Settings.Id, Settings.Password, Settings.Window.Font, Settings.Window.Width, Settings.Window.Height);

        return; // Enter Game
    }
    else
    {
        executeOption(_optionv);
    }
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