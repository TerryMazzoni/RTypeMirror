/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlWeapon
*/

#include "RlWeapon.hpp"

namespace Raylib {
    RlWeapon::RlWeapon(const std::string path)
    {
        _sprite = std::make_shared<RlSprite>(path);
    }

    RlWeapon::~RlWeapon()
    {
    }

    void RlWeapon::setSprite(std::shared_ptr<ECS::Sprite> sprite)
    {
        _sprite = sprite;
    }

    std::shared_ptr<RlSprite> RlWeapon::getSprite()
    {
        return _sprite;
    }
}
