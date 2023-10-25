/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** IComponent
*/

#pragma once

#include <vector>
#include <any>
#include <string>
#include "Enum.hpp"

namespace ECS {
    class IComponent {
        public:
            virtual ~IComponent() = default;
            /**
             * @brief Get the type of the component
             *
             * @return ComponentType
             */
            virtual ComponentType getType() const = 0;
            /**
             * @brief Set the type of the component
             *
             * @param ComponentType
             */
            virtual void setType(ComponentType type) = 0;
    };
} // namespace ECS
