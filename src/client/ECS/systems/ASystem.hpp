/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** ASystem
*/

#pragma once

#include <vector>
#include <optional>
#include "ISystem.hpp"

namespace ECS {
    class ASystem : public ISystem {
        public:
            ~ASystem() = default;

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
            void setActivation(bool state);
            /**
             * @brief Set the entity of the system
             * 
             * @param Entity 
             */
            void setEntity(Entity entity);
            /**
             * @brief Remove the entity from the system
             * 
             * @return bool 
             */
            void removeEntity();
            /**
             * @brief Get the entity of the system
             * 
             * @return std::string 
             */
            std::optional<Entity> getEntity() const;

        protected:
            bool _isActivated = true;
            std::optional<Entity> _entity;
    };
} // namespace ECS
