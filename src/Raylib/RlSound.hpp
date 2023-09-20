/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlSound
*/

#pragma once

#include <string>

#include "raylib.h"

namespace Raylib
{
    class RlSound
    {
    public:
        RlSound(std::string path);
        ~RlSound();

        void unload();
        void play();
        void setVolume(float volume);

    private:
        Sound _sound;
    };
}
