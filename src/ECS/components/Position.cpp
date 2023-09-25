/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Position
*/

#include "Position.hpp"

namespace ECS {
    template <typename T>
    Position<T>::Position() {
        _x = 0;
        _y = 0;
    }

    template <typename T>
    Position<T>::~Position() {
    }

    template <typename T>
    int Position<T>::setValue(T value) {
        _x = value.first;
        _y = value.second;
        return 0;
    }

    template <typename T>
    std::pair<float, float> Position<T>::getValue() const {
        return std::make_pair(_x, _y);
    }
} // namespace ECS
