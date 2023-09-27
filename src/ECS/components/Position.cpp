/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Position
*/

#include "Position.hpp"

namespace ECS
{
    Position::Position()
    {
        _x = 0;
        _y = 0;
    }

    Position::Position(std::pair<float, float> value)
    {
        _x = value.first;
        _y = value.second;
    }

    Position::~Position()
    {
    }

    int Position::setValue(std::pair<float, float> value)
    {
        _x = value.first;
        _y = value.second;
        return 0;
    }

    std::pair<float, float> Position::getValue() const
    {
        return std::make_pair(_x, _y);
    }
} // namespace ECS
