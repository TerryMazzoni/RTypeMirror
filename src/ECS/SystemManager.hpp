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

#include "Enum.hpp"

namespace ECS {
    class SystemManager {
        public:
            SystemManager();
            ~SystemManager();

            int execute(SceneType scene);

        protected:
        private:
            std::map<SceneType, std::vector<void *>> _listSystems; // replace void * with class system
    };
} // namespace ECS
