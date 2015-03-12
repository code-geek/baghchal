#ifndef TEXT_H
#define TEXT_H

#include "Headers.h"
#include "Flags.h"
#include <sstream>//to convert numbers to string

class Text
{
private:
    Font Cheeseburger;

    Flags * flags;

    String End;
    String DGoats;//dead goats
    String RGoats;//remaining goats to be placed
    String defturn;//define turn
    String PosRepeated;//position repeated
    String InvalidMove;
    String ComputerThinking;
    String Escape;

    //time header
    String TigerTime;
    String GoatTime;

    //actual time
    String TTime;
    String GTime;

    std::string dgoats;
    std::string rgoats;
    std::string tMin;
    std::string gMin;
    std::string tSec;
    std::string gSec;

    void ConvertToString(std::string & strng, int n);

public:
    Text(Flags * f);
    bool LoadFont();

    void SetTextPositions();
    void DisplayTexts(RenderWindow & App);
    void DisplayEndText(RenderWindow & App);
    void DisplayThinkingMessage(RenderWindow & App);
    void DispTime(RenderWindow & App);
};

#endif
