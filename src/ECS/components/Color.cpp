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

    int Color::setValue(std::string value)
    {
        int r = std::stoi(value.substr(0, value.find(",")));
        int g = std::stoi(value.substr(value.find(",") + 1, value.find(",", value.find(",") + 1)));
        int b = std::stoi(value.substr(value.find(",", value.find(",") + 1) + 1, value.find(",", value.find(",", value.find(",") + 1) + 1)));

        _color = Raylib::RlColor(r, g, b);
        return 0;
    }

    std::any Color::getValue() const
    {
        return _color;
    }
} // namespace ECS
