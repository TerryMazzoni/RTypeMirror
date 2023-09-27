/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Color
*/

#include "Color.hpp"

namespace ECS
{
    Color::Color()
    {
    }

    Color::Color(int r, int g, int b, int a)
    {
        _color = Raylib::RlColor(r, g, b, a);
    }

    Color::Color(Raylib::RlColor value)
    {
        _color = value;
    }

    Color::~Color()
    {
    }

    int Color::setValue(int r, int g, int b, int a)
    {
        _color = Raylib::RlColor(r, g, b, a);
        return 0;
    }

    int Color::setValue(Raylib::RlColor value)
    {
        _color = value;
        return 0;
    }

    Raylib::RlColor Color::getValue() const
    {
        return _color;
    }
} // namespace ECS
