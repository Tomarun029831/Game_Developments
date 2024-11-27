#include "../include/statu.h"

_Statu Statu;

void makeStuck(int _pointS)
{
    printf("makestuck called with %d\n", _pointS);
}

void disCard(int _pointL)
{
    printf("discard called with %d\n", _pointL);
}

void disStuck(int _pointS, int _pointL)
{
    printf("disstuck called with %d %d\n", _pointS, _pointL);
}

void Undo()
{
    printf("undo called\n");
}

void EndGame()
{
    printf("endgame called\n");
}