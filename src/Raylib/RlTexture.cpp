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

    void RlTexture::drawEx(Vector2 position, float rotation, float scale, RlColor color)
    {
        DrawTextureEx(_texture, position, rotation, scale, color.getColor());
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

    void RlTexture::setTexture(std::string path)
    {
        _texture = LoadTexture(path.c_str());
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
