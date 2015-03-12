#include "Input.h"

InputClass::InputClass(Flags * f, Board * b, Sprites * s, GoatPlayer * g, TigerPlayer * t, AI * a, MainMenu * m, SoundClass * snd, RenderWindow & App):Input(App.GetInput())
{
    flags = f;
    board = b;
    sprites = s;
    goatPlayer = g;
    tigerPlayer = t;
    ai = a;
    mainMenu = m;
    sound = snd;

    mousePressed = false;
    selectPressed = false;
    soundPlayed = true;
}

void InputClass::SelectButtonPressed()
{
    //select pressed first time
    if (!flags->selectPressed)
    {
        flags->selectPressed = true;
        flags->drawRepeatText = false;
        flags->drawInvalidMove = false;
        flags->highlightPoint = flags->selectorPoint; //to draw the highlight sprite

        DefineValidMovePoints();
    }

    //select pressed again while highlight is drawn
    else
    {
        //first erase the valid move dots.
        EraseValidMoveDots();

        if (flags->turn == Goat)
        {
            if (!flags->goatAIActive)
            {
                if(!goatPlayer->GoatLogic(flags->selectorPoint, flags->highlightPoint))
                    flags->drawInvalidMove = true;
                else
                {
                    flags->stateChanged = true;
                    sound->PlaySound();
                }
            }

        }

        else
        {
            if (!flags->tigerAIActive)
            {
                if(!tigerPlayer->TigerLogic(flags->selectorPoint, flags->highlightPoint))
                    flags->drawInvalidMove = true;
                else
                {
                    flags->stateChanged = true;
                    sound->PlaySound();
                }
            }
        }

        flags->selectPressed = false;
        flags->highlightIsDrawn = false;
    }

    flags->keyPressed = true;
    AITimer.Reset();
}

void InputClass::TimerUpdate()
{
    if (AITimer.GetElapsedTime() > AITime)
    {
        if (flags->keyPressed)
        {
            flags->keyPressed = false;
        }
        AITimer.Reset();
    }
}

//used to get input from the keyboarrd
void InputClass::GetInput(RenderWindow & App, Event & Event)
{
    // Move the selector
    //move up
    if (((Event.Type == Event::KeyPressed) && (Event.Key.Code == Key::Up)) && !flags->keyPressed)
    {
        //arrowPressed = true;
        if (flags->selectorPoint > 5)
        {
            sprites->Selector.Move(0, -dy);
            flags->selectorPoint -= 5;//adds -5 to the selector's current point
        }

        else
        {
            sprites->Selector.Move(0, 4*dy);
            flags->selectorPoint += 20;//adds 20 to the selector's current point
        }

        flags->keyPressed = true;
        AITimer.Reset();
    }

    //move down
    if (((Event.Type == Event::KeyPressed) && (Event.Key.Code == Key::Down)) && !flags->keyPressed)
    {
        //arrowPressed = true;
        if (flags->selectorPoint < 21)
        {
            sprites->Selector.Move(0, dy);
            flags->selectorPoint += 5;//adds 5 to the selector's current point
        }

        else
        {
            sprites->Selector.Move(0, -4*dy);
            flags->selectorPoint -= 20;//adds -20 to the selector's current point
        }

        flags->keyPressed = true;//for regulating the timer and slowing down the framerate
        AITimer.Reset();//resets the timer
    }

    //move left
    if (((Event.Type == Event::KeyPressed) && (Event.Key.Code == Key::Left)) && !flags->keyPressed)
    {
        //arrowPressed = true;
        if(flags->selectorPoint != 1)
        {
            if((flags->selectorPoint % 5) == 1)
            {
                sprites->Selector.Move(4*dx, -dy);
            }

            else
            {
                sprites->Selector.Move(-dx, 0);
            }

            flags->selectorPoint -= 1;

            flags->keyPressed = true;
            AITimer.Reset();
        }

        else
        {
            sprites->Selector.Move(4*dx, 4*dy);
            flags->selectorPoint = 25;

            flags->keyPressed = true;
            AITimer.Reset();
        }
    }

    //move right
    if (((Event.Type == Event::KeyPressed) && (Event.Key.Code == Key::Right)) && !flags->keyPressed)
    {
        //arrowPressed = true;
        if(flags->selectorPoint != 25)
        {
            if((flags->selectorPoint % 5) == 0)
            {
                sprites->Selector.Move(-4*dx, dy);
            }

            else
            {
                sprites->Selector.Move(dx, 0);
            }

            flags->selectorPoint += 1;

            flags->keyPressed = true;
            AITimer.Reset();
        }

        else
        {
            sprites->Selector.Move(-4*dx, -4*dy);
            flags->selectorPoint = 1;

            flags->keyPressed = true;
            AITimer.Reset();
        }
    }

    //defines what happens when the select key is pressed
    if (Input.IsKeyDown(sf::Key::Return) && !selectPressed)
    {
        selectPressed = true;
        SelectButtonPressed();
    }

    if ((Event.Type == Event::MouseMoved))
    {
        int a, b;
        a = Event.MouseMove.X;
        b = Event.MouseMove.Y;

        //move the selector
        MoveSelector(a, b);
    }

    if (((Input.IsMouseButtonDown(sf::Mouse::Left) || (Input.IsMouseButtonDown(sf::Mouse::Right))) && (!mousePressed)))
    {
        mousePressed = true;
        //perform the select button processing as before
        SelectButtonPressed();
    }

    if ((Event.Type == Event::MouseButtonReleased))
    {
        mousePressed = false;
    }

    if ((Event.Type == Event::KeyReleased))
    {
        selectPressed = false;
    }
}

void InputClass::MoveSelector(int a, int b)
{
    int hoverPoint = 13;//just initializing it to the central point so that it doesnt have a garbage value.
    for (int i = 1; i < 26; i++)
    {
        if(sprites->point[i].zone.LiesInZone(a, b))
        {
            hoverPoint = i;

            //move the selector to the hovered point and set it as the new selector point
            sprites->Selector.Move(board->point[hoverPoint].GetX() - board->point[flags->selectorPoint].GetX(), board->point[hoverPoint].GetY() - board->point[flags->selectorPoint].GetY());
            flags->selectorPoint = hoverPoint;
            break;
        }
    }

    flags->keyPressed = true;
    AITimer.Reset();
}

void InputClass::DefineValidMovePoints()
{
    //defines which points to show the valid move signals on
    if (((flags->turn == Tiger) && (board->point[flags->highlightPoint].GetState() == T))
            || ((flags->turn == Goat) && (flags->goatsToBePlaced == 0) && (board->point[flags->highlightPoint].GetState() == G)))
    {
        //look for moves in all four directions
        for(int i = 0; i < 4; i++)
        {
            //move conditions
            if((flags->highlightPoint + direction[i] < 26) && (tigerPlayer->IsMovable(board, flags->highlightPoint + direction[i], flags->highlightPoint)))
            {
                board->point[flags->highlightPoint + direction[i]].SetState(V);
            }

            if((flags->highlightPoint - direction[i] > 0) && (tigerPlayer->IsMovable(board, flags->highlightPoint - direction[i], flags->highlightPoint)))
            {
                board->point[flags->highlightPoint - direction[i]].SetState(V);
            }

            //capture conditions
            if (flags->turn == Tiger)
            {
                if((flags->highlightPoint + 2 * direction[i] < 26) && (tigerPlayer->CanCapture(board, flags->highlightPoint + 2 * direction[i], flags->highlightPoint)))
                {
                    board->point[flags->highlightPoint + 2 * direction[i]].SetState(V);
                }

                if((flags->highlightPoint - 2 * direction[i] > 0) && (tigerPlayer->CanCapture(board, flags->highlightPoint - 2 * direction[i], flags->highlightPoint)))
                {
                    board->point[flags->highlightPoint - 2 * direction[i]].SetState(V);
                }
            }
        }
    }
}

void InputClass::EraseValidMoveDots()
{
    for (int i = 1; i < 26; i++)
    {
        if (board->point[i].GetState() == V)
        {
            board->point[i].SetState(N);
        }
    }
}

void InputClass::MainMenuInput(RenderWindow & App, Event & Event)
{
    switch (mainMenu->mState)
    {
    //normal
    case NORMAL:
        NormalStateInput(App, Event);
        break;

    //credits
    case CREDITS:
        CreditsStateInput(App, Event);
        break;

    //levels
    case LEVELS:
        LevelsStateInput(App, Event);
        break;

    case GAME:
        break;
    }
}

void InputClass::NormalStateInput(RenderWindow & App, Event & Event)
{
    if ((Event.Type == Event::MouseMoved))
    {
        int a, b;
        a = Event.MouseMove.X;
        b = Event.MouseMove.Y;

        if (mainMenu->NormalZone[0].LiesInZone(a, b))
        {
            mainMenu->nState = C_GOAT;
            sound->hover = 0;

            if (!soundPlayed)
            {
                sound->PlaySound();
                soundPlayed = true;
            }
        }

        else if (mainMenu->NormalZone[1].LiesInZone(a, b))
        {
            mainMenu->nState = C_TIGER;
            sound->hover = 1;

            if (!soundPlayed)
            {
                sound->PlaySound();
                soundPlayed = true;
            }
        }

        else if (mainMenu->NormalZone[2].LiesInZone(a, b))
        {
            mainMenu->nState = HUMAN;
            sound->hover = 2;

            if (!soundPlayed)
            {
                sound->PlaySound();
                soundPlayed = true;
            }
        }

        else if (mainMenu->NormalZone[3].LiesInZone(a, b))
        {
            mainMenu->nState = EXIT;
            sound->hover = 3;

            if (!soundPlayed)
            {
                sound->PlaySound();
                soundPlayed = true;
            }
        }

        else if (mainMenu->NormalZone[4].LiesInZone(a, b))
        {
            mainMenu->nState = NCREDITS;
            sound->hover = 4;

            if (!soundPlayed)
            {
                sound->PlaySound();
                soundPlayed = true;
            }
        }

        else
        {
            sound->hover = -1;
            mainMenu->nState = NBASE;
        }
    }

    if ((Input.IsMouseButtonDown(sf::Mouse::Left) || (Input.IsMouseButtonDown(sf::Mouse::Right))))
    {
        mousePressed = true;
        switch(mainMenu->nState)
        {
        case NBASE:
            break;

        case C_GOAT:
            flags->goatAIActive = true;
            flags->tigerAIActive = false;
            mainMenu->mState = LEVELS;
            break;

        case C_TIGER:
            flags->tigerAIActive = true;
            flags->goatAIActive = false;
            mainMenu->mState = LEVELS;
            break;

        case HUMAN:
            flags->posRepeatRuleActive = true;
            flags->mainMenuOn = false;
            mainMenu->mState = GAME;
            break;

        case EXIT:
            flags->mainMenuOn = false;
            App.Close();
            break;

        case NCREDITS:
            mainMenu->mState = CREDITS;
            mainMenu->cState = CBASE;
            //show credits
            break;
        }
    }

    if ((Event.Type == Event::MouseButtonReleased))
    {
        mousePressed = false;
    }
}

void InputClass::CreditsStateInput(RenderWindow & App, Event & Event)
{
    if ((Event.Type == Event::MouseMoved))
    {
        int a, b;
        a = Event.MouseMove.X;
        b = Event.MouseMove.Y;

        if (mainMenu->CreditsZone.LiesInZone(a, b))
        {
            mainMenu->cState = HIGHLIGHT;
            sound->hover = 5;

            if (!soundPlayed)
            {
                sound->PlaySound();
                soundPlayed = true;
            }
        }

        else
        {
            sound->hover = -1;
            mainMenu->cState = CBASE;
        }
    }

    if ((Input.IsMouseButtonDown(sf::Mouse::Left) || (Input.IsMouseButtonDown(sf::Mouse::Right))))
    {
        mousePressed = true;
        switch(mainMenu->cState)
        {
        case CBASE:
            break;

        case HIGHLIGHT:
            mainMenu->mState = NORMAL;
            mainMenu->nState = NBASE;
            break;
        }
    }

    if ((Event.Type == Event::MouseButtonReleased))
    {
        mousePressed = false;
    }
}

void InputClass::LevelsStateInput(RenderWindow & App, Event & Event)
{
    if ((Event.Type == Event::MouseMoved))
    {
        int a, b;
        a = Event.MouseMove.X;
        b = Event.MouseMove.Y;

        if (mainMenu->LevelZone[0].LiesInZone(a, b))
        {
            mainMenu->lState = L1;
            sound->hover = 6;

            if (!soundPlayed)
            {
                sound->PlaySound();
                soundPlayed = true;
            }
        }

        else if (mainMenu->LevelZone[1].LiesInZone(a, b))
        {
            mainMenu->lState = L2;
            sound->hover = 7;

            if (!soundPlayed)
            {
                sound->PlaySound();
                soundPlayed = true;
            }
        }

        else if (mainMenu->LevelZone[2].LiesInZone(a, b))
        {
            mainMenu->lState = L3;
            sound->hover = 8;

            if (!soundPlayed)
            {
                sound->PlaySound();
                soundPlayed = true;
            }
        }

        else if (mainMenu->LevelZone[3].LiesInZone(a, b))
        {
            mainMenu->lState = L4;
            sound->hover = 9;

            if (!soundPlayed)
            {
                sound->PlaySound();
                soundPlayed = true;
            }
        }

        else if (mainMenu->LevelZone[4].LiesInZone(a, b))
        {
            mainMenu->lState = L5;
            sound->hover = 10;

            if (!soundPlayed)
            {
                sound->PlaySound();
                soundPlayed = true;
            }
        }

        else
        {
            sound->hover = -1;
            mainMenu->lState = LBASE;
        }
    }

    if ((Input.IsMouseButtonDown(sf::Mouse::Left) || (Input.IsMouseButtonDown(sf::Mouse::Right))))
    {
        mousePressed = true;
        switch(mainMenu->lState)
        {
        case LBASE:
            break;

        case L1:
            flags->searchDepth = 2;
            flags->mainMenuOn = false;
            mainMenu->mState = GAME;
            break;

        case L2:
            flags->searchDepth = 4;
            flags->mainMenuOn = false;
            mainMenu->mState = GAME;
            break;

        case L3:
            flags->searchDepth = 6;
            flags->mainMenuOn = false;
            mainMenu->mState = GAME;
            break;

        case L4:
            flags->searchDepth = 8;
            flags->mainMenuOn = false;
            mainMenu->mState = GAME;
            break;

        case L5:
            flags->searchDepth = 10;
            flags->mainMenuOn = false;
            mainMenu->mState = GAME;
            break;
        }
    }

    if ((Event.Type == Event::MouseButtonReleased))
    {
        mousePressed = false;
    }
}
