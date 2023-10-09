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
            SystemManager() = default;
            ~SystemManager() = default;

            /**
             * @brief Execute systems
             * 
             * @return std::vector<Action> 
             */
            std::vector<Action> execute();
            /**
             * @brief Add a system to the system manager
             * 
             * @param std::vector<std::shared_ptr<ISystem>>
             */
            void addSystems(std::vector<std::shared_ptr<ISystem>> listSystems);

        protected:
        private:
            std::vector<std::shared_ptr<ISystem>> _listSystems;
            std::vector<Action> _listActions;
    };
} // namespace ECS
