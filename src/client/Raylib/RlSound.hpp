/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlSound
*/

#pragma once

#include <string>

extern "C" {
    #include "raylib.h"
}

namespace Raylib
{
    class RlSound
    {
    public:
        RlSound(std::string path);
        ~RlSound();

        /**
         * @brief Unload the sound
         *
         */
        void unload();
        /**
         * @brief Play the sound
         *
         */
        void play();
        /**
         * @brief Set the volume of the sound
         *
         */
        void setVolume(float volume);

    private:
        Sound _sound;
    };
}
