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
        Color(int r, int g, int b, int a = 255);
        Color(Raylib::RlColor value);
        ~Color();

        int setValue(int r, int g, int b, int a = 255);
        int setValue(Raylib::RlColor value);
        Raylib::RlColor getValue() const;

    protected:
    private:
        Raylib::RlColor _color;
    };
} // namespace ECS
