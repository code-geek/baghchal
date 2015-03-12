#ifndef GOAT_H
#define GOAT_H

#include "MyPlayer.h"
#include "Tiger.h"

class GoatPlayer : public MyPlayer
{
private:
    TigerPlayer * tiger;

public:
    GoatPlayer(Flags * f, Board * b, GameState * g, TigerPlayer * t, Sprites * s);

    //overload the virtual function to make the class non-abstract
    void MakeObject() {}

    bool GoatLogic(int sp, int hp);
};

#endif
