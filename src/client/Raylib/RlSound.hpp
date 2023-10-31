/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlSound
*/

#pragma once

#include <string>
#include "Sounds.hpp"
extern "C" {
    #include "raylib.h"
}

namespace Raylib
{
    class RlSound : public ECS::Sounds
    {
    public:
        RlSound(std::string path);
        ~RlSound();

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
