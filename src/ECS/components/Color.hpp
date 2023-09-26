/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Color
*/

#pragma once

#include "IComponent.hpp"
#include "RlColor.hpp"

namespace ECS {
    template <typename T>
    class Color : public IComponent {
        public:
            Color();
            ~Color();

            int setValue(T value);
            Raylib::RlColor getValue() const;

        protected:
        private:
            Raylib::RlColor _color;
    };
} // namespace ECS
