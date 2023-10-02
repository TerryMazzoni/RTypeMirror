/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlDraw
*/

#pragma once

#include "raylib.h"
#include "RlColor.hpp"
#include "RlTexture.hpp"

namespace Raylib
{
    /**
     * @brief Clear the background
     *
     * @param color Color of the background
     */
    void clear(RlColor color);
    /**
     * @brief Begin drawing
     *
     */
    void beginDraw();
    /**
     * @brief End drawing
     *
     */
    void endDraw();
    void draw(RlTexture texture, int x, int y, RlColor color);
    void drawEx(RlTexture texture, Vector2 position, Vector2 values, RlColor color);
}
