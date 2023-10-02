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

    int Position::setValue(std::string value)
    {
        _x = std::stof(value.substr(0, value.find(',')));
        _y = std::stof(value.substr(value.find(',') + 1));
        return 0;
    }

    std::any Position::getValue() const
    {
        return std::pair<float, float>(_x, _y);
    }
} // namespace ECS
