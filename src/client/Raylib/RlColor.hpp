/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlColor
*/

#pragma once

extern "C" {
    #include "raylib.h"
}

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
        /**
         * @brief Get the Red value of the color
         *
         * @return unsigned char
         */
        unsigned char getR() const;
        /**
         * @brief Get the Green value of the color
         *
         * @return unsigned char
         */
        unsigned char getG() const;
        /**
         * @brief Get the Blue value of the color
         *
         * @return unsigned char
         */
        unsigned char getB() const;

    private:
        Color _color;
    };
}
