#include "game.h"

int main()
{
    Game BaghChal;
    if (BaghChal.Start())
    {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
