#include "Game.h"

Game::Game()
{
    sprites = new Sprites(&flags, &board, &mainMenu);
    texts = new Text(&flags);
    tigerPlayer = new TigerPlayer(&flags, &board, &gameState[1], sprites);
    goatPlayer = new GoatPlayer(&flags, &board, &gameState[1], tigerPlayer, sprites);
    ai = new AI(&flags, tigerPlayer, goatPlayer);
    input = new InputClass(&flags, &board, sprites, goatPlayer, tigerPlayer, ai, &mainMenu, &sound, App);
}

Game::~Game()
{
    delete input;
    delete ai;
    delete goatPlayer;
    delete tigerPlayer;
    delete texts;
    delete sprites;
}

//initializes the variables and loads the images and the font, sets the initial position of sprites and text, sends the required pointers to corresponding classes
bool Game::init()
{
    //set the initial values of the flags.
    flags.isPlaying = true;
    flags.tigerAIActive = false;
    flags.goatAIActive = false;
    flags.keyPressed = false;
    flags.highlightIsDrawn = false;
    flags.drawLastMove = false;
    flags.selectPressed = false;
    flags.isPosRepeated = false;
    flags.drawRepeatText = false;
    flags.drawInvalidMove = false;
    flags.aiThinking = false;
    flags.mainMenuOn = true;
    flags.posRepeatRuleActive = false;
    flags.stateChanged = false;
    flags.drawThinking = false;
    flags.timeSet = false;
    flags.turn = Goat;
    flags.goatsToBePlaced = 20;
    flags.deadGoats = 0;
    flags.selectorPoint = 13;
    flags.gsCounter = 1;
    flags.searchDepth = 4;
    flags.prevState = -1;
    flags.ts = 0;
    flags.gs = 0;
    flags.tm = totalTime;
    flags.gm = totalTime;
    firstRun = true;
    resetDepth = false;

    // Load the images used in the game
    if (!sprites->ImgLoader())
    {
        return false;
    }

    // Load the text font
    if (!texts->LoadFont())
    {
        return false;
    }

    // Load the sound
    if (!sound.LoadSound())
    {
        return false;
    }

    //set the co-ordinates of the points
    board.SetIncrements(dx, dy);
    board.SetPoints(boardX, boardY);

    //set the positions of the strings to be printed, the board, and the point sprites
    texts->SetTextPositions();
    sprites->SetPointSpritePosition();
    sprites->SetBoardPos();

    //sets the images of the background, board, selector, highlight and valid move
    sprites->SetSpriteImages();
    sprites->InitMMSprites();

    //defines the initial position of the selector
    sprites->Selector.SetPosition(board.point[flags.selectorPoint].GetX() - selectorWidth/2, board.point[flags.selectorPoint].GetY() - selectorHeight/2);

    //initialize the AI
    ai->initAI();

    mainMenu.Initialize();

    sound.hover = -1;

    for (int i = 0; i < numberOfStates+2; i++)
    {
        gameState[i].boardPos[i] = G;
    }

    return true;
}

bool Game::Start()
{
    //initialize the game. Return false to main if any failure occurs.
    if(!init())
    {
        return false;
    }

    // Create the window of the application
    VideoMode desktop = VideoMode::GetDesktopMode();
    App.Create(VideoMode(screenWidth, screenHeight, desktop.BitsPerPixel), "Baghchal", Style::Close);
    App.SetFramerateLimit(40);//limits the framerate. makes the program more efficient.

    //sets the icon in the titlebar
    App.SetIcon(sprites->img.iconimg.GetWidth(), sprites->img.iconimg.GetHeight(), sprites->img.iconimg.GetPixelsPtr());

    /***********************************************************************
                            Game loop starts
    ***********************************************************************/

    while (App.IsOpened())
    {
        // Handle events
        Event Event;

        while (App.GetEvent(Event))
        {
            // Window closed : exit
            if ((Event.Type == Event::Closed))
            {
                App.Close();
                break;
            }

            if ((Event.Type == Event::KeyPressed) && (Event.Key.Code == Key::Z))
            {
                if (mainMenu.mState != NORMAL)
                {
                    mainMenu.mState = NORMAL;
                    mainMenu.nState = NBASE;
                    mainMenu.cState = CBASE;
                    mainMenu.lState = LBASE;
                    flags.mainMenuOn = true;

                    flags.turn = Goat;
                    flags.keyPressed = false;
                    flags.highlightIsDrawn = false;
                    flags.drawLastMove = false;
                    flags.selectPressed = false;
                    flags.isPosRepeated = false;
                    flags.drawRepeatText = false;
                    flags.drawInvalidMove = false;
                    flags.aiThinking = false;
                    flags.isPlaying = true;
                    flags.goatAIActive = false;
                    flags.tigerAIActive = false;
                    flags.timeSet = false;
                    resetDepth = false;
                    flags.goatsToBePlaced = 20;
                    flags.deadGoats = 0;
                    flags.selectorPoint = 13;
                    flags.searchDepth = 4;

                    tigerPlayer->SetTigerPos();
                    ai->initAI();
                    ai->firstMove = true;

                    sprites->Selector.SetPosition(board.point[flags.selectorPoint].GetX() - selectorWidth/2, board.point[flags.selectorPoint].GetY() - selectorHeight/2);

                    board.Reset();
                    for (int i = 0; i < 26; i++)
                    {
                        sprites->point[i].isDrawn = false;
                    }
                }

//                else
//                {
//                    App.Close();
//                    break;
//                }

                break;
            }
        }

        if (!flags.mainMenuOn)
        {
            if (flags.isPlaying)
            {
                // Update the Timer
                input->TimerUpdate();

                //get and process input
                input->GetInput(App, Event);

                if (mainMenu.nState == HUMAN)
                {
                    Timer();
                }
            }

            // Clear the window
            App.Clear();

            DrawStuff();

            // Display the end text
            if (!flags.isPlaying)
            {
                texts->DisplayEndText(App);
            }

            //invoke the MakeMove function of AI Player.
            if ((flags.isPlaying) && ((flags.tigerAIActive && flags.turn == Tiger) || (flags.goatAIActive && flags.turn == Goat)))
            {
                //in order to make sure that the sprite is drawn before the ai starts thinking
                if (!flags.stateChanged && !firstRun)
                {
                    AIMove();
                    if (flags.turn == Tiger)
                        input->mousePressed = false;
                }
                else
                {
                    firstRun = false;
                    flags.stateChanged = false;
                    flags.drawThinking = true;
                }
            }
        }

        //for mainmenu
        else
        {
            //logic for sound
            if (sound.hover == -1)
            {
                flags.prevState = -1;
            }

            else if (flags.prevState != sound.hover)
            {
                input->soundPlayed = false;
                flags.prevState = sound.hover;
            }
            input->MainMenuInput(App, Event);
            sprites->DrawMainMenuSprite(App);
        }
        //  Display things on screen
        App.Display();
    }//end of while app is opened
    return true;
}

/***********************************************************************
                        Game loop ends
***********************************************************************/

void Game::DrawStuff()
{
    //draw the background, board and selector
    sprites->DrawPermanentSprites(App);

    //Draws the highlight, lastmove sprites when needed.
    sprites->DrawLastMove(App);

    //Draws the selector
    sprites->DrawSelector(App);

    //draw the highlight when needed
    sprites->DrawHighlightSprite(App);

    //Draws the sprite of each point according to its state
    sprites->DrawPointSprites(App);

    //Display the turn, goats remaining and dead goats text
    texts->DisplayTexts(App);

    //Display the time for human vs human mode
    if (mainMenu.nState == HUMAN)
    {
        texts->DispTime(App);
    }
}

void Game::AIMove()
{
    if (flags.searchDepth != 12 && mainMenu.lState == L5)
        SetSearchDepth();

    if (!flags.aiThinking)
    {
        SyncBoards();
        flags.aiThinking = true;
        if (ai->MakeMove())
        {
            flags.drawThinking = false;
            sound.PlaySound();
            input->mousePressed = false;
        }
    }
}

void Game::SyncBoards()
{
    for (int i = 1; i < 26; i++)
    {
        ai->board->point[i].SetState(board.point[i].GetState());
    }

    for (int j = 0; j < 4; j++)
    {
        ai->aiTigerPos[j] = tigerPlayer->tigerPos[j];
    }

    ai->aiDeadGoats = flags.deadGoats;
    ai->aiGoatsToBePlaced = flags.goatsToBePlaced;
    ai->aiTurn = flags.turn;

    ai->cornersOccupied = FindOccupiedCorners();
}

int Game::FindOccupiedCorners()
{
    int cornersOccupied = 0;
    for (int j = 0; j < 4; j++)
    {
        if (board.point[corner[j]].GetState() == T)
        {
            cornersOccupied++;
        }
    }
    return cornersOccupied;
}

void Game::SetSearchDepth()
{
    //this makes the ai play faster during the initial stages of the game, and stronger in the later stage.
    if ((flags.searchDepth >= 8) && !resetDepth)
    {
        if (flags.goatsToBePlaced > 12)
        {
            flags.searchDepth = 8;
        }

        else
        {
            flags.searchDepth = 10;
            resetDepth = true;
        }
    }

    else if (flags.goatsToBePlaced == 0 && flags.searchDepth == 10)
    {
        flags.searchDepth = 12;
    }
}

void Game::Timer()
{
    if (mainMenu.nState == HUMAN)
    {
        if (!flags.timeSet)
        {
            TigerTimer.Reset();
            GoatTimer.Reset();
            flags.ts = 0;
            flags.gs = 0;
            flags.tm = totalTime;
            flags.gm = totalTime;
            flags.tigerTime = 0;
            flags.goatTime = 0;

            flags.timeSet = true;
        }

        if (flags.turn == Tiger)
        {
            flags.gs = flags.goatTime;
            GoatTimer.Reset();
            flags.tigerTime = flags.ts - TigerTimer.GetElapsedTime();

            if (flags.tigerTime < 0)
            {
                flags.ts += 60;
                flags.tm--;

                if (flags.tm < 0)
                {
                    flags.tm = 0;
                    flags.winner = Goat;
                    flags.isPlaying = false;
                }
            }
        }

        else
        {
            flags.ts = flags.tigerTime;
            TigerTimer.Reset();
            flags.goatTime = flags.gs - GoatTimer.GetElapsedTime();

            if (flags.goatTime < 0)
            {
                flags.gs += 60;
                flags.gm--;


                if (flags.gm < 0)
                {
                    flags.gm = 0;
                    flags.winner = Tiger;
                    flags.isPlaying = false;
                }
            }
        }
    }
}
