/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** EventManager
*/

#include <iostream>
#include "EventManager.hpp"
#include "Factory.hpp"
#include "Sprite.hpp"
#include "Entity.hpp"

namespace ECS {

    EventManager::EventManager()
    {
        _clientReady = false;
    }

    EventManager::~EventManager()
    {
    }

    void EventManager::setMyPlayer(Entity my)
    {
        _myPlayer = my;
    }

    void EventManager::updateMyPlayer(int id)
    {
        Entity myPlayer = Entity();
        myPlayer.id = {_myPlayer.id.first, id};
        std::shared_ptr<ECS::Sprite> sprite = std::dynamic_pointer_cast<ECS::Sprite>(ECS::Factory::createComponent(ComponentType::Sprite, PATH_TEXTURES_PLAYER));
        sprite->setPosition({0, 200 * (id + 1)});
    }

    int EventManager::executeInputs(std::set<Input> listEvent)
    {
        _actions.clear();
        for (auto &event : listEvent) {
            if (std::get<0>(event) == EventType::Keyboard) {
                if (std::get<1>(event) == (int)EventInput::Space) {
                    _clientReady = true;
                    break;
                }
            }
        }
        return 0;
    }

    int EventManager::executeServerActions(Communication::ShipsPosition ships)
    {
        ECS::Entity tmp;
        std::string path;

        for (int i = 0; i < ships.nbrItems; i++) {
            tmp = ECS::Entity();
            switch (ships.ship[i].type) {
                case ShipType::ENEMY1:
                    tmp.id = EntityId(EntityType::Enemy1, ships.ship[i].id);
                    path = PATH_TEXTURES_ENEMY1;
                    break;
                case ShipType::ENEMY2:
                    tmp.id = EntityId(EntityType::Enemy2, ships.ship[i].id);
                    path = PATH_TEXTURES_ENEMY2;
                    break;
                case ShipType::BOSS1:
                    tmp.id = EntityId(EntityType::Boss1, ships.ship[i].id);
                    path = PATH_TEXTURES_BOSS1;
                    break;
                case ShipType::PLAYER:
                    tmp.id = EntityId(EntityType::Player, ships.ship[i].id);
                    path = PATH_TEXTURES_PLAYER;
                    break;
                default:
                    break;
            }
            std::shared_ptr<ECS::Sprite> sprite = std::dynamic_pointer_cast<ECS::Sprite>(ECS::Factory::createComponent(ComponentType::Sprite, path));
            sprite->setPosition(std::make_pair(ships.ship[i].position.x, ships.ship[i].position.y));
            sprite->setType(ComponentType::Sprite);
            sprite->setScale(ships.ship[i].scale);
            tmp.components.push_back(sprite);
            if (ships.ship[i].type == ShipType::PLAYER)
                _actions.push_back(std::make_tuple(std::vector<ECS::Entity>{tmp}, ActionType::UpdatePosPlayer, 0));
            else
                _actions.push_back(std::make_tuple(std::vector<ECS::Entity>{tmp}, ActionType::UpdatePosEnemy, 0));
        }
        return 0;
    }

    int EventManager::executeServerActions(Communication::MissilesPosition missiles)
    {
        ECS::Entity tmp;

        for (int i = 0; i < missiles.nbrItems; i++) {
            tmp = ECS::Entity();
            tmp.id = EntityId(EntityType::Bullet, missiles.missile[i].id);
            std::shared_ptr<ECS::Sprite> sprite = std::dynamic_pointer_cast<ECS::Sprite>(ECS::Factory::createComponent(ComponentType::Sprite, "assets/bullet/ammu1.png"));
            sprite->setPosition(std::make_pair(missiles.missile[i].position.x, missiles.missile[i].position.y));
            sprite->setType(ComponentType::Sprite);
            tmp.components.push_back(sprite);
            _actions.push_back(std::make_tuple(std::vector<ECS::Entity>{tmp}, ActionType::Shoot, 0));
        }
        return 0;
    }

    std::vector<Action> EventManager::getActions() const
    {
        return _actions;
    }

    void ECS::EventManager::clear()
    {
        _actions.clear();
    }

    bool ECS::EventManager::getClientReady() const
    {
        return _clientReady;
    }
} // namespace ECS
