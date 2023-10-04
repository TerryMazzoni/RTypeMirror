/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** ASystem
*/

#include <algorithm>
#include "ASystem.hpp"

namespace ECS {
    int ASystem::setActivation(bool state)
    {
        _isActivated = state;
    }

    void ASystem::addEntities(std::vector<Entity> listEntities)
    {
        _listEntities.insert(_listEntities.end(), listEntities.begin(), listEntities.end());
    }

    void ASystem::removeEntities(std::vector<Entity> listEntities)
    {
        for (auto &entity : listEntities) {
            _listEntities.erase(std::remove(_listEntities.begin(), _listEntities.end(), entity), _listEntities.end());
        }
    }
} // namespace ECS
