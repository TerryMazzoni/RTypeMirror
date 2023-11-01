/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** UpdatePosGun
*/

#pragma once

#include "ASystem.hpp"

namespace ECS {
    class UpdatePosGun : public ASystem {
        public:
            UpdatePosGun() = default;
            ~UpdatePosGun() = default;
            /**
             * @brief Move the gun position to follow the entity
             * 
             * @return std::vector<Action> 
             */
            std::vector<Action> execute();
    };
}
