#include "MainMenu.h"

void MainMenu::Initialize()
{
    mState = NORMAL;
    nState = NBASE;
    cState = CBASE;
    lState = LBASE;

    //normal zones
    //goat
    NormalZone[0].low_x = 216;
    NormalZone[0].high_x = 216+472;
    NormalZone[0].low_y = 215;
    NormalZone[0].high_y = 215+44;

    //tiger
    NormalZone[1].low_x = 212;
    NormalZone[1].high_x = 212+478;
    NormalZone[1].low_y = 285;
    NormalZone[1].high_y = 285+44;

    //human
    NormalZone[2].low_x = 185;
    NormalZone[2].high_x = 185+531;
    NormalZone[2].low_y = 355;
    NormalZone[2].high_y = 355+44;

    //exit
    NormalZone[3].low_x = 14;
    NormalZone[3].high_x = 14+95;
    NormalZone[3].low_y = 439;
    NormalZone[3].high_y = 439+35;

    //credits
    NormalZone[4].low_x = 730;
    NormalZone[4].high_x = 730+176;
    NormalZone[4].low_y = 439;
    NormalZone[4].high_y = 439+36;

    //credits zone
    CreditsZone.low_x = 20;
    CreditsZone.high_x = 20+115;
    CreditsZone.low_y = 439;
    CreditsZone.high_y = 439+35;

    int height = 42;
    int width = 200;
    int vGap = 65-42;//vertical gap
    int startHeight = yFactor * 272;
    int startWidth = xFactor * 535;
    int dHeight = vGap + height;//difference in height

    //level zones
    LevelZone[0].low_x = startWidth;
    LevelZone[0].high_x =  startWidth + width;
    LevelZone[0].low_y = startHeight;
    LevelZone[0].high_y = startHeight + height;

    LevelZone[1].low_x = startWidth;
    LevelZone[1].high_x =  startWidth + width;
    LevelZone[1].low_y = LevelZone[0].low_y + dHeight;
    LevelZone[1].high_y = LevelZone[0].low_y + dHeight + height;

    LevelZone[2].low_x = startWidth;
    LevelZone[2].high_x =  startWidth + width;
    LevelZone[2].low_y = LevelZone[1].low_y + dHeight;
    LevelZone[2].high_y = LevelZone[1].low_y + dHeight + height;

    LevelZone[3].low_x = startWidth;
    LevelZone[3].high_x =  startWidth + width;
    LevelZone[3].low_y = LevelZone[2].low_y + dHeight;
    LevelZone[3].high_y = LevelZone[2].low_y + dHeight + height;

    LevelZone[4].low_x = startWidth;
    LevelZone[4].high_x =  startWidth + width;
    LevelZone[4].low_y = LevelZone[3].low_y + dHeight;
    LevelZone[4].high_y = LevelZone[3].low_y + dHeight + height;
}
