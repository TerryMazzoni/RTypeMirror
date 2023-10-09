/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** ChangeTexture
*/

#include "Position.hpp"
#include "ChangeTexture.hpp"

namespace ECS
{
    std::vector<Action> ChangeTexture::execute()
    {
        std::vector<Action> actions = {};
        std::vector<Entity> entities = {};

        if (_isActivated && _entity.has_value())
        {
            entities.push_back(_entity.value());
            actions.push_back(std::make_tuple(entities, ActionType::ChangeTexture, nullptr));
        }
        return actions;
    }
}
