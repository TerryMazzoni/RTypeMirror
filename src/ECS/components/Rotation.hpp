/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Rotation
*/

#ifndef ROTATION_HPP_
#define ROTATION_HPP_

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

#endif /* !ROTATION_HPP_ */
