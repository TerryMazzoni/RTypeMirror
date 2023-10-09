/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Mouvement
*/

#include "Position.hpp"
#include "Mouvement.hpp"

namespace ECS
{

    Mouvement::Mouvement()
    {
        _goRight = true;
    }

    std::vector<Action> Mouvement::execute()
    {
        std::vector<Action> actions = {};
        std::vector<Entity> entities = {};
        std::pair<int, int> mouv;

        if (_isActivated && _entity.has_value())
        {
            entities.push_back(_entity.value());
            std::shared_ptr<ECS::IComponent> componentP = _entity.value().getComponent(ComponentType::Position);
            float x = std::any_cast<Position>(componentP->getValue()).x;
            if (x <= -64 && !_goRight)
            {
                _goRight = true;
            }
            else if (x >= 1984 && _goRight)
            {
                _goRight = false;
            }
            mouv = _goRight ? std::make_pair(10, 0) : std::make_pair(-10, 0);
            actions.push_back(std::make_tuple(entities, ActionType::Move, mouv));
        }
        return actions;
    }
}
