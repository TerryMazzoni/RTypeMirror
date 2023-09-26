/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Core
*/

#pragma once

#include "Enum.hpp"
#include "EntitiesManager.hpp"
#include "EventManager.hpp"
#include "Graph.hpp"
#include "SystemManager.hpp"

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
            SystemManager _systemManager;
    };
} // namespace ECS
