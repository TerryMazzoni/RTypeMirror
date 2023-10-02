/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Component
*/

#pragma once

#include "IComponent.hpp"

namespace ECS {

    template<typename T>
    class Component : public IComponent {
        public:
            Component(std::any value);
            Component() = default;
            ~Component() = default;
            int setValue(std::any value);
            std::any getValue() const;
            ComponentType getType() const;
            void setType(ComponentType type);

        private:
            T _value;
            ComponentType _type;
    };
}
