/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** ChangeTexture
*/

#include "ChangeTexture.hpp"

namespace ECS {
    ChangeTexture::ChangeTexture()
    {
    }

    std::vector<Action> ChangeTexture::execute()
    {
        std::vector<Action> actions = {};
        std::vector<Entity> entities = {};

        if (_isActivated && _entity.has_value()) {
            entities.push_back(_entity.value());
            actions.push_back(std::make_tuple(entities, ActionType::ChangeTexture, nullptr));
        }
        return actions;
    }
} // namespace ECS
