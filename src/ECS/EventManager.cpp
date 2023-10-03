/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** EventManager
*/

#include <iostream>
#include "EventManager.hpp"

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

    void EventManager::movePlayer(EventInput dir)
    {
        switch (dir) {
            case EventInput::Key_up:
                _actions.push_back(std::make_tuple(_myPlayer, ActionType::Move, std::make_pair(0, -10)));
                break;
            case EventInput::Key_down:
                _actions.push_back(std::make_tuple(_myPlayer, ActionType::Move, std::make_pair(0, 10)));
                break;
            case EventInput::Key_left:
                _actions.push_back(std::make_tuple(_myPlayer, ActionType::Move, std::make_pair(-10, 0)));
                break;
            case EventInput::Key_right:
                _actions.push_back(std::make_tuple(_myPlayer, ActionType::Move, std::make_pair(10, 0)));
                break;
            default:
                break;
        }
    }

    std::vector<Action> EventManager::getActions() const
    {
        return _actions;
    }

} // namespace ECS
