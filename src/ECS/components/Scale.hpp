/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Scale
*/

#pragma once

#include "IComponent.hpp"

namespace ECS {
    template <typename T>
    class Scale : public IComponent {
        public:
            Scale();
            ~Scale();

            int setValue(T value);
            float getValue() const;

        protected:
        private:
            float _scale;
    };
} // namespace ECS
