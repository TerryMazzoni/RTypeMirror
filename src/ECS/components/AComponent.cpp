/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** AComponent
*/

#include "AComponent.hpp"
#include "RlColor.hpp"
#include "RlTexture.hpp"

namespace ECS
{
    ComponentType AComponent::getType() const
    {
        return _type;
    }

    void AComponent::setType(ComponentType type)
    {
        _type = type;
    }
} // namespace ECS
