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
            /**
             * @brief Run the client loop
             * 
             * @return int 
             */
            int run();

        private:
            void createEntities();
            void createBullet(Entity entity);

            EntitiesManager _entitiesManager;
            EventManager _eventManager;
            SystemManager _systemManager;
            Graph _graph;
    };
} // namespace ECS
