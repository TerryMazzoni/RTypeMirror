/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** UpdatePosGun
*/

#include "UpdatePosGun.hpp"
#include "Weapon.hpp"

namespace ECS {
    std::vector<Action> UpdatePosGun::execute()
    {
        if (_isActivated && _entity.has_value()) {
            std::dynamic_pointer_cast<ECS::Sprite>(std::dynamic_pointer_cast<ECS::Weapon>(_entity.value().getComponent(ComponentType::Weapon))->getSprite())->setPosition(std::dynamic_pointer_cast<ECS::Sprite>(_entity.value().getComponent(ComponentType::Sprite))->getPos());
        }
        return {};
    }
} // namespace ECS
