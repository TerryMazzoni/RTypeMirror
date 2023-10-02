/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Position
*/

#pragma once

#include <utility>

namespace ECS
{
    struct Position
    {
        Position() : x(0), y(0) {};
        Position(float x, float y) : x(x), y(y) {};
        Position(std::pair<float, float> pos) : x(pos.first), y(pos.second) {};

        float x;
        float y;
    };
    
} // namespace ECS
