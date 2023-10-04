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
<<<<<<< HEAD
        _entity = entity;
=======
        for (auto &entity : listEntities) {
            if (entity.id.second > _listEntities.size()) {
                _listEntities.resize(entity.id.second + 1);
            }
            _listEntities[entity.id.second] = entity;
        }
>>>>>>> 0fbc961 (Fix: compil with cmake)
    }

    void ASystem::removeEntity()
    {
<<<<<<< HEAD
        _entity = std::nullopt;
=======
        for (auto &entity : listEntities) {
            _listEntities[entity.id.second] = std::nullopt;
        }
>>>>>>> 0fbc961 (Fix: compil with cmake)
    }

    std::optional<Entity> ASystem::getEntity() const
    {
        return _entity;
    }

} // namespace ECS
