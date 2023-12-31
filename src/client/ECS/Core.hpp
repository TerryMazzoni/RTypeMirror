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
             * @brief Init the window
             *
             */
            void initWindow();
            /**
             * @brief Run the client loop
             *
             * @param std::shared_ptr<Client::UDPClient>
             * @return int
             */
            int run(std::shared_ptr<Client::UDPClient>);
            /**
             * @brief Execute the Server Actions object
             *
             * @param Communication::ShipsPosition
             * @return int
             */
            int executeServerActions(std::vector<Communication::ShipsPosition>);
            /**
             * @brief Execute the Server Actions object
             *
             * @param Communication::MissilesPosition
             * @return int
             */
            int executeServerActions(std::vector<Communication::MissilesPosition>);

        private:
            std::vector<EventInput> transformInputsForClient(std::set<Input> inputs);
            void _createEntities();
            void _createBullet(Entity entity);
            void _createShip(Entity entity);
            void setDeltaTime();

            EntitiesManager _entitiesManager;
            EventManager _eventManager;
            SystemManager _systemManager;
            Graphic::Graph _graph;
    };
} // namespace ECS
