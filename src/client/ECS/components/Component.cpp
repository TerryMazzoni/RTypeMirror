/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** AComponent
*/

#include "Component.hpp"
#include "Sprite.hpp"

namespace ECS {
    ComponentType Component::getType() const
    {
        return _type;
    }

    void Component::setType(ComponentType type)
    {
        _type = type;
    }
} // namespace ECS
