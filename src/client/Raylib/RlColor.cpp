/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlColor
*/

#include "RlColor.hpp"

namespace Raylib
{
    void RlColor::setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    {
        _color = Color{r, g, b, a};
    }

    Color RlColor::getColor()
    {
        return _color;
    }

    unsigned char RlColor::getR() const
    {
        return _color.r;
    }

    unsigned char RlColor::getG() const
    {
        return _color.g;
    }

    unsigned char RlColor::getB() const
    {
        return _color.b;
    }

    RlColor::RlColor()
    {
        _color = Color{0, 0, 0, 255};
    }

    RlColor::RlColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    {
        _color = Color{r, g, b, a};
    }

    RlColor::~RlColor()
    {
    }
}
