/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Color
*/

#pragma once

#include "AComponent.hpp"
#include "RlColor.hpp"

namespace ECS
{
    class Color : public AComponent<Raylib::RlColor>
    {
    public:
        Color();
        ~Color();

        int setValue(Raylib::RlColor value);
        Raylib::RlColor getValue() const;

    protected:
    private:
        Raylib::RlColor _color;
    };
} // namespace ECS
