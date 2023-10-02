/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** EntitiesManager
*/

#include <iostream>
#include "EntitiesManager.hpp"

namespace ECS {
    EntitiesManager::EntitiesManager()
    {
        _listEntities = {};
        _mapComponent[ComponentType::Color] = {};
        _mapComponent[ComponentType::Position] = {};
        _mapComponent[ComponentType::Rotation] = {};
        _mapComponent[ComponentType::Scale] = {};
        _mapComponent[ComponentType::Text] = {};
        _mapComponent[ComponentType::Texture] = {};
        _sizeListComponents = 5;
        resizeMapComponent();
    }

    EntitiesManager::~EntitiesManager()
    {
    }

    std::vector<Entity> EntitiesManager::getEntities()
    {
        return _listEntities;
    }

    int EntitiesManager::addEntities(std::vector<Entity> entitiesToAdd)
    {
        for (auto &entityToAdd : entitiesToAdd) {
            if (entityToAdd.id.second >= _sizeListComponents) {
                _sizeListComponents = entityToAdd.id.second;
                resizeMapComponent();
            }
            _listEntities.push_back(entityToAdd);
            addComponentsEntity(entityToAdd);
        }
        return 0;   
    }

    int EntitiesManager::removeEntities(std::vector<Entity> entitiesToRemove)
    {
        for (auto &entity : entitiesToRemove) {
            for (auto &list : _mapComponent) {
                list.second[entity.id.second] = std::nullopt;
            }
        }
        return 0;
    }

    int EntitiesManager::clearEntities()
    {
        for (auto &list : _mapComponent) {
            list.second.clear();
            list.second.assign(5, std::nullopt);
        }
        return 0;
    }

    int EntitiesManager::updateEntities(std::any value, ComponentType compoType, std::vector<Entity> entitiesToUpdate)
    {
        std::vector<std::optional<std::shared_ptr<ECS::IComponent>>> &list = _mapComponent[compoType];

        for (auto &entity : entitiesToUpdate) {
            list[entity.id.second].value()->setValue(value);
        }
        return 0;
    }

    void EntitiesManager::resizeMapComponent()
    {
        for (auto &list : _mapComponent) {
            list.second.resize(_sizeListComponents);
        }
    }

    void EntitiesManager::addComponentsEntity(Entity entity)
    {
        for (auto &component : entity.components) {
            _mapComponent[component->getType()][entity.id.second] = component;
        }
    }
}
