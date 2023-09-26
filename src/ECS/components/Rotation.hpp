/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Rotation
*/

#pragma once

#include "IComponent.hpp"

namespace ECS {
    template <typename T>
    class Rotation : public IComponent {
        public:
            Rotation();
            ~Rotation();

            int setValue(T value);
            float getValue() const;

        protected:
        private:
            float _degree;
    };
} // namespace ECS
