/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Weapon
*/

#pragma once

#include <memory>
#include "Component.hpp"
#include "Sprite.hpp"

namespace ECS {
    class Weapon : public Component {
        public:
            ~Weapon() = default;
            /**
             * @brief Set the Sprite object
             * 
             * @param sprite 
             */
            virtual void setSprite(std::shared_ptr<ECS::IComponent> sprite) = 0;
            /**
             * @brief Get the Sprite object
             * 
             * @return std::shared_ptr<Sprite> 
             */
            virtual std::shared_ptr<ECS::IComponent> getSprite() = 0;
    };
}
