/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlText
*/

#pragma once

#include <string>

#include "raylib.h"
#include "RlColor.hpp"
#include "RlFont.hpp"

namespace Raylib
{
    /**
     * @brief Draw a text on the screen
     *
     * @param text String to draw
     * @param values Vector3 containing the x position, y position and font size
     * @param color Color of the text
     */
    void drawText(std::string text, Vector3 values, RlColor color = RlColor(255, 255, 255));
    /**
     * @brief Draw a text with a specific font on the screen
     *
     * @param font Font to use
     * @param text String to draw
     * @param values Vector4 containing the x position, y position, font size and spacing
     * @param color Color of the text
     */
    void drawTextEx(RlFont font, std::string text, Vector4 values, RlColor color = RlColor(255, 255, 255));
}
