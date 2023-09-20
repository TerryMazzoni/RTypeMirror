/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlMusic
*/

#pragma once

#include <string>

#include "raylib.h"

namespace Raylib
{
    class RlMusic
    {
    public:
        RlMusic(std::string path);
        ~RlMusic();

        void unload();
        void play();
        void stop();
        void setVolume(float volume);
        void update();

    private:
        Music _music;
    };
}