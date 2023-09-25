/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Text
*/

#include "Text.hpp"

namespace ECS {
    template <typename T>
    Text<T>::Text() {
        _text = NULL
    }

    template <typename T>
    Text<T>::~Text() {
    }

    template <typename T>
    int Text<T>::setValue(T value) {
        _text = value;
        return 0;
    }

    template <typename T>
    std::string Text<T>::getValue() const {
        return _text;
    }
} // namespace ECS
