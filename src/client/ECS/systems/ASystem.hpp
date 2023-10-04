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
            ASystem() = default;
            ~ASystem() = default;

            virtual std::vector<Action> execute() = 0;
            void setActivation(bool state);
            void addEntities(std::vector<Entity> listEntities);
            void removeEntities(std::vector<Entity> listEntities);

        protected:
            bool _isActivated = true;
            std::vector<std::optional<Entity>> _listEntities;
    };
} // namespace ECS
