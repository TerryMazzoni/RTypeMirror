/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlTexture
*/

#include "RlTexture.hpp"

namespace Raylib
{
    void RlTexture::unload()
    {
        UnloadTexture(_texture);
    }

    int RlTexture::getWidth() const
    {
        return (_texture.width);
    }

    int RlTexture::getHeight() const
    {
        return (_texture.height);
    }

    void RlTexture::setTexture(std::string path)
    {
        _texture = LoadTexture(path.c_str());
    }

    Texture2D RlTexture::getTexture() const
    {
        return (_texture);
    }

    RlTexture::RlTexture()
    {
    }

    RlTexture::RlTexture(std::string path)
    {
        _texture = LoadTexture(path.c_str());
    }

    RlTexture::~RlTexture()
    {
    }
}
