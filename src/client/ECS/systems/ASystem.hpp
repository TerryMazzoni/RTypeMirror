/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** ASystem
*/

#pragma once

#include <vector>
#include <optional>
#include "ISystem.hpp"

namespace ECS {
    class ASystem : public ISystem {
        public:
            ~ASystem() = default;

            virtual std::vector<Action> execute() = 0;
            void setActivation(bool state);
            void setEntity(Entity entity);
            void removeEntity();

        protected:
            bool _isActivated = true;
            std::optional<Entity> _entity;
    };
} // namespace ECS
