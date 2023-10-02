/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Entity
*/

#include "Entity.hpp"

namespace ECS {

    std::shared_ptr<ECS::IComponent> Entity::getComponent(ComponentType type)
    {
        for (auto &component : components) {
            if (component->getType() == type)
                return component;
        }
        return nullptr;
    }
} // namespace ECS
