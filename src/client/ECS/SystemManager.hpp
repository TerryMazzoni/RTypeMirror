/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** SystemManager
*/

#pragma once

#include <string>
#include <vector>
#include <map>
#include "Enum.hpp"
#include "ISystem.hpp"
#include "Entity.hpp"
#include "Enum.hpp"

namespace ECS {
    class SystemManager {
        public:
            SystemManager();
            ~SystemManager();

            std::vector<Action> execute();
            void addSystems(std::vector<ISystem> listSystems);
            void removeSystems(std::vector<ISystem> listSystems);

        protected:
        private:
            std::vector<ISystem> _listSystems;
            std::vector<Action> _listActions;
    };
} // namespace ECS
