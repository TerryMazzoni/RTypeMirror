/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Scale
*/

#ifndef SCALE_HPP_
#define SCALE_HPP_

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

#endif /* !SCALE_HPP_ */
