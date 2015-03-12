//takes input from the keyboard and mouse and does the processing of that input

#ifndef INPUT_H
#define INPUT_H

#include "Headers.h"
#include "Flags.h"
#include "Sprites.h"
#include "Goat.h"
#include "Tiger.h"
#include "AI.h"
#include "MainMenu.h"
#include "Sound.h"

class InputClass
{
private:
    Flags * flags;
    Board * board;
    Sprites * sprites;
    GoatPlayer * goatPlayer;
    TigerPlayer * tigerPlayer;
    AI * ai;
    MainMenu * mainMenu;
    SoundClass * sound;

    Clock AITimer;

    bool mousePressed;
    bool selectPressed;
    bool soundPlayed;

    const sf::Input& Input;

    void MoveSelector(int a, int b);
    void SelectButtonPressed();
    void DefineValidMovePoints();
    void EraseValidMoveDots();

    void NormalStateInput(RenderWindow & App, Event & Event);
    void CreditsStateInput(RenderWindow & App, Event & Event);
    void LevelsStateInput(RenderWindow & App, Event & Event);

public:
    InputClass(Flags * f, Board * b, Sprites * s, GoatPlayer * g, TigerPlayer * t, AI * a, MainMenu * m, SoundClass * snd, RenderWindow & App);
    void TimerUpdate(); //slows down the input process
    void GetInput(RenderWindow & App, Event & Event); //takes the input from the keyboard and mouse.
    void MainMenuInput(RenderWindow & App, Event & Event);

    friend class Game;
};

#endif
