#ifndef TIGER_H
#define TIGER_H

#include "MyPlayer.h"

class TigerPlayer : public MyPlayer
{
private:
    void WinCheck();
    int ValidMoves(int tigerPoint, Board * brd);
    bool CanTigersMove(int tPos[], Board * brd);

    int tigerPos[4];//the position of the 4 tigers.

public:
    TigerPlayer(Flags * f, Board * b, GameState * g, Sprites * s);

    //overload the virtual function to make the class non-abstract
    void MakeObject() {}

    bool CanCapture(Board * brd, int m, int n);
    void MoveCheck(Board * brd, int x, int y, int & move);
    void SetTigerPos();
    bool TigerLogic(int sp, int hp);
    void GenerateMoveList(int & counter);

    friend class GoatPlayer;
    friend class AI;
    friend class Game;
};

#endif
