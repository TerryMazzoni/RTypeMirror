/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** ASystem
*/

#pragma once

#include <vector>
#include "ISystem.hpp"

namespace ECS {
    class ASystem : public ISystem {
        public:
            virtual std::vector<Action> execute() = 0;
            int setActivation(bool state);
            void addEntities(std::vector<Entity> listEntities);
            void removeEntities(std::vector<Entity> listEntities);

        protected:
            bool _isActivated = true;
            std::vector<Entity> _listEntities;
    };
} // namespace ECS
