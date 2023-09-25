/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Texture
*/

#include "Texture.hpp"

namespace ECS {
    template <typename T>
    Texture<T>::Texture() {
        _texture = NULL
    }

    template <typename T>
    Texture<T>::~Texture() {
    }

    template <typename T>
    int Texture<T>::setValue(T value) {
        _texture = value;
        return 0;
    }

    template <typename T>
    Raylib::RlTexture *Texture<T>::getValue() const {
        return _texture;
    }
} // namespace ECS
