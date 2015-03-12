#include "Text.h"
#include "fonts\cheeseburger.h"

Text::Text(Flags * f)
{
    flags = f;
}

bool Text::LoadFont()
{
    if (!Cheeseburger.LoadFromMemory(cheeseburger_ttf, cheeseburger_ttf_size))
        return false;

    return true;
}

void Text::SetTextPositions()
{
    int move = 100;
    // Initialize the end text
    End.SetFont(Cheeseburger);
    //End.SetStyle(1 << 2);//underline
    End.SetSize(60.f/1.5);
    End.SetPosition(5, 0);
    End.SetColor(Color(244, 220, 6));

    //Intilialize the dead goats text
    DGoats.SetSize(30.f/1.5);
    DGoats.SetPosition(5, (boardHeight/2)/1.5 + move);

    //Intilialize the remaining goats text
    RGoats.SetSize(30.f/1.5);
    RGoats.SetPosition(5, (boardHeight/2 - 30)/1.5 + move);

    PosRepeated.SetSize(30.f/1.5);
    PosRepeated.SetPosition(5, (boardHeight/2 + 60)/1.5 + move);
    PosRepeated.SetColor(Color(244, 241, 6));
    PosRepeated.SetText("Repetition is not allowed!");

    InvalidMove.SetSize(30.f/1.5);
    InvalidMove.SetPosition(5, (boardHeight/2 + 60)/1.5 + move);
    InvalidMove.SetColor(Color(244, 241, 6));
    InvalidMove.SetText("Invalid Move!");

    ComputerThinking.SetSize(30.f/1.5);
    ComputerThinking.SetPosition(5, 0);
    ComputerThinking.SetColor(Color(244, 241, 6));
    ComputerThinking.SetText("I am thinking...");

    //Initialize the flags->turn string
    defturn.SetSize(30.f/1.5);
    defturn.SetPosition(5, (boardHeight/2 - 90)/1.5 + move);
    defturn.SetColor(Color(244, 241, 6));

    Escape.SetSize(20.f/1.5);
    Escape.SetPosition(5, 150/1.5);
    Escape.SetText("(Press Z.)");
    Escape.SetColor(Color(244, 241, 6));

    TigerTime.SetPosition(2*boardWidth -100, 5);
    TigerTime.SetColor(Color(244, 220, 6));
    TigerTime.SetText("Tiger:");

    GoatTime.SetPosition(2*boardWidth -100, 400);
    GoatTime.SetColor(Color(244, 220, 6));
    GoatTime.SetText("Goat:");

    TTime.SetPosition(2*boardWidth -100, 35);
    GTime.SetPosition(2*boardWidth -100, 430);
}

void Text::DisplayTexts(RenderWindow & App)
{
    //convert numbers dgoats & rgoats to string
    ConvertToString(dgoats, flags->deadGoats);
    ConvertToString(rgoats, flags->goatsToBePlaced);

    DGoats.SetText("Dead Goats: " + dgoats);
    App.Draw(DGoats);

    RGoats.SetText("Goats to place: " + rgoats);
    App.Draw(RGoats);


    if (flags->drawRepeatText)
    {
        App.Draw(PosRepeated);
    }

    if (flags->drawInvalidMove && !flags->drawRepeatText)
    {
        App.Draw(InvalidMove);
    }

    flags->turn == Tiger? defturn.SetText("Turn: Tiger") : defturn.SetText("Turn: Goat");
    App.Draw(defturn);

    if ((flags->isPlaying && ((flags->turn == Tiger && flags->tigerAIActive == true) || (flags->turn == Goat && flags->goatAIActive == true))))
        App.Draw(ComputerThinking);

}

void Text::DispTime(RenderWindow & App)
{
    ConvertToString(tMin, flags->tm);
    ConvertToString(gMin, flags->gm);
    ConvertToString(tSec, flags->tigerTime);
    ConvertToString(gSec, flags->goatTime);

    App.Draw(TigerTime);
    App.Draw(GoatTime);

    if (flags->tigerTime < 10)
    {
        tSec = "0" + tSec;
    }

    if (flags->tm < 10)
    {
        tMin = "0" + tMin;
    }

    TTime.SetText(tMin + " : " + tSec);
    App.Draw(TTime);

    if (flags->goatTime < 10)
    {
        gSec = "0" + gSec;
    }

    if (flags->gm < 10)
    {
        gMin = "0" + gMin;
    }

    GTime.SetText(gMin + " : " + gSec);
    App.Draw(GTime);
}

void Text::ConvertToString(std::string & strng, int n)
{
    std::ostringstream convert;
    convert << n;
    strng = convert.str();
}

void Text::DisplayEndText(RenderWindow & App)
{
    if (flags->winner == Tiger)
    {
        End.SetText("Tiger Player\nwins!");
    }

    else
    {
        End.SetText("Goat player\nwins!");
    }
    App.Draw(End);
    App.Draw(Escape);
}

void Text::DisplayThinkingMessage(RenderWindow & App)
{
    if (flags->drawThinking)
    {
        App.Draw(ComputerThinking);
    }
}
