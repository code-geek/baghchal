//used for the non-repetition rule

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "headers.h"

class GameState
{
private:
    Player turn;

public:
    GameState();
    State boardPos[26];
    void SetTurn(Player t);
    Player GetTurn() const;

    static bool PositionIsRepeated(GameState & gsA, GameState & gsB);
};

#endif
