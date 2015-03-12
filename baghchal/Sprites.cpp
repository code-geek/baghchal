#include "Sprites.h"
#include "Game.h"

Sprites::Sprites(Flags * f, Board * b, MainMenu * m)
{
    flags = f;
    board = b;
    mainMenu = m;
}

void Sprites::SetPointSpritePosition()
{
    for (int i = 1; i < 26; i++)
    {
        point[i].pnt.SetPosition(board->point[i].GetX() - playerWidth/2, board->point[i].GetY() - playerHeight/2);
        point[i].zone.SetZone(board->point[i].GetX(), board->point[i].GetY());
    }
}

void Sprites::SetSpriteImages()
{
    // Create the sprites of the board, background
    BoardSprite.SetImage(img.boardimg);
    Background.SetImage(img.backgroundimg);

    //selectors
    Selector.SetImage(img.selectorimg);

    LastMove[0].SetImage(img.lastmoveimg);//from point
    LastMove[1].SetImage(img.lastmoveimg);//to point

    HighLight.SetImage(img.highlightimg);
}

void Sprites::SetBoardPos()
{
    BoardSprite.SetPosition(boardX, boardY);
}

void Sprites::DrawLastMove(RenderWindow & App)
{
    if (flags->drawLastMove == true)
    {
        //from point
        LastMove[0].SetPosition(board->point[flags->fromPoint].GetX() - selectorWidth/2, board->point[flags->fromPoint].GetY() - selectorHeight/2);
        //to point
        LastMove[1].SetPosition(board->point[flags->toPoint].GetX() - selectorWidth/2, board->point[flags->toPoint].GetY() - selectorHeight/2);

        App.Draw(LastMove[1]);
        App.Draw(LastMove[0]);
    }
}

void Sprites::DrawPointSprites(RenderWindow & App)
{
    for (int i = 1; i < 26; i++)
    {
        switch(board->point[i].GetState())
        {
        case N:
            break;

        case T:
            if (!point[i].isDrawn)
            {
                //clear the image stored first
                point[i].pnt.SetImage(img.tigerimg);
                point[i].isDrawn = true;
            }

            App.Draw(point[i].pnt);
            break;

        case G:
            if (!point[i].isDrawn)
            {
                point[i].pnt.SetImage(img.goatimg);
                point[i].isDrawn = true;
            }

            App.Draw(point[i].pnt);
            break;

        case V:
            App.Draw(sf::Shape::Circle(float(board->point[i].GetX()+1),float(board->point[i].GetY()+1),float(10/1.5),sf::Color(0,100,100)));
            break;
        }
    }
}

void Sprites::DrawHighlightSprite(RenderWindow & App)
{
    if (flags->selectPressed)
    {
        if (!flags->highlightIsDrawn)
        {
            HighLight.SetPosition(Selector.GetPosition().x, Selector.GetPosition().y);
        }

        App.Draw(HighLight);
        flags->highlightIsDrawn = true;
    }
}

void Sprites::DrawPermanentSprites(RenderWindow & App)
{
    // Draw the background, board
    App.Draw(Background);
    App.Draw(BoardSprite);
}

void Sprites::DrawSelector(RenderWindow & App)
{
    App.Draw(Selector);
}

bool Sprites::ImgLoader()
{
    if (!img.LoadImages())
    {
        return false;
    }

    return true;
}

void Sprites::DrawMainMenuSprite(RenderWindow & App)
{
    App.Draw(Menu);

    switch (mainMenu->mState)
    {
    case NORMAL:
        switch (mainMenu->nState)
        {
        case NBASE:
            mmGoat.SetImage(img.mmGoat);
            mmTiger.SetImage(img.mmTiger);
            mmHuman.SetImage(img.mmHuman);
            mmExit.SetImage(img.mmExit);
            mmCredits.SetImage(img.mmCredits);
            break;

        case C_GOAT:
            mmGoat.SetImage(img.mmGoatH);
            mmTiger.SetImage(img.mmTiger);
            mmHuman.SetImage(img.mmHuman);
            mmExit.SetImage(img.mmExit);
            mmCredits.SetImage(img.mmCredits);
            break;

        case C_TIGER:
            mmGoat.SetImage(img.mmGoat);
            mmTiger.SetImage(img.mmTigerH);
            mmHuman.SetImage(img.mmHuman);
            mmExit.SetImage(img.mmExit);
            mmCredits.SetImage(img.mmCredits);
            break;

        case HUMAN:
            mmGoat.SetImage(img.mmGoat);
            mmTiger.SetImage(img.mmTiger);
            mmHuman.SetImage(img.mmHumanH);
            mmExit.SetImage(img.mmExit);
            mmCredits.SetImage(img.mmCredits);
            break;

        case EXIT:
            mmGoat.SetImage(img.mmGoat);
            mmTiger.SetImage(img.mmTiger);
            mmHuman.SetImage(img.mmHuman);
            mmExit.SetImage(img.mmExitH);
            mmCredits.SetImage(img.mmCredits);
            break;

        case NCREDITS:
            mmGoat.SetImage(img.mmGoat);
            mmTiger.SetImage(img.mmTiger);
            mmHuman.SetImage(img.mmHuman);
            mmExit.SetImage(img.mmExit);
            mmCredits.SetImage(img.mmCreditsH);
            break;
        }

        App.Draw(mmGoat);
        App.Draw(mmTiger);
        App.Draw(mmHuman);
        App.Draw(mmExit);
        App.Draw(mmCredits);

        break;

    case CREDITS:
        switch(mainMenu->cState)
        {
        case CBASE:
            mmBack.SetImage(img.mmBack);
            break;

        case HIGHLIGHT:
            mmBack.SetImage(img.mmBackH);
            break;
        }

        App.Draw(mmCreditsText);
        App.Draw(mmBack);

        break;

    case LEVELS:
        switch (mainMenu->lState)
        {
        case LBASE:
            l1.SetImage(img.l1);
            l2.SetImage(img.l2);
            l3.SetImage(img.l3);
            l4.SetImage(img.l4);
            l5.SetImage(img.l5);
            break;

        case L1:
            l1.SetImage(img.l1H);
            l2.SetImage(img.l2);
            l3.SetImage(img.l3);
            l4.SetImage(img.l4);
            l5.SetImage(img.l5);
            break;

        case L2:
            l1.SetImage(img.l1);
            l2.SetImage(img.l2H);
            l3.SetImage(img.l3);
            l4.SetImage(img.l4);
            l5.SetImage(img.l5);
            break;

        case L3:
            l1.SetImage(img.l1);
            l2.SetImage(img.l2);
            l3.SetImage(img.l3H);
            l4.SetImage(img.l4);
            l5.SetImage(img.l5);
            break;

        case L4:
            l1.SetImage(img.l1);
            l2.SetImage(img.l2);
            l3.SetImage(img.l3);
            l4.SetImage(img.l4H);
            l5.SetImage(img.l5);
            break;

        case L5:
            l1.SetImage(img.l1);
            l2.SetImage(img.l2);
            l3.SetImage(img.l3);
            l4.SetImage(img.l4);
            l5.SetImage(img.l5H);
            break;
        }
        App.Draw(l1);
        App.Draw(l2);
        App.Draw(l3);
        App.Draw(l4);
        App.Draw(l5);
        break;

    case GAME:
        break;
    }
}

void Sprites::InitMMSprites()
{
    Menu.SetImage(img.mmBase);
    mmGoat.SetImage(img.mmGoat);
    mmTiger.SetImage(img.mmTiger);
    mmHuman.SetImage(img.mmHuman);
    mmExit.SetImage(img.mmExit);
    mmCredits.SetImage(img.mmCredits);
    mmCreditsText.SetImage(img.mmCreditsText);
    l1.SetImage(img.l1);
    l2.SetImage(img.l2);
    l3.SetImage(img.l3);
    l4.SetImage(img.l4);
    l5.SetImage(img.l5);

    mmTiger.SetPosition(212, 285);
    mmGoat.SetPosition(216, 215);
    mmHuman.SetPosition(185, 355);
    mmExit.SetPosition(14, 439);
    mmCredits.SetPosition(730, 439);
    mmCreditsText.SetPosition(40, 192);
    mmBack.SetPosition(20, 439);
    l1.SetPosition(350, 180);
    l2.SetPosition(350, 245);
    l3.SetPosition(350, 310);
    l4.SetPosition(350, 375);
    l5.SetPosition(350, 440);
}
