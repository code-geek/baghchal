#include "ActiveZone.h"

void ActiveZone::SetZone(int a, int b)
{
    low_x = a - dx/2;
    low_y = b - dy/2;
    high_x = a + dx/2;
    high_y = b + dy/2;
}

bool ActiveZone::LiesInZone(int a , int b)
{
    if ((a>low_x) && (a<high_x) && (b>low_y) && (b<high_y))
    {
        return true;
    }
    return false;
}
