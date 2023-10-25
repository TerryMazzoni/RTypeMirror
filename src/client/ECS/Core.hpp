/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Core
*/

#pragma once

#include <memory>

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
             * @brief init Core
             * 
             */
            void init(int id);
            /**
             * @brief Run the client loop
             * 
             * @param std::shared_ptr<Client> 
             * @return int 
             */
            int run(std::shared_ptr<Client>);
            /**
             * @brief Execute the Server Actions object
             * 
             * @param Communication::ShipsPosition
             * @return int 
             */
            int executeServerActions(Communication::ShipsPosition);
            /**
             * @brief Execute the Server Actions object
             * 
             * @param Communication::MissilesPosition
             * @return int 
             */
            int executeServerActions(Communication::MissilesPosition);
        private:
            std::vector<EventInput> transformInputsForClient(std::set<Input> inputs);
            void createEntities();
            void createBullet(Entity entity);

            EntitiesManager _entitiesManager;
            EventManager _eventManager;
            SystemManager _systemManager;
            Graph _graph;
            int _id;
    };
} // namespace ECS
