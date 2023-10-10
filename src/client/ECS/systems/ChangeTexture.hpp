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
            ChangeTexture();
            ~ChangeTexture() = default;

            /**
             * @brief Execute the system logic
             * 
             * @return std::vector<Action> 
             */
            std::vector<Action> execute();
    };
}