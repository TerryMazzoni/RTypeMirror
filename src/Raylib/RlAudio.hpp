/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlAudio
*/

#pragma once

#include "raylib.h"

namespace Raylib {
    void initAudioDevice();
    void closeAudioDevice();
    void setMasterVolume(float volume);
}
