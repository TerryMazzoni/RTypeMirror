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
                    // TODO setready
                    break;
                }
            }
        }
        return 0;
    }

    int EventManager::executeServerActions(Communication::ShipsPosition ships)
    {
        ECS::Entity tmp;

        for (int i = 0; i < ships.nbrItems; i++) {
            tmp = ECS::Entity();
            if (ships.ship[i].type == ShipType::ENEMY)
                tmp.id = EntityId(EntityType::Enemy, ships.ship[i].id);
            else
                tmp.id = EntityId(EntityType::Player, ships.ship[i].id);
            std::shared_ptr<ECS::Sprite> sprite = std::dynamic_pointer_cast<ECS::Sprite>(ECS::Factory::createComponent(ComponentType::Sprite, PATH_TEXTURES_PLAYER));
            sprite->setPosition(std::make_pair(ships.ship[i].position.x, ships.ship[i].position.y));
            sprite->setType(ComponentType::Sprite);
            tmp.components.push_back(sprite);
            if (ships.ship[i].type == ShipType::ENEMY)
                _actions.push_back(std::make_tuple(std::vector<ECS::Entity>{tmp}, ActionType::UpdatePosEnemy, 0));
            else
                _actions.push_back(std::make_tuple(std::vector<ECS::Entity>{tmp}, ActionType::UpdatePosPlayer, 0));
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
} // namespace ECS
