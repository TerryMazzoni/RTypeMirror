/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** ChangeTexture
*/

#pragma once

#include "ASystem.hpp"

namespace ECS {
    class ChangeTexture : public ASystem {
        public:
            ChangeTexture() = default;
            ~ChangeTexture() = default;

            std::vector<Action> execute();
    };
}