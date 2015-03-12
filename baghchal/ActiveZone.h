#ifndef ACTIVEZONE_H
#define ACTIVEZONE_H

#include "Headers.h"

class ActiveZone
{
private:
    int low_x, low_y, high_x, high_y;

public:
    void SetZone(int a, int b);
    bool LiesInZone(int a, int b);

    friend class MainMenu;
};

#endif
