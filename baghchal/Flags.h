#ifndef FLAGS_H
#define FLAGS_H

#include "headers.h"

struct Flags
{
    bool isPlaying; //To check if the game if over.
    bool keyPressed; //Combined with TimerUpdate(), it is used to keep the speed of the GetInput() function manageably low.
    bool selectPressed;//to check whether the select button has been pressed once or twice, and process accordingly.
    bool highlightIsDrawn;//to check whether the highlight sprite is drawn
    bool drawLastMove;//to send a message to sprites class to draw the last move sprites
    bool isPosRepeated;//required for the non repetition rule
    bool drawRepeatText;//non repetition rule message
    bool drawInvalidMove;//draws the invalid move text
    bool tigerAIActive;//activate the tiger ai
    bool goatAIActive;//activate the goat ai
    bool aiThinking;//so that makemove function is not called while the ai is thinking
    bool mainMenuOn;//turns the main menu on and off, also used to transition from menu to board and vice versa
    bool posRepeatRuleActive;//tells whether this rule is active or not
    bool stateChanged;//used to draw the sprite before ai thinks
    bool drawThinking;//used to draw the ai thinking message (not implemented)
    bool timeSet;

    int selectorPoint; //the point at which the selector is currently located.
    int highlightPoint; //the point at which the highlight has been drawn.
    int fromPoint;//for drawing the lastmove sprite
    int toPoint;//for drawing the lastmove sprite
    int goatsToBePlaced;//number of goats remaining to be placeds
    int deadGoats;//number of dead goats
    int gsCounter;//gamestate counter
    int searchDepth;//starts from 0 goes upto searchDepth
    int prevState;//for sound
    float tigerTime;
    float goatTime;
    int tm;
    int gm;
    int ts;
    int gs;

    Player turn;//checks the turn
    Player winner;//To store the winner in wincheck function, and display it after isplaying is false
};

#endif
