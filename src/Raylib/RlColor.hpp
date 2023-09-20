/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlColor
*/

#pragma once

#include "raylib.h"

namespace Raylib {
    class RlColor {
        public:
            RlColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
            ~RlColor();

            Color getColor();
            void setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
        private:
            Color _color;
    };
}
