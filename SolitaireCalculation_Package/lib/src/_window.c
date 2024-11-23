#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/options.h"
#include "../include/settings.h"
#include "../include/window.h"
#include "../include/font.h"
#include "../include/statu.h"

extern _Settings Settings;
extern _Statu Statu;

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
    T_CLEAR;
    // ============== line_ 1 ==============
    /* === padding === */
    for (int i = 0; i < 10; i++)
        printf("   ");
    for (int i = 0; i < 9; i++)
        printf(" ");
    /* =============== */
    setFontAttributes(-1, 90, -1);
    printf("turn%c %2d", CONNECTTION_MARK, CARD_AMOUNT - Statu.amountCards + 1);
    puts("");
    RESET_FONT;

    // ============== line_ 2 ==============
    for (int i = 0; i < 6; i++)
        printf("   ");
    printf("  ");
    setFontAttributes(-1, 91, -1);
    puts(ROOF);
    RESET_FONT;

    // ============== line_ 3 ==============
    /* === padding === */
    setFontAttributes(-1, 32, -1);
    printf("%s", STRING_POINT);
    RESET_FONT;
    for (int i = 0; i < 3; i++)
        printf("    ");
    printf("  ");
    /* =============== */
    for (int i = 0; i < 4; i++)
    {
        setFontAttributes(-1, 91, -1);
        printf("%c  ", PILLAR);
        setFontAttributes(-1, 93, -1);
        printf("%d", i + 1);
        setFontAttributes(-1, 91, -1);
        printf("  %c", PILLAR);
        RESET_FONT;
        /* === padding === */
        if (i != 3)
            printf("      ");
        /* =============== */
    }
    puts("");

    // ============== line_ 4 ==============
    setFontAttributes(-1, 32, -1);
    printf("    %s", STRING_LEAD);
    RESET_FONT;
    printf("     ");
    setFontAttributes(-1, 32, -1);
    for (int i = 0; i < 4; i++)
    {
        printf("%s", UPPER_BANS);
        if (i != 3)
            printf("      ");
    }
    puts("");
    RESET_FONT;

    // ============== line_ 5 ==============
    /* === Showup ===*/
    setFontAttributes(-1, 32, -1);
    printf("$ ");
    RESET_FONT;
    printCard(Statu.showup);
    for (int i = 0; i < 2; i++)
        printf("    ");

    for (int i = 0; i < 4; i++)
    {
        setFontAttributes(-1, 32, -1);
        printf("%c  ", TOPPINGS);
        RESET_FONT;
        printRank(Statu.leadCards[i].rank); // patty
        setFontAttributes(-1, 32, -1);
        printf(" %c ", TOPPINGS);
        RESET_FONT;
        printCard(Statu.leadCards[i]);
        printf(" ");
    }

    puts("");
    // ============== line_ 6 ==============

    printf("              ");
    setFontAttributes(-1, 32, -1);
    for (int i = 0; i < 4; i++)
    {
        printf("%s", UNDER_BANS);
        if (i != 3)
            printf("      ");
    }
    puts("");
    RESET_FONT;

    // ============== line_ 7 ==============
    setFontAttributes(-1, 32, -1);
    printf("    %s", STRING_STUCK);
    RESET_FONT;
    puts("");

    // ============== line_ 8 ==============
    puts("");

    // ============== line_ 9 ==============
    setFontAttributes(-1, 32, -1);
    printf("ms (1~4):Makestack Stuckpoint");
    puts("");
    RESET_FONT;

    // ============== line_10 ==============
    setFontAttributes(-1, 32, -1);
    printf("dc (1~4):Discard Leadpoint");
    puts("");
    RESET_FONT;

    // ============== line_11 ==============
    setFontAttributes(-1, 32, -1);
    printf("ds (1~4) (1~4):Disstuck Stuckpoint Leadpoint");
    puts("");
    RESET_FONT;

    // ============== line_12 ==============
    setFontAttributes(-1, 32, -1);
    printf("ud :Undo");
    puts("");
    RESET_FONT;

    // ============== line_13 ==============
    setFontAttributes(-1, 32, -1);
    printf("ed :Endgame");
    puts("");
    RESET_FONT;

    // ============== line_14 ==============
    puts("");

    TC_END;
}

/* === padding === */
/* =============== */
