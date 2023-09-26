/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** EntitiesManager
*/

#pragma once

#include <vector>
#include "Enum.hpp"

namespace ECS
{
    class EntitiesManager
    {
    public:
        EntitiesManager();
        ~EntitiesManager();
        std::vector<EntityId> getEntities(SceneType scene);
        int addEntities(SceneType scene, std::vector<EntityId> entitiesToAdd);
        int removeEntities(SceneType scene, std::vector<EntityId> entitiesToRemove);
        template <typename T>
        int updateEntities(T value, std::vector<EntityId> entitiesToUpdate);

    protected:
    private:
        std::vector<EntityId> _listEntities;
    };
} // namespace ECS
