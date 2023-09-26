/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Text
*/

#pragma once

#include "IComponent.hpp"
#include "RlText.hpp"

namespace ECS {
    template <typename T>
    class Text : public IComponent {
        public:
            Text();
            ~Text();

            int setValue(T value);
            std::string getValue() const;

        protected:
        private:
            std::string _text;
    };
} // namespace ECS
