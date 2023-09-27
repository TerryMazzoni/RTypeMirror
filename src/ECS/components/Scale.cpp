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

    int Scale::setValue(float value)
    {
        _scale = value;
        return 0;
    }

    float Scale::getValue() const
    {
        return _scale;
    }
} // namespace ECS
