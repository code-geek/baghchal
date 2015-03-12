#ifndef SOUND_H
#define SOUND_H

#include "headers.h"

class SoundClass
{
private:
    SoundBuffer Button;
    Sound sound;
public:
    bool LoadSound();
    void PlaySound();

    int hover;//so as not to play the sound again when the hovered element is the same.
};

#endif
