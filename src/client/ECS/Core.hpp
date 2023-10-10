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
#include "Client.hpp"

namespace ECS {
    class Core {
        public:
            Core();
            ~Core();
            /**
             * @brief Run the client loop
             * 
             * @param std::shared_ptr<Client> 
             * @return int 
             */
            int run(std::shared_ptr<Client>);

        private:
            void createEntities();
            void createBullet(Entity entity);

            EntitiesManager _entitiesManager;
            EventManager _eventManager;
            SystemManager _systemManager;
            Graph _graph;
    };
} // namespace ECS
