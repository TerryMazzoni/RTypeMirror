/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** EventManager
*/

#include <iostream>
#include "EventManager.hpp"
#include "Factory.hpp"
#include "Position.hpp"

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
        _myPlayer.id = {_myPlayer.id.first, id};
        ECS::Position pos = std::any_cast<ECS::Position>(_myPlayer.getComponent(ComponentType::Position)->getValue());
        pos.y = pos.y + 200 * (id - 1);
        _myPlayer.getComponent(ComponentType::Position)->setValue(pos);
    }

    int EventManager::executeInputs(std::set<Input> listEvent)
    {
        _actions.clear();
        for (auto &event : listEvent) {
            if (std::get<0>(event) == EventType::Keyboard) {
                switch (std::get<1>(event)) {
                    case (int)EventInput::Key_up:
                        movePlayer((EventInput)std::get<1>(event));
                        break;
                    case (int)EventInput::Key_down:
                        movePlayer((EventInput)std::get<1>(event));
                        break;
                    case (int)EventInput::Key_left:
                        movePlayer((EventInput)std::get<1>(event));
                        break;
                    case (int)EventInput::Key_right:
                        movePlayer((EventInput)std::get<1>(event));
                        break;
                    default:
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
            std::shared_ptr<IComponent> pos = Factory::createComponent(ComponentType::Position, std::to_string(ships.ship[i].position.x) + "," + std::to_string(ships.ship[i].position.y));
            pos->setType(ComponentType::Position);
            try {
                std::cout << "serverAction : " << std::any_cast<ECS::Position>(pos->getValue()).x << ", " << std::any_cast<ECS::Position>(pos->getValue()).y << std::endl;
            } catch(std::exception &e) {
                std::cout << "serverActionError : " << e.what() << std::endl;
            }
            tmp.components.push_back(pos);
            _actions.push_back(std::make_tuple(std::vector<ECS::Entity>{tmp}, ActionType::Move, 0));
        }
        return 0;
    }

    int EventManager::executeServerActions(Communication::MissilesPosition missiles)
    {
        ECS::Entity tmp;
    
        for (int i = 0; i < missiles.nbrItems; i++) {
            tmp = ECS::Entity();
            tmp.id = EntityId(EntityType::Bullet, missiles.missile[i].id);
            tmp.components.push_back(Factory::createComponent(ComponentType::Position, std::to_string(missiles.missile[i].position.x) + "," + std::to_string(missiles.missile[i].position.y)));
            _actions.push_back(std::make_tuple(std::vector<ECS::Entity>{tmp}, ActionType::Shoot, 0));
        }
        return 0;
    }

    void EventManager::movePlayer(EventInput dir)
    {
        switch (dir) {
            case EventInput::Key_up:
                _actions.push_back(std::make_tuple(std::vector<ECS::Entity>{_myPlayer}, ActionType::Move, std::make_pair(0, -10)));
                break;
            case EventInput::Key_down:
                _actions.push_back(std::make_tuple(std::vector<ECS::Entity>{_myPlayer}, ActionType::Move, std::make_pair(0, 10)));
                break;
            case EventInput::Key_left:
                _actions.push_back(std::make_tuple(std::vector<ECS::Entity>{_myPlayer}, ActionType::Move, std::make_pair(-10, 0)));
                break;
            case EventInput::Key_right:
                _actions.push_back(std::make_tuple(std::vector<ECS::Entity>{_myPlayer}, ActionType::Move, std::make_pair(10, 0)));
                break;
            default:
                break;
        }
    }

    std::vector<Action> EventManager::getActions() const
    {
        // std::cout << "getActions: " << &_actions << std::endl;
        // std::cout << "getActions len: " << _actions.size() << std::endl;
        // std::cout << "Get actions :" << std::endl;
        // for (auto &action : _actions) {
        //     std::cout << (int) std::get<1>(action) << std::endl;
        // }
        // std::cout << "----------------------------------------------------------------" << std::endl;
        return _actions;
    }

    void ECS::EventManager::clear()
    {
        _actions.clear();
    }
} // namespace ECS
