#ifndef MAINMENU_H
#define MAINMENU_H

#include "ActiveZone.h"

enum MenuState {NORMAL=0, CREDITS, LEVELS, GAME};
enum NormalState {NBASE = 0, C_GOAT, C_TIGER, HUMAN, EXIT, NCREDITS};
enum CreditsState {CBASE=0, HIGHLIGHT};
enum LevelsState {LBASE = 0, L1, L2, L3, L4, L5};

class MainMenu
{
private:
    ActiveZone NormalZone[5];
    ActiveZone CreditsZone;
    ActiveZone LevelZone[5];

public:
    MenuState mState;
    NormalState nState;
    CreditsState cState;
    LevelsState lState;

    void Initialize();

    friend class InputClass;
    friend class Sprites;
};

#endif
