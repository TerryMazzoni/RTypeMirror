/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** ASystem
*/

#include <algorithm>
#include "ASystem.hpp"

namespace ECS {
    void ASystem::setActivation(bool state)
    {
        _isActivated = state;
    }

    void ASystem::setEntity(Entity entity)
    {
        _entity = entity;
        _name = _name + "_" + std::to_string(entity.id.second);
    }

    void ASystem::removeEntity()
    {
        _entity = std::nullopt;
    }

    std::string ASystem::getName() const
    {
        return _name;
    }

} // namespace ECS
