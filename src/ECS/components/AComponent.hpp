/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** AComponent
*/

#pragma once

#include "IComponent.hpp"

namespace ECS {
    template <typename T>
    class AComponent : public IComponent {
        public:
            virtual int setValue(T value) = 0;
            virtual T getValue() const = 0;
            int AddId(Entity);
            int RemoveId(Entity);

        protected:
        private:
    };
} // namespace ECS
