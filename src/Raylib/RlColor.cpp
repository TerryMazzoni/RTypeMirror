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
        _color = (Color){r, g, b, a};
    }

    Color RlColor::getColor()
    {
        return _color;
    }

    RlColor::RlColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    {
        _color = (Color){r, g, b, a};
    }

    RlColor::~RlColor()
    {
    }
}
