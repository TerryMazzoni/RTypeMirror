/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlWeapon
*/

#pragma once

#include "RlSprite.hpp"
#include "Weapon.hpp"

namespace Raylib {
    class RlWeapon : public Weapon {
        public:
            RlWeapon(const std::string path);
            ~RlWeapon() = default;
            /**
             * @brief Set the Sprite object
             * 
             * @param sprite 
             */
            void setSprite(std::shared_ptr<ECS::Sprite> sprite);
            /**
             * @brief Get the Sprite object
             * 
             * @return std::shared_ptr<ECS::Sprite> 
             */
            std::shared_ptr<ECS::Sprite> getSprite();

        private:
            RlSprite _sprite;
    };
}
