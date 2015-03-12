#include "Goat.h"

GoatPlayer::GoatPlayer(Flags * f, Board * b, GameState * g, TigerPlayer * t, Sprites * s)
{
    flags = f;
    board = b;
    gameState = g;
    tiger = t;
    sprites = s;
}

//defines the placement phase and the movement phase of the goats.
bool GoatPlayer::GoatLogic(int sp, int hp)
{
    //placement phase

    //flags->goatsToBePlaced is the number of goats remaining to be placed
    if (flags->goatsToBePlaced > 0)
    {
        //if an empty square is pressed twice
        if ((board->point[hp].GetState() == N) && (sp == hp))
        {
            board->point[hp].SetState(G);
            sprites->point[hp].isDrawn = false;

            flags->fromPoint = hp;
            flags->toPoint = sp;
            flags->drawLastMove = true;

            flags->goatsToBePlaced--;

            //minimum no. of goatts needed to trap tigers is 11
            if ((20 - flags->goatsToBePlaced) >= 11) //i.e. if at least 11 goats are on the board
            {
                tiger->WinCheck();
            }

            flags->turn = Tiger;

            if (flags->goatsToBePlaced == 0  && flags->posRepeatRuleActive)
            {
                for (int i = 0; i <= numberOfStates; i++)
                    SaveGameState(i);
            }
            return true;
        }
    }

    //movement phase

    //if the goat is movable from the highlight point to the selector point
    else if((board->point[hp].GetState() == G) && (IsMovable(board, sp, hp)))
    {
        if (flags->posRepeatRuleActive)
        {
            int counter = 0;
            tiger->GenerateMoveList(counter);

            SaveGameState(0);

            if (counter != 1)
            {
                ChangeGameState(G, N);//put a goat in the selectorpoint and nothing in the highlightpoint
                PosRepeatCheck();
            }

            else
            {
                flags->isPosRepeated = false;
            }
        }

        if (!flags->posRepeatRuleActive || !flags->isPosRepeated)
        {
            board->point[sp].SetState(G);
            sprites->point[sp].isDrawn = false;

            board->point[hp].SetState(N);
            sprites->point[hp].isDrawn = false;

            flags->fromPoint = hp;
            flags->toPoint = sp;
            flags->drawLastMove = true;

            tiger->WinCheck();

            flags->turn = Tiger;

            if (flags->posRepeatRuleActive)
                SaveGameState(flags->gsCounter);

            return true;
        }

        else
        {
            flags->isPosRepeated = false;
            flags->drawRepeatText = true;
        }
    }
    return false;
}
