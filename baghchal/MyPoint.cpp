#include "MyPoint.h"

int MyPoint::GetX() const
{
    return x;
}

int MyPoint::GetY() const
{
    return y;
}

State MyPoint::GetState() const
{
    return state;
}

void MyPoint::SetX(int inputX)
{
    x = inputX;
}

void MyPoint::SetY(int inputY)
{
    y = inputY;
}

void MyPoint::SetState(State inputState)
{
    state = inputState;
}
