/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlAudio
*/

#include "RlAudio.hpp"

namespace Raylib {
    void initAudioDevice()
    {
        InitAudioDevice();
    }

    void closeAudioDevice()
    {
        CloseAudioDevice();
    }

    void setMasterVolume(float volume)
    {
        SetMasterVolume(volume);
    }
}
