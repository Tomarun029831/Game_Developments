#include "../include/statu.h"
#include <stdio.h>

_Statu Statu;

void Showup(_ChainCard *Node)
{
    if (Statu.showup.rank == NULL)
    {
    }
}

void MakeStuck(int _pointS)
{
    printf("makestuck called with %d\n", _pointS);
}

void DisCard(int _pointL)
{
    printf("discard called with %d\n", _pointL);
}

void DisStuck(int _pointS, int _pointL)
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