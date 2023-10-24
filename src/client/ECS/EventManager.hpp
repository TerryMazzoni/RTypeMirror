/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** EventManager
*/

#pragma once

#include <string>
#include <vector>
#include <set>
#include <tuple>
#include <any>
#include <optional>
#include <memory>
#include "Enum.hpp"
#include "Entity.hpp"
#include "Communication.hpp"

namespace ECS {
    class EventManager {
        public:
            EventManager();
            ~EventManager();

            /**
             * @brief Set the My Player object
             * 
             * @param Entity
             */
            void setMyPlayer(Entity my);
            /**
             * @brief Execute player inputs
             * 
             * @param std::set<Input>
             * @return int 
             */
            int executeInputs(std::set<Input>);
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
            /**
             * @brief Get the Actions object
             * 
             * @return std::vector<Action> 
             */
            std::vector<Action> getActions() const;
            /**
             * @brief clear the vector
             * 
             */
            void clear();

        private:
            /**
             * @brief Move the player entity
             * 
             * @param EventInput
             */
            void movePlayer(EventInput dir);

            Entity _myPlayer;
            std::vector<Action> _actions;
    };
} // namespace ECS
