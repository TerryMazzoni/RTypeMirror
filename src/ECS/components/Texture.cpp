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

    Texture::Texture(const std::string texture)
    {
        _texture = Raylib::RlTexture(texture);
    }

    Texture::Texture(Raylib::RlTexture value)
    {
        _texture = value;
    }

    Texture::~Texture()
    {
    }

    int Texture::setValue(const std::string texture)
    {
        _texture = Raylib::RlTexture(texture);
        return 0;
    }

    std::any Texture::getValue() const
    {
        return _texture;
    }
} // namespace ECS
