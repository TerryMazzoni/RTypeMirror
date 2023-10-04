/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Core
*/

#pragma once

#include "Enum.hpp"
#include "ECS.hpp"
#include "Raylib.hpp"
#include "Graph.hpp"
// #include "SystemManager.hpp"

namespace ECS {
    class Core {
        public:
            Core();
            ~Core();
            int run();

        private:
            EntitiesManager _entitiesManager;
            EventManager _eventManager;
            Graph _graph;
            // SystemManager _systemManager;
    };
} // namespace ECS
