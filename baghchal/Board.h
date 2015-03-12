#ifndef BOARD_H
#define BOARD_H

#include "MyPoint.h"

class Board
{
private:
    int incrementX;
    int incrementY;
public:
    MyPoint point[26]; //each point of the board. point[0] is avoided and point[1] to point[25] are used.
    void SetIncrements(int X, int Y);
    void SetPoints(int initialX, int initialY); //used to define the co-ordinates of the points on the board.
    void Reset();//resets the original board position

    friend class MyPlayer;
    friend class TigerPlayer;
};

#endif
