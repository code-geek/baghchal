#ifndef GAME_H
#define GAME_H

#include "Headers.h"
#include "Input.h"
#include "Board.h"
#include "Sprites.h"
#include "Text.h"
#include "Tiger.h"
#include "Goat.h"
#include "Flags.h"
#include "GameState.h"
#include "AI.h"
#include "MainMenu.h"
#include "Sound.h"

class Game
{
private:
    RenderWindow App;

    Board board;
    Flags flags;
    MainMenu mainMenu;
    SoundClass sound;

    Clock TigerTimer;
    Clock GoatTimer;

    InputClass * input;
    Sprites * sprites;
    Text * texts;
    TigerPlayer * tigerPlayer;
    GoatPlayer * goatPlayer;
    AI * ai;

    GameState gameState[numberOfStates+2];//for the non-repetition rule

    bool init(); //initializes the variables and loads the images and the font, sets the initial position of sprites and text, sends the required pointers to corresponding classes
    void DrawStuff();
    void AIMove();
    void SyncBoards();
    void SetSearchDepth();
    void Timer();
    int FindOccupiedCorners();

    bool resetDepth;//used for ai
    bool firstRun;

public:
    Game();
    ~Game();

    bool Start(); //the function that contains the game loop.
};

#endif
