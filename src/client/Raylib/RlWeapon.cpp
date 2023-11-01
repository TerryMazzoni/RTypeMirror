/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlWeapon
*/

#include "RlWeapon.hpp"
#include "Factory.hpp"

namespace Raylib {
    RlWeapon::RlWeapon(const std::string path)
    {
        _sprite = ECS::Factory::createComponent(ComponentType::Sprite, path);
    }

    void RlWeapon::setSprite(std::shared_ptr<ECS::IComponent> sprite)
    {
        _sprite = sprite;
    }

    std::shared_ptr<ECS::IComponent> RlWeapon::getSprite()
    {
        return _sprite;
    }
}
