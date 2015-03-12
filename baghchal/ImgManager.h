#ifndef IMGMANAGER_H
#define IMGMANAGER_H

//#include "headers.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class ImgManager
{
public:
    Image boardimg, backgroundimg, selectorimg, highlightimg, goatimg, tigerimg, lastmoveimg, iconimg;
    Image mmBase, mmGoat, mmTiger, mmHuman, mmExit, mmCredits, mmBack, mmCreditsText;
    Image mmBaseH, mmGoatH, mmTigerH, mmHumanH, mmExitH, mmCreditsH, mmBackH;
    Image l1, l2, l3, l4, l5, l1H, l2H, l3H, l4H, l5H;

    bool LoadImages();
};

#endif
