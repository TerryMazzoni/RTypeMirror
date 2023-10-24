/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlSprite
*/

#include <iostream>
#include "RlSprite.hpp"

namespace Raylib {
    RlSprite::RlSprite()
        : _listTextures({}), _currentTexture({0}), _textureWithColor({}), _positions({0, 0}), _color((Color){255, 255, 255, 255}), _scale(1.0), _rotation(0)
    {
    }

    RlSprite::RlSprite(const int x, const int y)
        : _listTextures({}), _currentTexture({0}), _textureWithColor({}), _color((Color){255, 255, 255, 255}), _scale(1.0), _rotation(0)
    {
        _positions = std::make_pair(x, y);
    }

    RlSprite::RlSprite(const std::vector<std::string> pathTextures, std::vector<int> textureIndexes)
        : _textureWithColor({}), _positions({0, 0}), _color((Color){255, 255, 255, 255}), _scale(1.0), _rotation(0)
    {
        for (const auto &texture : pathTextures) {
            _listTextures.push_back(LoadTexture(texture.c_str()));
        }
        _currentTexture = textureIndexes;
    }

    void RlSprite::setPosition(const int x, const int y)
    {
        _positions = std::make_pair(x, y);
    }

    void RlSprite::setPosition(std::pair<int, int> positions)
    {
        _positions = positions;
    }

    void RlSprite::setTextures(const std::vector<std::string> pathTextures, std::vector<int> textureIndexes)
    {
        for (const auto &texture : pathTextures) {
            _listTextures.push_back(LoadTexture(texture.c_str()));
        }
        _currentTexture = textureIndexes;
    }

    void RlSprite::setColor(const int r, const int g, const int b, const int a, std::vector<int> textureWithColor)
    {
        _color = (Color){(unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a};
        _textureWithColor = textureWithColor;
    }

    void RlSprite::setScale(const float scale)
    {
        _scale = scale;
    }

    void RlSprite::setRotation(const float rotation)
    {
        _rotation = rotation;
    }

    std::pair<int, int> RlSprite::getPos() const
    {
        return _positions;
    }

    int RlSprite::getPosX() const
    {
        return _positions.first;
    }

    int RlSprite::getPosY() const
    {
        return _positions.second;
    }

    std::vector<std::any> RlSprite::getTexturesToDisplay() const
    {
        std::vector<std::any> texturesToDisplay = {};

        for (auto &index : _currentTexture) {
            texturesToDisplay.push_back(_listTextures[index]);
        }
        return texturesToDisplay;
    }

    int RlSprite::getR() const
    {
        return _color.r;
    }

    int RlSprite::getG() const
    {
        return _color.g;
    }

    int RlSprite::getB() const
    {
        return _color.b;
    }

    int RlSprite::getA() const
    {
        return _color.a;
    }

    float RlSprite::getScale() const
    {
        return _scale;
    }

    float RlSprite::getRotation() const
    {
        return _rotation;
    }

    void RlSprite::move(const std::pair<int, int> velocity)
    {
        _positions.first += velocity.first;
        _positions.second += velocity.second;
    }

    void RlSprite::animateTextures()
    {
        int idx = 0;

        for (auto &indexTexture : _currentTexture) {
            indexTexture = indexTexture + 1 > _listTextures.size() / _currentTexture.size() * (idx + 1) - 1
                               ? _listTextures.size() / _currentTexture.size() * idx
                               : indexTexture + 1;
            idx++;
        }
    }
} // namespace Raylib
