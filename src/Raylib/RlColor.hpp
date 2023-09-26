/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlColor
*/

#pragma once

#include "raylib.h"

namespace Raylib
{
    class RlColor
    {
    public:
        RlColor();
        RlColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
        ~RlColor();

        /**
         * @brief Get the Color object
         *
         * @return Color
         */
        Color getColor();
        /**
         * @brief Set the Color object
         *
         * @param r Red value of the color
         * @param g Green value of the color
         * @param b Blue value of the color
         * @param a Alpha value of the color
         */
        void setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);

    private:
        Color _color;
    };
}
