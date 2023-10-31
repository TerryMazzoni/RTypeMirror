/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlMusic
*/

#pragma once

#include <string>
#include "Musics.hpp"
extern "C" {
    #include "raylib.h"
}

namespace Raylib
{
    class RlMusic : public ECS::Musics
    {
    public:
        RlMusic() = default;
        RlMusic(const std::string path);
        ~RlMusic();

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
         * @brief Return the current state of the music
         * 
         * @return true 
         * @return false 
         */
        bool isPlaying();
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
        /**
         * @brief Set the is the music loop
         * 
         * @param loop 
         */
        void setLoop(bool loop);

    private:
        Music _music;
    };
}
