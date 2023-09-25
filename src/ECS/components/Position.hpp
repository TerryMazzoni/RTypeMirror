/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Position
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_

#include "IComponent.hpp"

namespace ECS {
    template <typename T>
    class Position : public IComponent {
        public:
            Position();
            ~Position();

            int setValue(T value);
            std::pair<float, float> getValue() const;

        protected:
        private:
            float _x;
            float _y;
    };
} // namespace ECS

#endif /* !POSITION_HPP_ */
