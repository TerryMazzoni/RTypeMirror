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

    Color::Color(Raylib::RlColor value)
    {
        _color = value;
    }

    Color::~Color()
    {
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
