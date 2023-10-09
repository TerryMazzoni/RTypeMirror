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
    }

    void ASystem::removeEntity()
    {
        _entity = std::nullopt;
    }

    std::optional<Entity> ASystem::getEntity() const
    {
        return _entity;
    }

} // namespace ECS
