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

    void Entity::setComponent(ComponentType type, std::shared_ptr<ECS::IComponent> value)
    {
        int i = 0;
    
        for (auto component : components) {
            if (component->getType() == type) {
                components[i] = value;
                return;
            }
            i++;
        }
        components.push_back(value);
    }
} // namespace ECS
