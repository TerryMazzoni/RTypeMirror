/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Scale
*/

#include "Scale.hpp"

namespace ECS {
    template <typename T>
    Scale<T>::Scale() {
        _scale = 1.0;
    }

    template <typename T>
    Scale<T>::~Scale() {
    }

    template <typename T>
    int Scale<T>::setValue(T value) {
        _scale = value;
        return 0;
    }

    template <typename T>
    float Scale<T>::getValue() const {
        return _scale;
    }
} // namespace ECS
