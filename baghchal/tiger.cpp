#include "tiger.h"

TigerPlayer::TigerPlayer(Flags * f, Board * b, GameState * g, Sprites * s)
{
    flags = f;
    board = b;
    gameState = g;
    sprites = s;

    SetTigerPos();
}

void TigerPlayer::SetTigerPos()
{
    tigerPos[0] = 1;
    tigerPos[1] = 5;
    tigerPos[2] = 21;
    tigerPos[3] = 25;
}

//defines tiger moves and captures. control gets here when the turn is tiger's and the select key is pressed again after the highlight is drawn.
bool TigerPlayer::TigerLogic(int sp, int hp)//sp = selector point, hp = highlight point
{
    if (board->point[hp].GetState() == T)
    {
        //checks if the tiger is movable from the hp to the sp
        if (IsMovable(board, sp, hp))
        {
            if (flags->goatsToBePlaced == 0 && flags->posRepeatRuleActive)
            {
                int counter = 0;
                GenerateMoveList(counter);

                SaveGameState(0);

                if (counter != 1)
                {
                    ChangeGameState(T, N);//put a tiger in the selectorpoint and nothing in the highlightpoint
                    PosRepeatCheck();
                }

                else
                {
                    flags->isPosRepeated = false;
                }
            }

            if (!flags->posRepeatRuleActive || !flags->isPosRepeated)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (hp == tigerPos[i])
                    {
                        tigerPos[i] = sp;
                        break;
                    }
                }

                board->point[sp].SetState(T);
                sprites->point[sp].isDrawn = false;

                board->point[hp].SetState(N);
                sprites->point[hp].isDrawn = false;

                flags->fromPoint = hp;
                flags->toPoint = sp;
                flags->drawLastMove = true;

                flags->turn = Goat;

                if (!flags->goatsToBePlaced  && flags->posRepeatRuleActive)
                    SaveGameState(flags->gsCounter);

                return true;
            }

            else
            {
                flags->isPosRepeated = false;
                flags->drawRepeatText = true;
            }
        }

        //condition for eating goat
        else if(CanCapture(board, sp, hp))
        {
            for (int i = 0; i < 4; i++)
            {
                if (hp == tigerPos[i])
                {
                    tigerPos[i] = sp;
                    break;
                }
            }

            board->point[sp].SetState(T);
            sprites->point[sp].isDrawn = false;

            board->point[hp].SetState(N);
            sprites->point[hp].isDrawn = false;

            int midpoint = abs((hp + sp) / 2);

            board->point[midpoint].SetState(N);
            sprites->point[midpoint].isDrawn = false;

            flags->fromPoint = hp;
            flags->toPoint = sp;
            flags->drawLastMove = true;

            flags->deadGoats++;
            WinCheck();

            flags->turn = Goat;

            if (!flags->goatsToBePlaced  && flags->posRepeatRuleActive)
                SaveGameState(flags->gsCounter);
            return true;
        }//end of if(IsMovable()) and corresponding else
    }// end of main if
    return false;
}// end of function TigerLogic()

//checks if the highlighted tiger can capture to the selected point
bool TigerPlayer::CanCapture(Board * brd, int m, int n)//m is selector, n is highlight
{
    if (
        (brd->point[m].GetState() == N)
        &&
        (
            //horizontal
            ((abs(brd->point[m].GetX() - brd->point[n].GetX()) == 2*brd->incrementX) && (abs(brd->point[m].GetY() - brd->point[n].GetY()) == 0)) ||
            //vertical
            ((abs(brd->point[m].GetY() - brd->point[n].GetY()) == 2*brd->incrementY) && (abs(brd->point[m].GetX() - brd->point[n].GetX()) == 0)) ||
            //diagonal
            ((n % 2 !=0) && (abs(brd->point[m].GetY() - brd->point[n].GetY()) == 2*brd->incrementY) && (abs(brd->point[m].GetX() - brd->point[n].GetX()) == 2*brd->incrementX))
        )
        &&
        (brd->point[(m + n) / 2].GetState() == G)
    )

    {
        return true;
    }

    else
    {
        return false;
    }
}

void TigerPlayer::WinCheck()
{
    if (flags->deadGoats == 5)
    {
        flags->isPlaying = false;
        flags->winner = Tiger;
    }

    else if (!CanTigersMove(tigerPos, board))
    {
        flags->isPlaying = false;
        flags->winner = Goat;
    }
}

//returns the number of valid moves of tigers
int TigerPlayer::ValidMoves(int tigerPoint, Board * brd)
{
    int tigerMoves = 0;//count the number of valid moves remaining

    MoveCheck(brd, tigerPoint, direction[0], tigerMoves);//horizontal
    MoveCheck(brd, tigerPoint, direction[2], tigerMoves);//vertical

    if (tigerPoint % 2 != 0)//diagonal check from odd points
    {
        MoveCheck(brd, tigerPoint, direction[1], tigerMoves);
        MoveCheck(brd, tigerPoint, direction[3], tigerMoves);
    }

    return tigerMoves;
}

//checks if the tigers have any valid moves remaining
bool TigerPlayer::CanTigersMove(int tPos[], Board * brd)
{
    for (int i = 0; i < 4; i++)//for each tiger
    {
        if(ValidMoves(tPos[i], brd))
            return true;
    }
    return false;
}

//checks for the number of moves in any direction and adds them to the variable
void TigerPlayer::MoveCheck(Board * brd, int x, int y, int & move)//x = point at which tiger is located , y = direction in to check, 1 is horizontal, 5 is vertical, 4 and 6 are diagonals.
{
    //so as not to check unnecessary points
    if (x+y > 0 && x+y < 26)
    {
        if (IsMovable(brd, x+y, x))//added the ismovable condition
        {
            move++;
        }
    }

    if (x-y > 0 && x-y < 26)
    {
        if (IsMovable(brd, x-y, x))
        {
            move++;
        }
    }

    //capture conditions

    if (x+2*y > 0 && x+2*y < 26)
    {
        if (CanCapture(brd, x+2*y, x))
        {
            move++;
        }
    }

    if (x-2*y > 0 && x-2*y < 26)
    {
        if (CanCapture(brd, x-2*y, x))
        {
            move++;
        }
    }
}

void TigerPlayer::GenerateMoveList(int & counter)
{
    counter = 0;

    //for tiger
    if (flags->turn == Tiger)
    {
        //capture conditions
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                int x = tigerPos[i];
                int y = direction[j];

                if (x+2*y > 0 && x+2*y < 26)
                {
                    if (CanCapture(board, x+2*y, x))
                    {
                        counter++;
                        if (counter > 1)
                        {
                            return;
                        }
                    }
                }

                if (x-2*y > 0 && x-2*y < 26)
                {
                    if (CanCapture(board, x-2*y, x))
                    {
                        counter++;
                        if (counter > 1)
                        {
                            return;
                        }
                    }
                }
            }
        }


        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                int x = tigerPos[i];
                int y = direction[j];

                if (x+y > 0 && x+y < 26)
                {
                    if (IsMovable(board, x+y, x))
                    {
                        counter++;
                        if (counter > 1)
                        {
                            return;
                        }
                    }
                }

                if (x-y > 0 && x-y < 26)
                {
                    if (IsMovable(board, x-y, x))
                    {
                        counter++;
                        if (counter > 1)
                        {
                            return;
                        }
                    }
                }
            }
        }
    }

    else //if the turn is goat's
    {
        if (flags->goatsToBePlaced > 0)
        {
            for (int i = 1; i < 26; i++)
            {
                if ((board->point[i].GetState() == N) || (board->point[i].GetState() == V))
                {
                    counter++;
                    if (counter > 1)
                    {
                        return;
                    }
                }
            }
        }

        else
        {
            for (int i = 1; i < 26; i++)
            {
                if(board->point[i].GetState() == G)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        int x = i;
                        int y = direction[j];

                        if (x+y > 0 && x+y < 26)
                        {
                            if (IsMovable(board, x+y, x))
                            {
                                counter++;
                                if (counter > 1)
                                {
                                    return;
                                }
                            }
                        }

                        if (x-y > 0 && x-y < 26)
                        {
                            if (IsMovable(board, x-y, x))
                            {
                                counter++;
                                if (counter > 1)
                                {
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
