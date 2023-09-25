/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Color
*/

#include "Color.hpp"

namespace ECS {
    template <typename T>
    Color<T>::Color() {
        _color = nullptr
    }

    template <typename T>
    Color<T>::~Color() {
    }

    template <typename T>
    int Color<T>::setValue(T value) {
        _color = value;
        return 0;
    }

    template <typename T>
    Raylib::RlColor Color<T>::getValue() const {
        return _color;
    }
} // namespace ECS
