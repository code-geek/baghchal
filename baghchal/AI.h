#ifndef AI_H
#define AI_H

#include "Headers.h"
#include "Board.h"
#include "Flags.h"
#include "Tiger.h"
#include "Goat.h"

class AI
{
private:
    enum MoveType {GOAT_MOVE = 0, GOAT_PLACE, TIGER_MOVE, TIGER_CAPTURE};

    Board * board;
    Flags * flags;
    TigerPlayer * tigerPlayer;
    GoatPlayer * goatPlayer;

    int moveTo, moveFrom;//final move selected by the tree is set in these variables.

    Clock AITimer;

    struct Move
    {
        int from;
        int to;
        MoveType type;
    };//a move is like a key which changes the ai board and can be used to revert the change.

    //temporary flags for ai analysis of board pos
    Player aiTurn;

    int aiGoatsToBePlaced;
    int aiDeadGoats;
    int aiTigerPos[4];
    int distFromCorner[4];

    int cornersOccupied;

    //evaluation functions and minimax search tree: the heart of the ai.
    int TigerEvaluatePosition();
    int GoatEvaluatePosition(int depth);

    int TigerMiniMax(int depth, int alpha = -INF, int beta = +INF);
    int GoatMiniMax(int depth, int alpha = -INF, int beta = +INF);

    //additional functions needed for the evaluation of a position.
    int PossibleCaptures();
    int TigersTrapped(Board * brd);
    int MovableToCorner();
    int TigersHuddled();
    int GhostGoats();

    //generates the move list at each node and stores it in an array. the counter gives the number of moves generated.
    void GenerateMoveList(int & counter, Move move[]);

    //special win checking functions for the ai board
    bool TigerWinCheck();
    bool GoatWinCheck(Board * b);

    //these functions can change the ai board position, variables and revert the change.
    //The process is: change the position, analyze the result, revert the change.
    void TigerCapture(Move & move, int & tempTigerPos, bool & cornerMoved, bool & cornerLeft);
    void RevertTigerCapture(Move & move, int & tempTigerPos, bool & cornerMoved, bool & cornerLeft);

    void TigerMove(Move & move, int & tempTigerPos, bool & cornerMoved, bool & cornerLeft);
    void RevertTigerMove(Move & move, int & tempTigerPos, bool & cornerMoved, bool & cornerLeft);

    void GoatMove(Move & move);
    void RevertGoatMove(Move & move);

    void GoatPlace(Move & move);
    void RevertGoatPlace(Move & move);

    void PrintBoard();

    //to make the first move of goat ai faster.
    bool firstMove;

public:
    AI(Flags * f, TigerPlayer * t, GoatPlayer * g);
    ~AI();
    void initAI();//called from the game class
    bool MakeMove();//called from the game class

    //this is useful when observing ai vs ai game.
    void SlowDownAIMove();

    friend class Game;
    friend class TigerPlayer;
};

#endif
