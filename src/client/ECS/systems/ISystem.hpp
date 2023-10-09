/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** ISystem
*/

#pragma once

#include <any>
#include "Enum.hpp"
#include "Entity.hpp"

namespace ECS {
    class ISystem {
        public:
            virtual ~ISystem() = default;

            /**
             * @brief Execute the system logic
             * 
             * @return std::vector<Action> 
             */
            virtual std::vector<Action> execute() = 0;
            /**
             * @brief Set the system activation
             * 
             * @param bool
             */
            virtual void setActivation(bool state) = 0;
            /**
             * @brief Set the entity of the system
             * 
             * @param Entity
             */
            virtual void setEntity(Entity entity) = 0;
            /**
             * @brief Remove the entity from the system
             * 
             * @return bool 
             */
            virtual void removeEntity() = 0;
    };
} // namespace ECS
