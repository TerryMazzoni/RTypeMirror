/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** SystemManager
*/

#pragma once

#include <string>
#include <map>
#include <vector>
#include "Enum.hpp"
#include "ISystem.hpp"

namespace ECS {
    class SystemManager {
        public:
            SystemManager();
            ~SystemManager();

            int execute(SceneType scene);

        protected:
        private:
            std::map<SceneType, std::vector<ISystem>> _listSystems;
    };
} // namespace ECS

