/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** BulletMouvement
*/

#include <utility>
#include "Position.hpp"
#include "BulletMouvement.hpp"

namespace ECS {
    BulletMouvement::BulletMouvement()
    {
    }

    std::vector<Action> BulletMouvement::execute()
    {
        std::vector<Action> actions = {};
        std::vector<Entity> entities = {};
        std::pair<int, int> mouv;

        if (_isActivated && _entity.has_value()) {
            entities.push_back(_entity.value());
            std::shared_ptr<ECS::IComponent> componentP = _entity.value().getComponent(ComponentType::Position);
            actions.push_back(std::make_tuple(entities, ActionType::Move, std::make_pair(15, 0)));
        }
        return actions;
    }
} // namespace ECS
