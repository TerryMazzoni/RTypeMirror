/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Position
*/

#pragma once

#include <string>

#include "AComponent.hpp"

namespace ECS
{
    class Position : public AComponent
    {
    public:
        Position();
        Position(std::pair<float, float> value);
        ~Position();

        int setValue(std::string value);
        std::any getValue() const;

    protected:
    private:
        float _x;
        float _y;
    };
} // namespace ECS
