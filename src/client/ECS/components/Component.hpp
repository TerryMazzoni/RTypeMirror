/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Component
*/

#pragma once

#include "IComponent.hpp"

namespace ECS {

    class Component : public IComponent {
        public:
            Component() = default;
            ~Component() = default;
            /**
             * @brief Get the type of the component
             *
             * @return ComponentType
             */
            ComponentType getType() const;
            /**
             * @brief Set the type of the component
             *
             * @param ComponentType
             */
            void setType(ComponentType type);

        private:
            ComponentType _type;
    };
} // namespace ECS
