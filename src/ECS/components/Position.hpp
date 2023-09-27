/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Position
*/

#pragma once

#include "AComponent.hpp"

namespace ECS
{
    class Position : public AComponent<std::pair<float, float>>
    {
    public:
        Position();
        Position(std::pair<float, float> value);
        ~Position();

        int setValue(std::pair<float, float> value);
        std::pair<float, float> getValue() const;

    protected:
    private:
        float _x;
        float _y;
    };
} // namespace ECS
