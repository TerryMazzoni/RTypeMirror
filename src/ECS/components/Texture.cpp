/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Texture
*/

#include "Texture.hpp"

namespace ECS
{
    Texture::Texture()
    {
    }

    Texture::~Texture()
    {
    }

    int Texture::setValue(Raylib::RlTexture value)
    {
        _texture = value;
        return 0;
    }

    Raylib::RlTexture Texture::getValue() const
    {
        return _texture;
    }
} // namespace ECS
