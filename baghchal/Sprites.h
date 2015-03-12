#ifndef SPRITES_H
#define SPRITES_H

#include "Headers.h"
#include "ImgManager.h"
#include "Board.h"
#include "Flags.h"
#include "MainMenu.h"

class Sprites
{
private:
    ImgManager img;
    Flags * flags;
    Board * board;
    MainMenu * mainMenu;

    //Sprites needed
    Sprite BoardSprite;
    Sprite Background;
    Sprite Selector;
    Sprite LastMove[2];
    Sprite HighLight;
    Sprite Menu;

    Sprite mmGoat, mmTiger, mmHuman, mmExit, mmCredits, mmBack, mmCreditsText;
    Sprite l1, l2, l3, l4, l5;

    struct PointSprite
    {
        Sprite pnt; //each point has a sprite which is used to draw the tiger and goat according to the state.
        ActiveZone zone; //the zone of each point. defines the area for mouse input.
        bool isDrawn;//checks whether the point's sprite has been drawn already
    } point[26];

public:
    Sprites(Flags * f, Board * b, MainMenu * m);

    void SetSpriteImages();
    void SetPointSpritePosition();
    void InitMMSprites();

    void DrawPointSprites(RenderWindow & App);
    void DrawHighlightSprite(RenderWindow & App);
    void DrawLastMove(RenderWindow & App);
    void DrawSelector(RenderWindow & App);
    void DrawPermanentSprites(RenderWindow & App);//board, background, selector
    void DrawMainMenuSprite(RenderWindow & App);

    void SetBoardPos();
    void DrawValidMove();

    bool ImgLoader();

    friend class InputClass;
    friend class Game;
    friend class TigerPlayer;
    friend class GoatPlayer;
};

#endif
