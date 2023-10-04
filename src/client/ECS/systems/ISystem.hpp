/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** ISystem
*/

#pragma once

#include <any>
#include "Enum.hpp"
#include "Entity.hpp"

namespace ECS {
    class ISystem {
        public:
            virtual ~ISystem() = default;

            virtual std::vector<Action> execute() = 0;
            virtual void setActivation(bool state) = 0;
            virtual void setEntity(Entity entity) = 0;
            virtual void removeEntity() = 0;
    };
} // namespace ECS
