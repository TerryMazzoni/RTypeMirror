/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Sound
*/

#pragma once

#include "Component.hpp"

namespace ECS {
    class Sounds : public Component {
        public:
            ~Sounds() = default;
            /**
             * @brief Play the sound
             * 
             */
            virtual void play() = 0;
            /**
             * @brief Set the Volume object
             * 
             * @param volume 
             */
            virtual void setVolume(float volume) = 0;
    };
} // namespace ECS
