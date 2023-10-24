/*
** EPITECH PROJECT, 2023
** RTypeMirror
** File description:
** RlDraw
*/

#pragma once

#include "raylib.h"
#include "RlColor.hpp"

namespace Raylib
{
    /**
     * @brief Clear the background
     *
     * @param color Color of the background
     */
    void clear(Color color);
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
    void draw(Texture2D texture, int x, int y, Color color);
    /**
     * @brief Draw a texture with a specified rotation and scale
     * 
     * @param RlTexture Texture to draw
     * @param Vector2 Position of the texture
     * @param Vector2 Rotation and scale of the texture
     * @param RlColor Color of the texture
     */
    void drawEx(Texture2D texture, Vector2 position, Vector2 values, Color color);
}
