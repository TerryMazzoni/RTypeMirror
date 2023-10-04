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

    void ASystem::addEntities(std::vector<Entity> listEntities)
    {
        for (auto &entity : listEntities) {
            if (entity.id.second > _listEntities.size()) {
                _listEntities.resize(entity.id.second + 1);
            }
            _listEntities[entity.id.second] = entity;
        }
    }

    void ASystem::removeEntities(std::vector<Entity> listEntities)
    {
        for (auto &entity : listEntities) {
            _listEntities[entity.id.second] = std::nullopt;
        }
    }
} // namespace ECS
