/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Rotation
*/

#include "Rotation.hpp"

namespace ECS
{
    Rotation::Rotation()
    {
        _degree = 0;
    }

    Rotation::Rotation(float value)
    {
        _degree = value;
    }

    Rotation::~Rotation()
    {
    }

    int Rotation::setValue(float value)
    {
        _degree = value;
        return 0;
    }

    float Rotation::getValue() const
    {
        return _degree;
    }
} // namespace ECS
