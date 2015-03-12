//Stores the 2 properties of a point: co-ordinates and state. Allows the setting and getting of these properties.

#ifndef MYPOINT_H
#define MYPOINT_H

#include "Headers.h"
#include "ActiveZone.h"

class MyPoint
{
private:
    int x, y; //co-ordinates of the point
    State state; //defines what to draw.

public:
    //accessors for getting private values
    int GetX() const;
    int GetY() const;
    State GetState() const;

    //accessors for setting private values
    void SetX(int inputX);
    void SetY(int inputY);
    void SetState(State inputState);
};

#endif
