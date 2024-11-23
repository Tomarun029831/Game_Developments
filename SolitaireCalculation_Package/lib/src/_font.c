#include <stdio.h>
#include "../include/font.h"

void loadFont(const char *const _font)
{
}

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