/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Text
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

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

#endif /* !TEXT_HPP_ */
