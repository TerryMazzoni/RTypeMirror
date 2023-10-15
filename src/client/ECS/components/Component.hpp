/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Component
*/

#pragma once

#include "IComponent.hpp"

namespace ECS {

    template <typename T>
    class Component : public IComponent {
        public:
            Component(std::any value);
            Component() = default;
            ~Component() = default;
            /**
             * @brief Set the value of the component
             *
             * @param std::any
             * @return int
             */
            int setValue(std::any value);
            /**
             * @brief Get the value of the component
             *
             * @return std::any
             */
            std::any getValue() const;
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
            T _value;
            ComponentType _type;
    };
} // namespace ECS
