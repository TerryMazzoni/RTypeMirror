/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** EntitiesManager
*/

#include <iostream>
#include <map>
#include "EntitiesManager.hpp"
#include "Position.hpp"
#include "Texture.hpp"
#include "Factory.hpp"

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
        _listEntities.resize(_sizeListComponents + 1);
    }

    EntitiesManager::~EntitiesManager()
    {
    }

    std::vector<std::optional<Entity>> EntitiesManager::getEntities()
    {
        return _listEntities;
    }

    int EntitiesManager::addEntities(std::vector<Entity> entitiesToAdd)
    {
        for (auto &entityToAdd : entitiesToAdd) {
            if (entityToAdd.id.second >= _sizeListComponents) {
                _sizeListComponents = entityToAdd.id.second;
                resizeMapComponent();
                _listEntities.resize(_sizeListComponents + 1);
            }
            addComponentsEntity(entityToAdd);
            _listEntities[entityToAdd.id.second] = entityToAdd;
        }
        return 0;
    }

    int EntitiesManager::removeEntities(std::vector<Entity> entitiesToRemove)
    {
        for (auto &entity : entitiesToRemove) {
            for (auto &list : _mapComponent) {
                list.second[entity.id.second] = std::nullopt;
            }
            _listEntities[entity.id.second] = std::nullopt;
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

    int EntitiesManager::updateEntities(std::vector<Action> actions)
    {
        static std::map<EntityType, const std::string> entityPaths = {
            {EntityType::Bullet, ""},
            {EntityType::Enemy, "assets/player/Player1.png"},
            {EntityType::Player, "assets/spaceship/sprite_spaceships0.png,assets/spaceship/sprite_spaceships1.png,assets/spaceship/sprite_spaceships2.png,assets/spaceship/sprite_spaceships3.png,assets/capsule/sprite_capsules0.png,assets/capsule/sprite_capsules1.png,assets/capsule/sprite_capsules2.png,assets/capsule/sprite_capsules3.png,0,4"},
        };
        std::vector<std::optional<std::shared_ptr<ECS::IComponent>>> list;
        int idx = 0;

        _entitiesToCreate.clear();
        for (auto &action : actions) {
            // std::cout << "Action " << (int) std::get<1>(action) << std::endl;
            switch (std::get<1>(action)) {
                case ActionType::Move:
                    list = _mapComponent[ComponentType::Position];
                    for (auto &entity : std::get<0>(action)) {
                        std::shared_ptr<ECS::IComponent> componentP = entity.getComponent(ComponentType::Position);
                        // std::cout << std::get<2>(action).type().name() << "==" << typeid(int).name() << std::endl;
                        if (std::get<2>(action).type() == typeid(int)) {
                            // std::cout << "Position component : " << entity.getComponent(ComponentType::Position) << std::endl;
                            // std::cout << "      x: " << std::any_cast<ECS::Position>(componentP->getValue()).x << std::endl;
                            // std::cout << "      y: " << std::any_cast<ECS::Position>(componentP->getValue()).y << std::endl;
                            // std::cout << "entity.id.second: " << entity.id.second << ", list[entity.id.second].has_value(): " << !list[entity.id.second].has_value() << std::endl;
                            if (list.size() < entity.id.second or !list[entity.id.second].has_value()) {
                                entity.components.push_back(Factory::createComponent(ComponentType::Texture, entityPaths[entity.id.first]));
                                addEntities({entity});
                                // std::cout << "Entity added" << std::endl;
                            } else
                                list[entity.id.second] = componentP;
                        } else {
                            // std::cout << entity.getComponent(ComponentType::Position) << ", " << std::any_cast<std::pair<int, int>>(std::get<2>(action)).first << ", "<< std::any_cast<std::pair<int, int>>(std::get<2>(action)).second << std::endl;
                            float x = std::any_cast<ECS::Position>(componentP->getValue()).x;
                            float y = std::any_cast<ECS::Position>(componentP->getValue()).y;
                            std::pair<int, int> mouv = std::any_cast<std::pair<int, int>>(std::get<2>(action));
                            // std::cout << "else: " << entity.id.second << std::endl;
                            list[entity.id.second].value()->setValue(Position(std::make_pair(x + mouv.first, y + mouv.second)));
                        }
                    }
                    break;
                case ActionType::Shoot:
                    _entitiesToCreate.push_back(std::make_pair(std::get<0>(action), EntityType::Bullet));
                    break;
                case ActionType::ChangeTexture:
                    list = _mapComponent[ComponentType::Texture];
                    for (auto &entity : std::get<0>(action)) {
                        idx = 0;
                        std::shared_ptr<ECS::IComponent> componentT = entity.getComponent(ComponentType::Texture);
                        ECS::Texture texture = std::any_cast<ECS::Texture>(componentT->getValue());
                        for (auto &text : texture.currentTexture) {
                            text = text + 1 > texture.textureList.size() / texture.currentTexture.size() * (idx + 1) - 1 ? texture.textureList.size() / texture.currentTexture.size() * idx : text + 1;
                            idx++;
                        }
                        list[entity.id.second].value()->setValue(std::any_cast<ECS::Texture>(texture));
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
            list.second.resize(_sizeListComponents + 1);
        }
    }

    void EntitiesManager::addComponentsEntity(Entity entity)
    {
        for (auto &component : entity.components) {
            _mapComponent[component->getType()][entity.id.second] = component;
        }
    }

    std::vector<std::pair<std::vector<Entity>, EntityType>> EntitiesManager::getEntitiesToCreate()
    {
        return _entitiesToCreate;
    }

    std::vector<Entity> EntitiesManager::getEntitiesToDelete()
    {
        _entitiesToDelete.clear();
        for (auto &entity : _listEntities) {
            if (entity.has_value()) {
                std::shared_ptr<ECS::IComponent> position = entity.value().getComponent(ComponentType::Position);
                float x = std::any_cast<ECS::Position>(position->getValue()).x;
                float y = std::any_cast<ECS::Position>(position->getValue()).y;

                if ((x < -100 || y < -100 || x > 2020 || y > 1180) and entity.value().id.first != EntityType::Player) {
                    _entitiesToDelete.push_back(entity.value());
                }
            }
        }
        return _entitiesToDelete;
    }
} // namespace ECS
