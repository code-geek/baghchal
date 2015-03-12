#include "GameState.h"

GameState::GameState()
{
    for (int i = 0; i < 26; i++)
        boardPos[i] = N;

    turn = Goat;
}

void GameState::SetTurn(Player t)
{
    turn = t;
}

Player GameState::GetTurn() const
{
    return turn;
}

bool GameState::PositionIsRepeated(GameState & gsA, GameState & gsB)
{
    if(gsA.GetTurn() != gsB.GetTurn())
        return false;

    for (int i = 1; i < 26; i++)
    {
        if(gsA.boardPos[i] != gsB.boardPos[i])
            return false;
    }

    return true;
}
