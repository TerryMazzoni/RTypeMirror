/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** UpdateAudio
*/

#pragma once

#include "ASystem.hpp"

namespace ECS {
    class UpdateMusic : public ASystem {
        public:
            UpdateMusic();
            ~UpdateMusic() = default;

            std::vector<Action> execute();
    };
}
