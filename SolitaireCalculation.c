#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CARDS 52
#define NUM_STOCK 48
#define dot_turnbar "\t     .------_:=^=:_------_:=^=:_------_:=^=:_------_:=^=:_------."
#define dot_topframe ".-----."
#define dot_buttomframe "'-----'"
#define dot_nocard "  "
char *playeraction_1[2] = {"ms", "makestack"};
char *playeraction_2[2] = {"dc", "discard"};
char *playeraction_3[2] = {"ds", "disstuck"};

//"θ_", "π_", "β_", "ω_"
char *suits[] = {"S_", "D_", "H_", "C_"};

//"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"
char *ranks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

typedef struct
{
    char *rank;
    char *suit;
} Card;

// globals argument
Card stock[NUM_STOCK], lead[4][NUM_STOCK], stuck[4][NUM_STOCK + 5], showup;
char *nextlead[4], log_playerchoise[NUM_STOCK][10];
int stop = 0, turn = 0, log_counter = 0;

/*行動が取られる度にテーブルを更新します。*/
void update_table(void);

/*手札を台札に置きます。*/
void dis_card(int lead_point);

/*場札を台札に置きます。*/
void dis_stuck(int stuck_point, int lead_point);

/*手札を場札に置きます。*/
void make_stuck(int stuck_point);

/*最初に置かれる4枚のカード（リード）を設定します。*/
void leads(Card lead[][NUM_STOCK]);

/*山札の上のカードを1枚めくります。*/
void turnup(Card *stock);

/*プレイヤーがターンごとに取る行動を処理します。*/
void player_action(void);

/*山札をシャッフルします。*/
void shuffle(Card *stock);

/*山札、場札の初期化*/
void initialize_game(Card stock[], Card stuck[][NUM_STOCK + 5]);

/*1ターン戻す*/
void undo(void);

/*ゲーム終了*/
void endgame(void);

int main(void)
{
    int i;
    initialize_game(stock, stuck);
    //    shuffle(stock);

    while (stop != 1 && stop != 2)
    {
        update_table();
    }

    if (stop == 2)
    {
        printf("\n!! GAME CLEAR !!\n");
    }

    return 0;
}
void update_table(void)
{
    int i;
    leads(lead);
    printf("\x1b[?25l\x1b[H\x1b[J"); // 画面をクリア
    printf("\n                                       turn_ %2d\n", turn);
    printf("%s\n", dot_turnbar);
    printf("point:              |  1  |      |  2  |      |  3  |      |  4  |\n");
    printf("    lead:     %s      %s      %s      %s\n", dot_topframe, dot_topframe, dot_topframe, dot_topframe);
    if (showup.suit != NULL)
    {
        printf("$ ");
    }
    else
    {
        printf("  ");
    }
    if (showup.suit != NULL)
    {
        printf("%s", showup.suit);
    }
    else
    {
        printf("  ");
    }
    if (showup.rank != NULL)
    {
        printf("%2s", showup.rank);
    }
    else
    {
        printf("  ");
    }
    printf("        ");

    for (i = 0; i < 4; i++)
    {
        int lead_index = 0;
        while (lead[i][lead_index].suit != NULL)
        {
            lead_index++;
        }
        printf("| %3s | %s %s ", nextlead[i] ? nextlead[i] : dot_nocard, lead[i][lead_index - 1].suit, lead[i][lead_index - 1].rank);
    }
    printf("\n              %s      %s      %s      %s\n", dot_buttomframe, dot_buttomframe, dot_buttomframe, dot_buttomframe);

    printf("    stuck:\n");
    int max_elements = 0; // 各行の最大の要素数を保持する変数を初期化
    for (i = 0; i < 4; i++)
    {
        int elements_count = 0;
        while (stuck[i][elements_count].suit != NULL && elements_count < NUM_STOCK)
        { // 各行の要素数を計算する
            elements_count++;
        }
        if (max_elements < elements_count)
        { // 各行の要素数が最大値よりも大きい場合、更新する
            max_elements = elements_count;
        }
    }

    // 各行の最大の要素数を基準にして各行の要素にアクセスする
    for (i = 0; i < max_elements; i++)
    {
        printf("                      ");
        if (stuck[0][i].suit != NULL)
        {
            printf("%s%s", stuck[0][i].suit, stuck[0][i].rank);
        }
        else
        {
            printf("%s", dot_nocard);
        }
        if (stuck[1][i].suit != NULL)
        {
            printf("          %s%s", stuck[1][i].suit, stuck[1][i].rank);
        }
        else
        {
            printf("          %s", dot_nocard);
        }
        if (stuck[2][i].suit != NULL)
        {
            printf("          %s%s", stuck[2][i].suit, stuck[2][i].rank);
        }
        else
        {
            printf("          %s", dot_nocard);
        }
        if (stuck[3][i].suit != NULL)
        {
            printf("          %s%s", stuck[3][i].suit, stuck[3][i].rank);
        }
        else
        {
            printf("          %s", dot_nocard);
        }
        printf("\n");
    }
    printf("\x1b[?25h");

    player_action();
}

void undo(void)
{
    if (log_counter == 0)
    {
        printf("You cannot undo at turn 1\n");
        player_action();
        return;
    }

    char log_action[3];
    int log_stuck_point, log_lead_point, log_subcounter;

    sscanf(log_playerchoise[log_counter - 1], "%2s %1d %1d %2d", log_action, &log_stuck_point, &log_lead_point, &log_subcounter);

    if (strcmp(log_action, "ms") == 0)
    {
        int i;
        for (i = 0; stock[i].suit == NULL; i++)
            ;
        stock[i - 1] = showup;
        for (i = 0; stuck[log_stuck_point - 1][i].suit != NULL; i++)
            ;
        showup = stuck[log_stuck_point - 1][i - 1];
        stuck[log_stuck_point - 1][i - 1].rank = NULL;
        stuck[log_stuck_point - 1][i - 1].suit = NULL;
    }
    else if (strcmp(log_action, "dc") == 0)
    {
        int i;
        for (i = 0; stock[i].suit == NULL; i++)
            ;
        stock[i - 1] = showup;
        for (i = 0; lead[log_stuck_point - 1][i].suit != NULL; i++)
            ;
        showup = lead[log_stuck_point - 1][i - 1];
        lead[log_stuck_point - 1][i - 1].rank = NULL;
        lead[log_stuck_point - 1][i - 1].suit = NULL;
    }
    else if (strcmp(log_action, "ds") == 0)
    {
        int i, j;
        for (i = 0; stuck[log_stuck_point - 1][i].suit != NULL; i++)
            ;
        for (j = 0; lead[log_lead_point - 1][j].suit != NULL; j++)
            ;
        stuck[log_stuck_point - 1][i] = lead[log_lead_point - 1][j - 1];
        lead[log_lead_point - 1][j - 1].rank = NULL;
        lead[log_lead_point - 1][j - 1].suit = NULL;
    }

    // Clear log entry and adjust counters
    log_counter--;
    turn--;
    memset(log_playerchoise[log_counter], '\0', sizeof(log_playerchoise[log_counter]));
}

void endgame(void)
{
    stop = 1;
}

void make_stuck(int stuck_point)
{
    int i;
    for (i = 0; i < NUM_STOCK; i++)
    {
        if (stuck[stuck_point - 1][i].suit == NULL)
        {
            stuck[stuck_point - 1][i] = showup;
            showup.suit = NULL;
            showup.rank = NULL;
            snprintf(log_playerchoise[log_counter], sizeof(log_playerchoise[log_counter]), "ms %1d 1 %2d", stuck_point, log_counter);
            turnup(stock);
            log_counter++;
            break;
        }
    }
}

void dis_card(int lead_point)
{
    int i;
    if (nextlead[lead_point - 1] == showup.rank)
    {
        for (i = 0; lead[lead_point - 1][i].suit != NULL; i++)
            ;
        lead[lead_point - 1][i] = showup;
        showup.rank = NULL;
        showup.suit = NULL;
        snprintf(log_playerchoise[log_counter], sizeof(log_playerchoise[log_counter]), "dc %1d 1 %2d", lead_point, log_counter);
        turnup(stock);
        log_counter++;
    }
    else
    {
        printf("Invalid action: showup does not match nextlead on point %d\n", lead_point);
        player_action();
    }
}

void dis_stuck(int stuck_point, int lead_point)
{
    int i, j;
    for (i = 0; i < NUM_STOCK && stuck[stuck_point - 1][i].suit != NULL; i++)
        ;
    for (j = 0; j < NUM_STOCK && lead[lead_point - 1][j].suit != NULL; j++)
        ;

    if (nextlead[lead_point - 1] == stuck[stuck_point - 1][i - 1].rank)
    {
        lead[lead_point - 1][j] = stuck[stuck_point - 1][i - 1];
        stuck[stuck_point - 1][i - 1].rank = NULL;
        stuck[stuck_point - 1][i - 1].suit = NULL;
        snprintf(log_playerchoise[log_counter], sizeof(log_playerchoise[log_counter]), "ds %1d %1d %2d", stuck_point, lead_point, log_counter);
        log_counter++;
    }
    else
    {
        printf("Invalid action: Stuck card at position %d in point %d does not match next lead card at point %d\n", i, stuck_point, lead_point);
        player_action();
    }
}

void player_action(void)
{
    char request[7], first_str[3], second_str[3], action[3];
    int stuck_point, lead_point;

    printf("\n%s (1~4):%s stuckpoint\n%s (1~4):%s leadpoint\n%s (1~4) (1~4):%s stuckpoint leadpoint\nud :undo\ned :endgame\n\n", playeraction_1[0], playeraction_1[1], playeraction_2[0], playeraction_2[1], playeraction_3[0], playeraction_3[1]);

    scanf("%6s", request);
    getchar();

    sscanf(request, "%2s %1s %1s", action, first_str, second_str);

    if (strcmp(action, playeraction_1[0]) != 0 && strcmp(action, playeraction_2[0]) != 0 && strcmp(action, playeraction_3[0]) != 0 && strcmp(action, "ud") != 0 && strcmp(action, "ed") != 0)
    {
        printf("Invalid action. Please try again.\n");
        player_action();
        return;
    }

    stuck_point = atoi(first_str);

    if ((stuck_point < 1 || stuck_point > 4) && strcmp(action, "ed") != 0 && strcmp(action, "ud") != 0)
    {
        printf("Invalid stuck point. Please try again.\n");
        player_action();
        return;
    }

    if (strcmp(action, playeraction_3[0]) == 0 && strcmp(action, "ed") != 0 && strcmp(action, "ud") != 0)
    {
        lead_point = atoi(second_str);
        if (lead_point < 1 || lead_point > 4)
        {
            printf("Invalid lead point. Please try again.\n");
            player_action();
            return;
        }
    }

    if (strcmp(action, "ms") == 0)
    {
        make_stuck(stuck_point);
    }
    else if (strcmp(action, "dc") == 0)
    {
        lead_point = stuck_point;
        stuck_point = '\0';
        dis_card(lead_point);
    }
    else if (strcmp(action, "ds") == 0)
    {
        dis_stuck(stuck_point, lead_point);
    }
    else if (strcmp(action, "ud") == 0)
    {
        undo();
    }
    else if (strcmp(action, "ed") == 0)
    {
        endgame();
    }
}

void leads(Card lead[][NUM_STOCK])
{
    int i, j, t;

    for (j = 0; j < 4; j++)
    {
        for (i = 0; lead[j][i].suit != NULL; i++)
            ;
        for (t = 0; strcmp(lead[j][i - 1].rank, ranks[t]) != 0; t++)
            ;
        nextlead[j] = ranks[(t + j + 1) % 13];
    }

    for (i = 0; i < 4; i++)
    {
        if (lead[i][(NUM_CARDS / 4) - 1].rank != NULL && strcmp(lead[i][(NUM_CARDS / 4) - 1].rank, ranks[12]) == 0)
        {
            nextlead[i] = '\0';
        }
    }

    if (lead[0][(NUM_CARDS / 4) - 1].suit != NULL && lead[1][(NUM_CARDS / 4) - 1].suit != NULL && lead[2][(NUM_CARDS / 4) - 1].suit != NULL && lead[3][(NUM_CARDS / 4) - 1].suit != NULL && strcmp(lead[0][(NUM_CARDS / 4) - 1].rank, ranks[12]) == 0 && strcmp(lead[1][(NUM_CARDS / 4) - 1].rank, ranks[12]) == 0 && strcmp(lead[2][(NUM_CARDS / 4) - 1].rank, ranks[12]) == 0 && strcmp(lead[3][(NUM_CARDS / 4) - 1].rank, ranks[12]) == 0)
    {
        stop = 2;
    }
}

void turnup(Card *stock)
{
    int i;
    if (turn <= 48)
    {
        for (i = 0; (stock[i].rank == NULL) && (stock[i].suit == NULL); i++)
            ;
        showup.suit = stock[i].suit;
        showup.rank = stock[i].rank;
        stock[i].suit = NULL;
        stock[i].rank = NULL;
        turn++;
    }

    if (turn >= 49)
    {
        showup.rank = NULL;
        showup.suit = NULL;
        return;
    }
}

void shuffle(Card *stock)
{
    srand(time(NULL));
    int i, j;
    Card memo;
    for (i = 0; i < NUM_STOCK; i++)
    {
        j = rand() % NUM_STOCK;
        memo = stock[i];
        stock[i] = stock[j];
        stock[j] = memo;
    }
}

void initialize_game(Card stock[], Card stuck[][NUM_STOCK + 5])
{
    int stock_index = 0, i;
    // Initialize stock
    for (i = NUM_CARDS - 1; i >= 0; i--)
    {
        if (i == 0 || i == (13 + 1) || i == (26 + 2) || i == (39 + 3))
        {
            int lead_index = i / 13;
            lead[lead_index][0].suit = suits[lead_index];
            lead[lead_index][0].rank = ranks[lead_index];
        }
        else
        {
            stock[stock_index].suit = suits[i / 13];
            stock[stock_index].rank = ranks[i % 13];
            stock_index++;
        }
    }
    showup.rank = NULL;
    showup.suit = NULL;
    turnup(stock);
    for (i = 0; i < 4; i++)
    {
        nextlead[i] = NULL;
    }
    // Initialize stuck
    for (i = 0; i < 4; i++)
    {
        for (int j = 0; j < NUM_STOCK; j++)
        {
            stuck[i][j].suit = NULL;
            stuck[i][j].rank = NULL;
        }
    }
    // initialize log
    for (i = 0; i < NUM_STOCK; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            log_playerchoise[i][j] = '\0';
        }
    }
}
