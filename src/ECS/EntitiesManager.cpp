/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** EntitiesManager
*/

#include "EntitiesManager.hpp"

namespace ECS {
    EntitiesManager::EntitiesManager()
    {
    }

    EntitiesManager::~EntitiesManager()
    {
    }

    std::vector<EntityId> EntitiesManager::getEntities()
    {
        return _listEntities;
    }

    int EntitiesManager::removeEntities(std::vector<EntityId> entitiesToRemove)
    {
        for (auto &entity : entitiesToRemove) {
            for (auto &list : _mapComponent) {
                list.second[entity.second] = std::any();
            }
        }
    }

    int EntitiesManager::clearEntities()
    {
        for (auto &list : _mapComponent) {
            list.second.clear();
            list.second.assign(5, std::any());
        }
    }

    int EntitiesManager::updateEntities(std::string value, ComponentType compoType, std::vector<EntityId> entitiesToUpdate)
    {
        std::vector<std::any> &list = _mapComponent[compoType];

        for (auto &entity : entitiesToUpdate) {
            (Component)list[entity.second].setValue(value);
        }
    }
}
