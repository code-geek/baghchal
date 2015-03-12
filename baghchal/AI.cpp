#include "AI.h"

AI::AI(Flags * f, TigerPlayer * t, GoatPlayer * g)
{
    board = new Board;
    flags = f;
    tigerPlayer = t;
    goatPlayer = g;
    firstMove = true;
}

AI::~AI()
{
    delete board;
}

void AI::initAI()
{
    for(int i = 0 ; i < 4; i++)
    {
        aiTigerPos[i] = tigerPlayer->tigerPos[i];
    }

    aiDeadGoats = flags->deadGoats;
    aiGoatsToBePlaced = flags->goatsToBePlaced;
    aiTurn = flags->turn;

    //initializes the board position so that it represents the position at the start of the game.
    board->SetIncrements(1, 1);
    board->SetPoints(1, 1);
}

bool AI::MakeMove()
{
    int score = 0;

    if(aiTurn == Tiger)
    {
        score = TigerMiniMax(0);

        if(!tigerPlayer->TigerLogic(moveTo, moveFrom))
        {
            flags->drawInvalidMove = true;
        }

        else
        {
            flags->aiThinking = false;
            return true;
        }
    }

    else
    {
        if (!firstMove)
        {
            score = GoatMiniMax(0);
        }

        else
        {
            int arr[4] = {3, 11, 15, 23};

            srand(time(0));
            int mv = rand()%4;

            moveFrom = arr[mv];
            moveTo = arr[mv];

            firstMove = false;
        }

        if(!goatPlayer->GoatLogic(moveTo, moveFrom))
        {
            flags->drawInvalidMove = true;
        }

        else
        {
            flags->aiThinking = false;
            return true;
        }
    }
    flags->aiThinking = false;
    return false;
}

bool AI::TigerWinCheck()
{
    if (aiDeadGoats == 5)
    {
        return true;
    }
    return false;
}

bool AI::GoatWinCheck(Board * b)
{
    if (!tigerPlayer->CanTigersMove(aiTigerPos, b))
    {
        return true;
    }
    return false;
}

//this function can be made a LOT more efficient.
void AI::GenerateMoveList(int & counter, Move move[])
{
    counter = 0;

    //for efficiency of ab pruning
    int replaceCounter = 0;
    int initialPossibleCaptures = PossibleCaptures();
    int tempTigerPos;
    int a;

    //for tiger
    if (aiTurn == Tiger)
    {
        //capture conditions
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                int x = aiTigerPos[i];
                int y = direction[j];

                if (x+2*y > 0 && x+2*y < 26)
                {
                    if (tigerPlayer->CanCapture(board, x+2*y, x))
                    {
                        move[counter].from = x;
                        move[counter].to = x+2*y;
                        move[counter].type = TIGER_CAPTURE;
                        counter++;
                    }
                }

                if (x-2*y > 0 && x-2*y < 26)
                {
                    if (tigerPlayer->CanCapture(board, x-2*y, x))
                    {
                        move[counter].from = x;
                        move[counter].to = x-2*y;
                        move[counter].type = TIGER_CAPTURE;
                        counter++;
                    }
                }
            }
        }

        replaceCounter = counter;//to avoid replacing the capture moves.

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                int x = aiTigerPos[i];
                int y = direction[j];

                if (x+y > 0 && x+y < 26)
                {
                    if (tigerPlayer->IsMovable(board, x+y, x))
                    {
                        move[counter].from = x;
                        move[counter].to = x+y;
                        move[counter].type = TIGER_MOVE;

                        //for efficiency of ab pruning
                        board->point[move[counter].to].SetState(T);
                        board->point[move[counter].from].SetState(N);

                        for (int j = 0; j < 4; j++)
                        {
                            if (aiTigerPos[j] == move[counter].from)
                            {
                                aiTigerPos[j] = move[counter].to;
                                tempTigerPos = j;
                                break;
                            }
                        }

                        a = PossibleCaptures();

                        board->point[move[counter].to].SetState(N);
                        board->point[move[counter].from].SetState(T);
                        aiTigerPos[tempTigerPos] = move[counter].from;

                        if (a > initialPossibleCaptures)
                        {
                            Move temp = move[replaceCounter];
                            move[replaceCounter] = move[counter];
                            move[counter] = temp;

                            replaceCounter++;
                        }
                        counter++;
                    }
                }

                if (x-y > 0 && x-y < 26)
                {
                    if (tigerPlayer->IsMovable(board, x-y, x))
                    {
                        move[counter].from = x;
                        move[counter].to = x-y;
                        move[counter].type = TIGER_MOVE;

                        //for efficiency of ab pruning
                        board->point[move[counter].to].SetState(T);
                        board->point[move[counter].from].SetState(N);

                        for (int j = 0; j < 4; j++)
                        {
                            if (aiTigerPos[j] == move[counter].from)
                            {
                                aiTigerPos[j] = move[counter].to;
                                tempTigerPos = j;
                                break;
                            }
                        }

                        a = PossibleCaptures();

                        board->point[move[counter].to].SetState(N);
                        board->point[move[counter].from].SetState(T);
                        aiTigerPos[tempTigerPos] = move[counter].from;

                        if (a > initialPossibleCaptures)
                        {
                            Move temp = move[replaceCounter];
                            move[replaceCounter] = move[counter];
                            move[counter] = temp;

                            replaceCounter++;
                        }
                        counter++;
                    }
                }
            }
        }
    }

    else //if aiturn is goat
    {
        if (aiGoatsToBePlaced > 0)
        {
            for (int i = 1; i < 26; i++)
            {
                if ((board->point[i].GetState() == N) || (board->point[i].GetState() == V))
                {
                    move[counter].from = i;
                    move[counter].to = i;
                    move[counter].type = GOAT_PLACE;

                    //for efficiency of ab pruning
                    board->point[move[counter].to].SetState(G);
                    a = PossibleCaptures();
                    board->point[move[counter].to].SetState(N);

                    if (a < initialPossibleCaptures)
                    {
                        Move temp = move[replaceCounter];
                        move[replaceCounter] = move[counter];
                        move[counter] = temp;

                        replaceCounter++;
                    }
                    counter++;
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
                            if (tigerPlayer->IsMovable(board, x+y, x))
                            {
                                move[counter].from = x;
                                move[counter].to = x+y;
                                move[counter].type = GOAT_MOVE;

                                //for efficiency of ab pruning
                                board->point[move[counter].to].SetState(G);
                                board->point[move[counter].from].SetState(N);
                                a = PossibleCaptures();
                                board->point[move[counter].to].SetState(N);
                                board->point[move[counter].from].SetState(G);

                                if (a < initialPossibleCaptures)
                                {
                                    Move temp = move[replaceCounter];
                                    move[replaceCounter] = move[counter];
                                    move[counter] = temp;

                                    replaceCounter++;
                                }
                                counter++;
                            }
                        }

                        if (x-y > 0 && x-y < 26)
                        {
                            if (tigerPlayer->IsMovable(board, x-y, x))
                            {
                                move[counter].from = x;
                                move[counter].to = x-y;
                                move[counter].type = GOAT_MOVE;

                                //for efficiency of ab pruning
                                board->point[move[counter].to].SetState(G);
                                board->point[move[counter].from].SetState(N);
                                a = PossibleCaptures();
                                board->point[move[counter].to].SetState(N);
                                board->point[move[counter].from].SetState(G);

                                if (a < initialPossibleCaptures)
                                {
                                    Move temp = move[replaceCounter];
                                    move[replaceCounter] = move[counter];
                                    move[counter] = temp;

                                    replaceCounter++;
                                }
                                counter++;
                            }
                        }
                    }
                }
            }
        }
    }
}

void AI::SlowDownAIMove()
{
    while(1)
    {
        if (AITimer.GetElapsedTime() > 0.55)
        {
            AITimer.Reset();
            break;
        }
    }
}

//these evaluation functions need improving.
int AI::TigerEvaluatePosition()
{
    if (TigerWinCheck())
        return +INF;
    if (GoatWinCheck(board))
        return -INF;

    return (1000 * aiDeadGoats - 300 * GhostGoats() + 200 * PossibleCaptures() - 500 * TigersTrapped(board) + 50 * cornersOccupied);
}

int AI::GoatEvaluatePosition(int depth)
{
    if (TigerWinCheck())
        return -INF;
    if (GoatWinCheck(board))
        return +INF - depth;

    return -(1000 * aiDeadGoats - 300*GhostGoats() + 100 * PossibleCaptures() - 200 * TigersTrapped(board) + depth);
}

int AI::TigerMiniMax(int depth, int alpha, int beta)
{
    int posVal = TigerEvaluatePosition();

    if (depth == flags->searchDepth || posVal == +INF || posVal == -INF)
    {
        posVal = posVal == +INF? posVal - 1: posVal + 1;

        return posVal;
    }

    int counter = 0;
    Move move[21];

    GenerateMoveList(counter, move);

    int val, tempTigerPos;
    bool cornerMoved = false;
    bool cornerLeft = false;

    for (int i = 0; i < counter; i++)
    {
        switch(move[i].type)
        {
        case TIGER_CAPTURE:
            TigerCapture(move[i], tempTigerPos, cornerMoved, cornerLeft);

            val = TigerMiniMax(depth + 1, alpha, beta);

            if (val > alpha)
            {
                alpha = val;
                if (depth == 0)
                {
                    moveFrom = move[i].from;
                    moveTo = move[i].to;
                }
            }

            RevertTigerCapture(move[i], tempTigerPos, cornerMoved, cornerLeft);

            if (alpha >= beta)
            {
                return alpha;
            }

            break;


        case TIGER_MOVE:
            TigerMove(move[i], tempTigerPos, cornerMoved, cornerLeft);

            val = TigerMiniMax(depth + 1, alpha, beta);

            if (val > alpha)
            {
                alpha = val;
                if (depth == 0)
                {
                    moveFrom = move[i].from;
                    moveTo = move[i].to;
                }
            }

            RevertTigerMove(move[i], tempTigerPos, cornerMoved, cornerLeft);

            if (alpha >= beta)
            {
                return alpha;
            }

            break;

        case GOAT_PLACE:
            GoatPlace(move[i]);

            val = TigerMiniMax(depth + 1, alpha, beta);

            if (val < beta)
            {
                beta = val;
            }

            RevertGoatPlace(move[i]);

            if (alpha >= beta)
            {
                return beta;
            }

            break;

        case GOAT_MOVE:
            GoatMove(move[i]);

            val = TigerMiniMax(depth + 1, alpha, beta);

            if (val < beta)
            {
                beta = val;
            }

            RevertGoatMove(move[i]);

            if (alpha >= beta)
            {
                return beta;
            }
            break;
        }
    }

    if (aiTurn == Tiger)
        return alpha;
    else
        return beta;
}

int AI::GoatMiniMax(int depth, int alpha, int beta)
{
    int posVal = GoatEvaluatePosition(depth);

    if (depth == flags->searchDepth || posVal == +INF - depth || posVal == -INF)
    {
        posVal = posVal == +INF - depth? posVal - 1: posVal + 1;
        return posVal;
    }

    int counter = 0;
    Move move[21];

    GenerateMoveList(counter, move);

    int val, tempTigerPos;
    bool cornerMoved = false;
    bool cornerLeft = false;

    for (int i = 0; i < counter; i++)
    {
        switch(move[i].type)
        {
        case TIGER_CAPTURE:

            TigerCapture(move[i], tempTigerPos, cornerMoved, cornerLeft);

            val = GoatMiniMax(depth + 1, alpha, beta);

            if (val < beta)
            {
                beta = val;
            }

            RevertTigerCapture(move[i], tempTigerPos, cornerMoved, cornerLeft);

            if (alpha >= beta)
            {
                return beta;
            }

            break;


        case TIGER_MOVE:

            TigerMove(move[i], tempTigerPos, cornerMoved, cornerLeft);

            val = GoatMiniMax(depth + 1, alpha, beta);

            if (val < beta)
            {
                beta = val;
            }

            RevertTigerMove(move[i], tempTigerPos, cornerMoved, cornerLeft);

            if (alpha >= beta)
            {
                return beta;
            }

            break;

        case GOAT_PLACE:

            GoatPlace(move[i]);

            val = GoatMiniMax(depth + 1, alpha, beta);

            if (val > alpha)
            {
                alpha = val;
                if (depth == 0)
                {
                    moveFrom = move[i].from;
                    moveTo = move[i].to;
                }
            }

            RevertGoatPlace(move[i]);

            if (alpha >= beta)
            {
                return alpha;
            }

            break;

        case GOAT_MOVE:

            GoatMove(move[i]);

            val = GoatMiniMax(depth + 1, alpha, beta);

            if (val > alpha)
            {
                alpha = val;
                if (depth == 0)
                {
                    moveFrom = move[i].from;
                    moveTo = move[i].to;
                }
            }

            RevertGoatMove(move[i]);

            if (alpha >= beta)
            {
                return alpha;
            }

            break;
        }
    }

    if (aiTurn == Goat)
        return alpha;
    else
        return beta;
}

void AI::TigerCapture(Move & move, int & tempTigerPos, bool & cornerMoved, bool & cornerLeft)
{
    board->point[move.to].SetState(T);
    board->point[(move.to + move.from)/2].SetState(N);
    board->point[move.from].SetState(N);

    for (int k = 0; k < 4; k++)
    {
        if (aiTigerPos[k] == move.from)
        {
            aiTigerPos[k] = move.to;
            tempTigerPos = k;
            break;
        }
    }

    aiTurn = Goat;
    aiDeadGoats++;

    for (int y = 0; y < 4; y++)
    {
        if(move.to == corner[y])
        {
            cornersOccupied++;
            cornerMoved = true;
        }
        else if (move.from == corner[y])
        {
            cornersOccupied--;
            cornerLeft = true;
        }
    }
}

void AI::RevertTigerCapture(Move & move, int & tempTigerPos, bool & cornerMoved, bool & cornerLeft)
{
    board->point[move.to].SetState(N);
    board->point[(move.to + move.from)/2].SetState(G);
    board->point[move.from].SetState(T);

    aiTigerPos[tempTigerPos] = move.from;
    aiDeadGoats--;
    aiTurn = Tiger;

    if (cornerMoved)
    {
        cornersOccupied--;
        cornerMoved = false;
    }
    else if (cornerLeft)
    {
        cornersOccupied++;
        cornerLeft = false;
    }
}

void AI::TigerMove(Move & move, int & tempTigerPos, bool & cornerMoved, bool & cornerLeft)
{
    board->point[move.to].SetState(T);
    board->point[move.from].SetState(N);

    for (int j = 0; j < 4; j++)
    {
        if (aiTigerPos[j] == move.from)
        {
            aiTigerPos[j] = move.to;
            tempTigerPos = j;
            break;
        }
    }

    aiTurn = Goat;

    for (int y = 0; y < 4; y++)
    {
        if(move.to == corner[y])
        {
            cornersOccupied++;
            cornerMoved = true;
        }

        else if (move.from == corner[y])
        {
            cornersOccupied--;
            cornerLeft = true;
        }
    }
}

void AI::RevertTigerMove(Move & move, int & tempTigerPos, bool & cornerMoved, bool & cornerLeft)
{
    board->point[move.from].SetState(T);
    board->point[move.to].SetState(N);

    aiTigerPos[tempTigerPos] = move.from;

    aiTurn = Tiger;

    if (cornerMoved)
    {
        cornersOccupied--;
        cornerMoved = false;
    }

    else if (cornerLeft)
    {
        cornersOccupied++;
        cornerLeft = false;
    }
}

void AI::GoatPlace(Move & move)
{
    board->point[move.to].SetState(G);
    aiGoatsToBePlaced--;
    aiTurn = Tiger;
}

void AI::RevertGoatPlace(Move & move)
{
    aiGoatsToBePlaced++;
    board->point[move.to].SetState(N);
    aiTurn = Goat;
}

void AI::GoatMove(Move & move)
{
    board->point[move.to].SetState(G);
    board->point[move.from].SetState(N);
    aiTurn = Tiger;
}

void AI::RevertGoatMove(Move & move)
{
    board->point[move.to].SetState(N);
    board->point[move.from].SetState(G);
    aiTurn = Goat;
}

int AI::TigersHuddled()
{
    int huddle = 0;
    for (int j = 0; j < 4; j++)
    {
        if (abs(aiTigerPos[0] - aiTigerPos[1]) <= direction[j])
            huddle++;

        if (abs(aiTigerPos[0] - aiTigerPos[2]) <= direction[j])
            huddle++;

        if (abs(aiTigerPos[0] - aiTigerPos[3]) <= direction[j])
            huddle++;

        if (abs(aiTigerPos[1] - aiTigerPos[2]) <= direction[j])
            huddle++;

        if (abs(aiTigerPos[1] - aiTigerPos[3]) <= direction[j])
            huddle++;

        if (abs(aiTigerPos[2] - aiTigerPos[3]) <= direction[j])
            huddle++;
    }

    return huddle;
}

int AI::PossibleCaptures()
{
    int possibleCaptureNumber = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (aiTigerPos[i]+2*direction[j] > 0 && aiTigerPos[i]+2*direction[j] < 26)
            {
                if (tigerPlayer->CanCapture(board, aiTigerPos[i]+2*direction[j], aiTigerPos[i]))
                {
                    possibleCaptureNumber++;
                }
            }

            if (aiTigerPos[i]-2*direction[j] > 0 && aiTigerPos[i]-2*direction[j] < 26)
            {
                if (tigerPlayer->CanCapture(board, aiTigerPos[i]-2*direction[j], aiTigerPos[i]))
                {
                    possibleCaptureNumber++;
                }
            }
        }
    }
    return possibleCaptureNumber;
}

int AI::TigersTrapped(Board * brd)
{
    int tigersTrapped = 0;
    for (int i = 0; i < 4; i++)
    {
        if (!tigerPlayer->ValidMoves(aiTigerPos[i], board))
            tigersTrapped++;
    }
    return tigersTrapped;
}

int AI::MovableToCorner()
{
    int movable = 0;
    for (int k = 0; k < 4; k++)
    {
        for (int l = 0; l < 4; l++)
        {
            if (tigerPlayer->IsMovable(board, corner[l], aiTigerPos[k]))
                movable++;
        }
    }
    return movable;
}

int AI::GhostGoats()
{
    int ghostGoats = 0;
    bool gg = true;

    for (int i = 1; i < 26; i++)
    {
        if (board->point[i].GetState() == N)
        {
            for (int j = 0; j < 4; j++)
            {
                //so as not to check diagonal for even points
                if (!(i%2 == 0 && (j == 1 || j == 3)))
                {
                    if (i + direction[j] < 26)
                    {
                        if(board->point[i + direction[j]].GetState() != G)
                        {
                            gg = false;
                            break;
                        }
                    }

                    if (i - direction[j] > 0)
                    {
                        if(board->point[i - direction[j]].GetState() != G)
                        {
                            gg = false;
                            break;
                        }
                    }
                }
            }

            if (gg)
            {
                ghostGoats++;
            }
            gg = true;
        }
    }
    return ghostGoats;
}

//void AI::PrintBoard()
//{
//    for(int i = 1; i < 26; i++)
//    {
//        ofile << board->point[i].GetState();
//        ofile << " ";
//
//        if (i%5 == 0)
//        {
//            ofile << endl;
//        }
//    }
//    ofile << endl << endl;
//}
