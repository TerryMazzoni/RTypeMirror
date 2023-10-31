/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Sound
*/

#pragma once

#include <iostream>
#include "Component.hpp"

namespace ECS {
    class Musics : public Component {
        public:
            ~Musics() = default;
            /**
             * @brief Play the music
             *
             */
            virtual void play() = 0;
            /**
             * @brief Stop the music
             *
             */
            virtual void stop() = 0;
            /**
             * @brief Return the current state of the music
             *
             * @return true
             * @return false
             */
            virtual bool isPlaying() = 0;
            /**
             * @brief Set the Volume object
             *
             * @param volume
             */
            virtual void setVolume(float volume) = 0;
            /**
             * @brief Update the music
             *
             */
            virtual void update() = 0;
            /**
             * @brief Set the is the music loop
             * 
             * @param loop 
             */
            virtual void setLoop(bool loop) = 0;
    };
} // namespace ECS