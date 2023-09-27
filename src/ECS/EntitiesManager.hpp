/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** EntitiesManager
*/

#pragma once

#include <vector>
#include <any>
#include <map>
#include <string>
#include "Enum.hpp"

namespace ECS
{
    class EntitiesManager
    {
    public:
        EntitiesManager();
        ~EntitiesManager();
        std::vector<EntityId> getEntities();
        int addEntities(std::vector<EntityId> entitiesToAdd);
        int removeEntities(std::vector<EntityId> entitiesToRemove);
        int clearEntities();
        int updateEntities(std::string value, ComponentType compoType, std::vector<EntityId> entitiesToUpdate);

    protected:
    private:
        std::vector<EntityId> _listEntities;
        std::map<ComponentType, std::vector<std::any>> _mapComponent;
    };
} // namespace ECS
