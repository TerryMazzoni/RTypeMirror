/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlSound
*/

#include "RlSound.hpp"

namespace Raylib
{
    void RlSound::unload()
    {
        UnloadSound(_sound);
    }

    void RlSound::play()
    {
        PlaySound(_sound);
    }

    void RlSound::setVolume(float volume)
    {
        SetSoundVolume(_sound, volume);
    }

    RlSound::RlSound(std::string path)
    {
        _sound = LoadSound(path.c_str());
    }

    RlSound::~RlSound()
    {
    }
}