#include "Sound.h"
#include "sounds\wood.h"

bool SoundClass::LoadSound()
{
    if (!Button.LoadFromMemory(wood_wav, wood_wav_size))
    {
        return false;
    }
    return true;
}

void SoundClass::PlaySound()
{
    sound.SetBuffer(Button);
    sound.Play();

    // Loop while the sound is playing
    while (sound.GetStatus() == Sound::Playing)
    {}
}
