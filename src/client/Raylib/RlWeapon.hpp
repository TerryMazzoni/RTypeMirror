/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlWeapon
*/

#pragma once

#include "IComponent.hpp"
#include "Weapon.hpp"

namespace Raylib {
    class RlWeapon : public ECS::Weapon {
        public:
            RlWeapon(const std::string path);
            ~RlWeapon() = default;
            /**
             * @brief Set the Sprite object
             * 
             * @param sprite 
             */
            void setSprite(std::shared_ptr<ECS::IComponent> sprite);
            /**
             * @brief Get the Sprite object
             * 
             * @return std::shared_ptr<ECS::IComponent> 
             */
            std::shared_ptr<ECS::IComponent> getSprite();

        private:
            std::shared_ptr<ECS::IComponent> _sprite;
    };
}
