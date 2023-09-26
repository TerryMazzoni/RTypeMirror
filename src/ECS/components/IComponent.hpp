/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** IComponent
*/

#pragma once

#include <vector>
#include "Enum.hpp"

namespace ECS {
    template <typename T>
    class IComponent {
        public:
            virtual ~IComponent() = default;

            virtual int setValue(T value) = 0;
            virtual T getValue() const = 0;
            virtual int AddId(Entity) = 0;
            virtual int RemoveId(Entity) = 0;

        protected:
            std::vector<Entity> _ids;
    };
} // namespace ECS
