/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Scale
*/

#include "Scale.hpp"

namespace ECS
{
    Scale::Scale()
    {
        _scale = 1.0;
    }

    Scale::Scale(float value)
    {
        _scale = value;
    }

    Scale::~Scale()
    {
    }

    int Scale::setValue(std::string value)
    {
        _scale = std::stof(value);
        return 0;
    }

    std::any Scale::getValue() const
    {
        return _scale;
    }
} // namespace ECS
