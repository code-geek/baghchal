#include "MyPlayer.h"

//checks if the highlighted goat or tiger is movable to the selectorPoint
bool MyPlayer::IsMovable(Board * brd, int m, int n) //m = flags->selectorPoint n = flags->highlightPoint
{
    if (
        (brd->point[m].GetState() == N)
        &&
        (
            //horizontal
            ((abs(brd->point[m].GetX() - brd->point[n].GetX()) == brd->incrementX) && (abs(brd->point[m].GetY() - brd->point[n].GetY()) == 0)) ||
            //vertical
            ((abs(brd->point[m].GetY() - brd->point[n].GetY()) == brd->incrementY) && (abs(brd->point[m].GetX() - brd->point[n].GetX()) == 0)) ||
            //diagonal
            ((n % 2 !=0) && (abs(brd->point[m].GetY() - brd->point[n].GetY()) == brd->incrementY) && (abs(brd->point[m].GetX() - brd->point[n].GetX()) == brd->incrementX))
        )
    )
    {
        return true;
    }

    else
    {
        return false;
    }
}

void MyPlayer::SaveGameState(int n)
{
    for (int i = 1; i < 26; i++)
    {
        gameState[n].boardPos[i] = board->point[i].GetState();
    }

    gameState[n].SetTurn(flags->turn);

    if (n == flags->gsCounter)
        flags->gsCounter++;

    if(flags->gsCounter % numberOfStates == 1)
    {
        flags->gsCounter = 1;
    }
}

void MyPlayer::PosRepeatCheck()
{
    int counter = 0;
    for (int i = 1; i <= numberOfStates; i++)
    {
        if (GameState::PositionIsRepeated(gameState[0], gameState[i]))//if the states are the same
        {
            counter++;
            if (counter > 1)
            {
                flags->isPosRepeated = true;
                break;
            }
        }
    }
}

void MyPlayer::ChangeGameState(State a, State b)
{
    gameState[0].boardPos[flags->selectorPoint] = a;
    gameState[0].boardPos[flags->highlightPoint] = b;

    if (gameState[0].GetTurn() == Tiger)
        gameState[0].SetTurn(Goat);
    else
        gameState[0].SetTurn(Tiger);
}
