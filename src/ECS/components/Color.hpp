/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** Color
*/

#pragma once

#include "RlColor.hpp"

namespace ECS {
    struct Color {
            Color()
                : color(0, 0, 0, 255){};
            Color(int r, int g, int b, int a = 255)
                : color(r, g, b, a){};
            Color(Raylib::RlColor color)
                : color(color){};

            Raylib::RlColor color;
    };

} // namespace ECS
