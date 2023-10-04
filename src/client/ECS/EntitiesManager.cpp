/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** EntitiesManager
*/

#include <iostream>
#include "EntitiesManager.hpp"
#include "Position.hpp"

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

    int EntitiesManager::updateEntities(std::vector<Action> actions)
    {
        std::vector<std::optional<std::shared_ptr<ECS::IComponent>>> list;
        int idx = 0;
    
        for (auto &action : actions) {
            switch (std::get<1>(action)) {
                case ActionType::Move:
                    list = _mapComponent[ComponentType::Position];
                    for (auto &entity : std::get<0>(action)) {
                        std::shared_ptr<ECS::IComponent> componentP = entity.getComponent(ComponentType::Position);
                        float x = std::any_cast<ECS::Position>(componentP->getValue()).x;
                        float y = std::any_cast<ECS::Position>(componentP->getValue()).y;
                        std::pair<int, int> mouv = std::any_cast<std::pair<int, int>>(std::get<2>(action));
                        list[entity.id.second].value()->setValue(Position(std::make_pair(x + mouv.first, y + mouv.second)));
                    }
                    break;
                case ActionType::Shoot:
                    break;
                case ActionType::ChangeTexture:
                    list = _mapComponent[ComponentType::Texture];
                    for (auto &entity : std::get<0>(action)) {
                        idx = 0;
                        std::shared_ptr<ECS::IComponent> componentT = entity.getComponent(ComponentType::Texture);
                        ECS::Texture texture = std::any_cast<ECS::Texture>(componentT->getValue());
                        for (auto &text : texture.currentTexture) {
                            text = text + 1 > (texture.textureList.size() % texture.currentTexture.size()) ? (texture.textureList.size() % texture.currentTexture.size()) * idx : text + 1;
                            idx++;
                        }
                        list[entity.id.second].value()->setValue(std::any_cast<std::string>(componentT->getValue()));
                    }
                    break;
                case ActionType::Unknown:
                    break;
                default:
                    break;
            }
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
} // namespace ECS
