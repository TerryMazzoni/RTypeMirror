/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Entity
*/

#pragma once

#include <vector>
#include <memory>
#include <any>

#include "IComponent.hpp"

#define Action std::tuple<std::vector<ECS::Entity>, ActionType, std::any>

namespace ECS {
    struct Entity {
            EntityId id;
            std::vector<std::shared_ptr<ECS::IComponent>> components;

            /**
             * @brief Get a shared pointer to the Component object
             * 
             * @param ComponentType
             * @return std::shared_ptr<ECS::IComponent> 
             */
            std::shared_ptr<ECS::IComponent> getComponent(ComponentType type);
    };
} // namespace ECS