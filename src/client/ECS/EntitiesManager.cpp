/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** EntitiesManager
*/

#include <iostream>
#include <map>
#include "EntitiesManager.hpp"
#include "Sprite.hpp"

namespace ECS {
    EntitiesManager::EntitiesManager()
    {
        _listEntities = {};
        _mapComponent[ComponentType::Sprite] = {};
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
        std::vector<std::optional<std::shared_ptr<ECS::IComponent>>> list;
        int idx = 0;

        for (auto &action : actions) {
            // std::cout << "Action " << (int) std::get<1>(action) << std::endl;
            switch (std::get<1>(action)) {
                case ActionType::Move:
                    list = _mapComponent[ComponentType::Sprite];
                    for (auto &entity : std::get<0>(action)) {
                        std::shared_ptr<ECS::Sprite> sprite = std::dynamic_pointer_cast<ECS::Sprite>(entity.getComponent(ComponentType::Sprite));
                        std::pair<int, int> move = std::any_cast<std::pair<int, int>>(std::get<2>(action));
                        sprite->move(move);
                    }
                    break;
                case ActionType::UpdatePosPlayer:
                    list = _mapComponent[ComponentType::Sprite];
                    for (auto &entity : std::get<0>(action)) {
                        std::shared_ptr<ECS::Sprite> sprite = std::dynamic_pointer_cast<ECS::Sprite>(entity.getComponent(ComponentType::Sprite));
<<<<<<< HEAD
                        if (std::get<2>(action).type() == typeid(int)) {
                            std::cout << "      x: " << sprite->getPosX() << std::endl;
                            std::cout << "      y: " << sprite->getPosY() << std::endl;
                            std::cout << "entity.id.second: " << entity.id.second << ", list[entity.id.second].has_value(): " << !list[entity.id.second].has_value() << std::endl;
                            if (list.size() < entity.id.second or !list[entity.id.second].has_value()) {
                                _entitiesToCreate.push_back(std::make_pair(std::get<0>(action), EntityType::Player));
                                // std::cout << "create new entity " << std::endl;
                                // entity.components.push_back(Factory::createComponent(ComponentType::Texture, entityPaths[entity.id.first]));
                                // addEntities({entity});
                                // std::cout << "Entity added" << std::endl;
                            }
                            else {
                                list[entity.id.second] = sprite;
                                _listEntities[entity.id.second]->setComponent(ComponentType::Sprite, sprite);
                            }
                            std::cout << "----------------------------" << std::endl;
=======
                        if (list.size() < entity.id.second or !list[entity.id.second].has_value()) {
                            std::cout << "UpdatePosPlayer create : " << entity.id.second << std::endl;
                            _entitiesToCreate.push_back(std::make_pair(std::get<0>(action), EntityType::Player));
                        }
                        else {
                            std::shared_ptr<ECS::Sprite> pos = std::dynamic_pointer_cast<ECS::Sprite>(_listEntities[entity.id.second]->getComponent(ComponentType::Sprite));
                            pos->setPosition(sprite->getPos());
                            std::cout << "UpdatePosPlayer update : " << entity.id.second << std::endl;
>>>>>>> b7af44bbbf2ccf61efd453689a958a6d79e30e6b
                        }
                    }
                    break;
                case ActionType::UpdatePosEnemy:
                    list = _mapComponent[ComponentType::Sprite];
                    for (auto &entity : std::get<0>(action)) {
                        std::shared_ptr<ECS::Sprite> sprite = std::dynamic_pointer_cast<ECS::Sprite>(entity.getComponent(ComponentType::Sprite));
<<<<<<< HEAD
                        if (std::get<2>(action).type() == typeid(int)) {
                            std::cout << "      x: " << sprite->getPosX() << std::endl;
                            std::cout << "      y: " << sprite->getPosY() << std::endl;
                            std::cout << "entity.id.second: " << entity.id.second << ", list[entity.id.second].has_value(): " << !list[entity.id.second].has_value() << std::endl;
                            if (list.size() < entity.id.second or !list[entity.id.second].has_value()) {
                                _entitiesToCreate.push_back(std::make_pair(std::get<0>(action), EntityType::Player));
                                // std::cout << "create new entity " << std::endl;
                                // entity.components.push_back(Factory::createComponent(ComponentType::Texture, entityPaths[entity.id.first]));
                                // addEntities({entity});
                                // std::cout << "Entity added" << std::endl;
                            }
                            else {
                                list[entity.id.second] = sprite;
                                _listEntities[entity.id.second]->setComponent(ComponentType::Sprite, sprite);
                            }
                            std::cout << "----------------------------" << std::endl;
=======
                        if (list.size() < entity.id.second or !list[entity.id.second].has_value()) {
                            _entitiesToCreate.push_back(std::make_pair(std::get<0>(action), EntityType::Player));
                        }
                        else {
                            list[entity.id.second] = sprite;
                            _listEntities[entity.id.second]->setComponent(ComponentType::Sprite, sprite);
>>>>>>> b7af44bbbf2ccf61efd453689a958a6d79e30e6b
                        }
                    }
                    break;
                case ActionType::Shoot:
                    _entitiesToCreate.push_back(std::make_pair(std::get<0>(action), EntityType::Bullet));
                    break;
                case ActionType::ChangeTexture:
                    list = _mapComponent[ComponentType::Sprite];
                    for (auto &entity : std::get<0>(action)) {
                        std::shared_ptr<ECS::Sprite> sprite = std::dynamic_pointer_cast<ECS::Sprite>(entity.getComponent(ComponentType::Sprite));
                        sprite->animateTextures();
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
                std::shared_ptr<ECS::Sprite> sprite = std::dynamic_pointer_cast<ECS::Sprite>(entity.value().getComponent(ComponentType::Sprite));
<<<<<<< HEAD
=======
                if (sprite == nullptr)
                    continue;
>>>>>>> b7af44bbbf2ccf61efd453689a958a6d79e30e6b
                int x = sprite->getPosX();
                int y = sprite->getPosY();

                if ((x < -100 || y < -100 || x > 2020 || y > 1180) and entity.value().id.first != EntityType::Player) {
                    _entitiesToDelete.push_back(entity.value());
                }
            }
        }
        return _entitiesToDelete;
    }

    void EntitiesManager::clearEntitiesToCreate()
    {
        _entitiesToCreate.clear();
    }
} // namespace ECS
