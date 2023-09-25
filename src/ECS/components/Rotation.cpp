/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Rotation
*/

#include "Rotation.hpp"

namespace ECS {
    template <typename T>
    Rotation<T>::Rotation() {
        _x = 0;
        _y = 0;
    }

    template <typename T>
    Rotation<T>::~Rotation() {
    }

    template <typename T>
    int Rotation<T>::setValue(T value) {
        _degree = value;
        return 0;
    }

    template <typename T>
    float Rotation<T>::getValue() const {
        return _degree;
    }
} // namespace ECS
