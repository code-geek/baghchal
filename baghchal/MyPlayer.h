#ifndef MYPLAYER_H
#define MYPLAYER_H

#include "Headers.h"
#include "Board.h"
#include "Sprites.h"
#include "Flags.h"
#include "Board.h"
#include "GameState.h"

class MyPlayer
{
protected:
    Flags * flags;
    Board * board;
    GameState * gameState;
    Sprites * sprites;

public:
    virtual void MakeObject() = 0;

    bool IsMovable(Board * brd, int m, int n);

    //functions for repetition check
    void SaveGameState(int n);
    void PosRepeatCheck();
    void ChangeGameState(State a, State b);//selectorpoint to a, highlightpoint to b
};

#endif
