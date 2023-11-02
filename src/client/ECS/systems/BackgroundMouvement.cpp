/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** BackgroundMouvement
*/

#include <utility>
#include <iostream>
#include "Sprite.hpp"
#include "BackgroundMouvement.hpp"

namespace ECS {
    BackgroundMouvement::BackgroundMouvement(int start, int end)
    {
        _start = start;
        _end = end;
    }

    std::vector<Action> BackgroundMouvement::execute()
    {
        std::vector<Action> actions = {};
        std::vector<Entity> entities = {};
        std::pair<int, int> mouv;

        

        if (_isActivated && _entity.has_value()) {
            std::shared_ptr<ECS::Sprite> sprite = std::dynamic_pointer_cast<ECS::Sprite>(_entity.value().getComponent(ComponentType::Sprite));
            std::pair<int, int> pos = sprite.get()->getPos();
            int speed = (int)sprite.get()->getSpeed();
            if (pos.first <= _end)
                sprite.get()->setPosition({_start, 0});
            entities.push_back(_entity.value());
            actions.push_back(std::make_tuple(entities, ActionType::Move, std::make_pair(speed, 0)));
        }
        return actions;
    }
} // namespace ECS
