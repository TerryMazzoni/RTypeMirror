/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** EntitiesManager
*/

#pragma once

#include <vector>
#include <optional>
#include <map>
#include <string>
#include "Enum.hpp"
#include "Component.hpp"
#include "Entity.hpp"

namespace ECS
{
    class EntitiesManager
    {
    public:
        EntitiesManager();
        ~EntitiesManager();
        std::vector<Entity> getEntities();
        int addEntities(std::vector<Entity> entitiesToAdd);
        int removeEntities(std::vector<Entity> entitiesToRemove);
        int clearEntities();
        int updateEntities(std::any value, ComponentType compoType, std::vector<Entity> entitiesToUpdate);

    protected:
    private:
        void resizeMapComponent();
        void addComponentsEntity(Entity entity);

        std::vector<Entity> _listEntities;
        std::map<ComponentType, std::vector<std::optional<std::shared_ptr<ECS::IComponent>>>> _mapComponent;
        int _sizeListComponents;
    };
} // namespace ECS
