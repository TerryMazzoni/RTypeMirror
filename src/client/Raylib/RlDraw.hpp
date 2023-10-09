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
    /**
     * @brief Draw a texture
     *
     * @param RlTexture Texture to draw
     * @param int X position
     * @param int Y position
     * @param RlColor Color of the texture
    */
    void draw(RlTexture texture, int x, int y, RlColor color);
    /**
     * @brief Draw a texture with a specified rotation and scale
     * 
     * @param RlTexture Texture to draw
     * @param Vector2 Position of the texture
     * @param Vector2 Rotation and scale of the texture
     * @param RlColor Color of the texture
     */
    void drawEx(RlTexture texture, Vector2 position, Vector2 values, RlColor color);
}
