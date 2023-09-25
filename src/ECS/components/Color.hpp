/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Color
*/

#ifndef COLOR_HPP_
#define COLOR_HPP_

#include "IComponent.hpp"
#include "RlColor.hpp"

namespace ECS {
    template <typename T>
    class Color : public IComponent {
        public:
            Color();
            ~Color();

            int setValue(T value);
            Raylib::RlColor *getValue() const;

        protected:
        private:
            Raylib::RlColor *_color;
    };
} // namespace ECS

#endif /* !COLOR_HPP_ */
