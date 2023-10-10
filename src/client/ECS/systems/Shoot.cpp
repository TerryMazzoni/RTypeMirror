/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Shoot
*/

#include <iostream>
#include "Shoot.hpp"

namespace ECS {

    Shoot::Shoot()
    {
        _count = 0;
    }

    std::vector<Action> Shoot::execute()
    {
        if (_isActivated && _entity.has_value() && _count == 3) {
            _count = 0;
            std::vector<Entity> entities = {_entity.value()};
            return {std::make_tuple(entities, ActionType::Shoot, 0)};
        }
        _count++;
        return {};
    }
} // namespace ECS
