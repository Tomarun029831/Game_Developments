#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/options.h"
#include "../include/settings.h"
#include "../include/window.h"
#include "../include/statu.h"

extern _Settings Settings;
extern _Statu Statu;

void printCard(_Card card);
void printRank(_Card card);
void printSuit(_Card card);

void printCard(_Card card)
{
    printSuit(card);
    setFontAttributes(-1, 37, -1);
    printf("_");
    RESET_FONT;
    printRank(card);
}

void printRank(_Card card)
{
    setFontAttributes(-1, 39, -1);
    printf("%2s", card.rank);
    RESET_FONT;
}
void printSuit(_Card card)
{
    setFontAttributes(-1, 39, -1);
    printf("%c", card.suit);
    RESET_FONT;
}

void loginWindow(const char **_optionv)
{
    char userID[MAX_LENGTH_PATH] = "";
    char password[MAX_LENGTH_PATH] = "";
    // found option
    if (_optionv[0] == OPTION_FAILURE)
    {
        // T_CLEAR;
        // TC_END;
        printf("1- ID:%s\nPassword:%s\nFont:%s\nWight:%d\nHeight:%d\n",
               Settings.Id, Settings.Password, Settings.Window.Font.name, Settings.Window.Width, Settings.Window.Height);

        puts("please input userId and password");

        do
        {
            printf("userID: \033[K");
            scanf_s("%s", userID, sizeof(userID));
            UP_CURSOR;
            // if (strchr(userID, INVAIL_MARK) != NULL)
            // {
            //     RESET_FONT;
            //     exit(EXIT_FAILURE);
            // }
        } while (loadSettings(userID, 'r') != LOAD_SUCCESS);

        puts("");

        setFontAttributes(8, -1, -1);
        do
        {
            RESET_FONT;
            printf("password: \033[K");
            setFontAttributes(8, -1, -1); // Hide input
            scanf_s("%s", password, sizeof(password));
            UP_CURSOR;
            if (strchr(password, INVAIL_MARK) != NULL)
            {
                RESET_FONT;
                exit(EXIT_FAILURE);
            }
        } while (strcmp(password, Settings.Password) != 0);
        RESET_FONT;

        // strcpy(Settings.Id, "abcdefghijk");
        // strcpy(Settings.Password, "0123456789");
        // strcpy(Settings.Window.Font.name, "mailyoUnchi");
        // Settings.Window.Height = 10;
        // Settings.Window.Width = 6;

        // loadSettings("/defaults", 's');

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

void showTable()
{
    //                                            turn_  1
    //              .------_:=^=:_------_:=^=:_------_:=^=:_------_:=^=:_------.
    // point:              |  1  |      |  2  |      |  3  |      |  4  |
    //     lead:     .-----.      .-----.      .-----.      .-----.
    // $ C_ K        |   2 | S_ A |   4 | D_ 2 |   6 | H_ 3 |   8 | C_ 4
    //               '-----'      '-----'      '-----'      '-----'
    //     stuck:

    // ms (1~4):makestack stuckpoint
    // dc (1~4):discard leadpoint
    // ds (1~4) (1~4):disstuck stuckpoint leadpoint
    // ud :undo
    // ed :endgame
    // T_CLEAR;

    // ============== line_ 1 ==============
    /* === padding === */
    for (int i = 0; i < 44; i++)
        printf("\t");
    /* =============== */
    printf("turn%c%2d", CONNECTTION_MARK, CARD_AMOUNT - Statu.amountCards + 1);
    puts("");

    // ============== line_ 2 ==============
    for (int i = 0; i < 3; i++)
        printf("\t");
    printf(" ");
    puts(ROOF);

    // ============== line_ 3 ==============
    /* === padding === */
    printf("%s", STRING_POINT);
    for (int i = 0; i < 3; i++)
        printf("\t");
    printf("  ");
    /* =============== */
    for (int i = 0; i < 4; i++)
    {
        printf("%c  %d  %c", SEP, i + 1, SEP);
        /* === padding === */
        if (i != 3)
            printf("\t  ");
        /* =============== */
    }
    puts("");

    // ============== line_ 4 ==============
    printf("\t%s", STRING_LEAD);
    printf("\t ");
    for (int i = 0; i < 4; i++)
    {
        printf("%s", UPPER_BANS);
        if (i != 3)
            printf("\t  ");
    }
    puts("");

    // ============== line_ 5 ==============
    /* === Showup ===*/
    setFontAttributes(-1, 36, -1);
    printf("$ ");
    RESET_FONT;
    printCard(Statu.showup);
    for (int i = 0; i < 2; i++)
        printf("\t");

    for (int i = 0; i < 4; i++)
    {
        printf("%c  ", SEP);
        printRank(Statu.leadCards[i]);
        printf(" %c ", SEP);
        printCard(Statu.leadCards[i]);
        printf(" ");
    }

    puts("");
    // ============== line_ 6 ==============

    printf("\t ");
    for (int i = 0; i < 4; i++)
    {
        printf("%s", UNDER_BANS);
        if (i != 3)
            printf("\t  ");
    }
    puts("");

    // ============== line_ 7 ==============
    printf("\t%s", STRING_STUCK);
    puts("");

    // ============== line_ 8 ==============
    puts("");

    // ============== line_ 9 ==============
    printf("ms (1~4):makestack stuckpoint");
    puts("");

    // ============== line_10 ==============
    printf("dc (1~4):discard leadpoint");
    puts("");

    // ============== line_11 ==============
    printf("ds (1~4) (1~4):disstuck stuckpoint leadpoint");
    puts("");

    // ============== line_12 ==============
    printf("ud :undo");
    puts("");

    // ============== line_13 ==============
    printf("ed :endgame");
    puts("");

    // ============== line_14 ==============
    puts("");

    TC_END;
}

/* === padding === */
/* =============== */
