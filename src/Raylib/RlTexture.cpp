/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlTexture
*/

#include "RlTexture.hpp"

namespace Raylib
{
    void RlTexture::draw(int x, int y, RlColor color)
    {
        DrawTexture(_texture, x, y, color.getColor());
    }

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

    RlTexture::RlTexture(std::string path)
    {
        _texture = LoadTexture(path.c_str());
    }

    RlTexture::~RlTexture()
    {
    }
}
