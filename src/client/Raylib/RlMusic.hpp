/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlMusic
*/

#pragma once

#include <string>

extern "C" {
    #include "raylib.h"
}

namespace Raylib
{
    class RlMusic
    {
    public:
        RlMusic(std::string path);
        ~RlMusic();

        /**
         * @brief Unload the music
         *
         */
        void unload();
        /**
         * @brief Play the music
         *
         */
        void play();
        /**
         * @brief Stop the music
         *
         */
        void stop();
        /**
         * @brief Set the volume of the music
         *
         */
        void setVolume(float volume);
        /**
         * @brief Update the music
         *
         */
        void update();

    private:
        Music _music;
    };
}
