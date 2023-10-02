/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Color
*/

#pragma once

#include <string>

#include "AComponent.hpp"
#include "RlColor.hpp"

namespace ECS
{
    class Color : public AComponent
    {
    public:
        Color();
        Color(int r, int g, int b, int a = 255);
        Color(Raylib::RlColor value);
        ~Color();

        int setValue(int r, int g, int b, int a = 255);
        int setValue(std::string value);
        std::any getValue() const;

    protected:
    private:
        Raylib::RlColor _color;
    };
} // namespace ECS
